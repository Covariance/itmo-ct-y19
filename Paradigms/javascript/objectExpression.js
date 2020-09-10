"use strict";

// region common code
const OPS = {};

let expressionConstructor = (constructor, evaluate, toPrefix, toPostfix, toString, diff) => {
    constructor.prototype.evaluate = evaluate;
    constructor.prototype.prefix = toPrefix;
    constructor.prototype.postfix = toPostfix;
    constructor.prototype.toString = toString;
    constructor.prototype.diff = diff;
};
// endregion

// region constants
function Const(value) {
    this._value = value;
}

expressionConstructor(
    Const,
    function () {
        return +this._value
    },
    function () {
        return this._value.toString();
    },
    function () {
        return this._value.toString();
    },
    function () {
        return this._value.toString();
    },
    function () {
        return Const.ZERO
    }
);

Const.ZERO = new Const(0);
Const.ONE = new Const(1);
Const.TWO = new Const(2);
// endregion

// region variables
let VARS = {
    'x': 0,
    'y': 1,
    'z': 2
};

function Variable(name) {
    this._name = name;
    this._ind = VARS[name];
}

expressionConstructor(
    Variable,
    function (...args) {
        return args[this._ind]
    },
    function () {
        return this._name;
    },
    function () {
        return this._name;
    },
    function () {
        return this._name;
    },
    function (d) {
        return ((this._name === d) ? Const.ONE : Const.ZERO)
    }
);
// endregion

// region operations
function Operation(...args) {
    this._args = args;
}

expressionConstructor(
    Operation,
    function (...vars) {
        return this._operation(...this._args.map(val => val.evaluate(...vars)))
    },
    function () {
        return "(" + this._name + " " + this._args.map(x => x.prefix()).join(" ") + ")";
    },
    function () {
        return "(" + this._args.map(x => x.postfix()).join(" ") + " " + this._name + ")"
    },
    function () {
        return [...this._args, this._name].join(" ");
    },
    function (d) {
        return this._differentiator(d, ...this._args)
    },
);

let createOperation = (_operation, _name, _differentiator) => {
    let Constructor = function (...args) {
        Operation.call(this, ...args)
    };
    Constructor.prototype = Object.create(Operation.prototype);
    Constructor.prototype._operation = _operation;
    Constructor.prototype._name = _name;
    Constructor.prototype._differentiator = _differentiator;
    Constructor.prototype.constructor = Constructor;
    OPS[_name] = Constructor;
    return Constructor;
};

let Negate = createOperation(
    a => -a,
    "negate",
    (name, f) => new Negate(f.diff(name)) // (-f)' = -f'
);

const Add = createOperation(
    (a, b) => a + b,
    "+",
    (name, f, g) => new Add(f.diff(name), g.diff(name)) // (f + g)' = f' + g'
);

const Subtract = createOperation(
    (a, b) => a - b,
    "-",
    (name, f, g) => new Subtract(f.diff(name), g.diff(name)) // (f - g)' = f' - g'
);

const Multiply = createOperation(
    (a, b) => a * b,
    "*",
    (name, f, g) => new Add(
        new Multiply(f.diff(name), g),
        new Multiply(f, g.diff(name))
    ) // (f * g)' = f' * g + f * g'
);

const Divide = createOperation(
    (a, b) => a / b,
    "/",
    (name, f, g) =>
        new Divide(
            new Subtract(
                new Multiply(f.diff(name), g),
                new Multiply(f, g.diff(name))),
            new Multiply(g, g)
        ) // (f / g)' = (f'g - g'f) / (g*g)
);

const Gauss = createOperation(
    (a, b, c, x) => a * Math.exp(-(x - b) * (x - b) / (2 * c * c)),
    // g(a, b, c, x) = a * e^(-(x-b)^2 / 2*c^2)
    "gauss",
    function (name, a, b, c, x) {
        const sub = new Subtract(x, b);
        const gauss = new Gauss(Const.ONE, b, c, x);
        return new Add(
            new Multiply(
                a.diff(name),
                gauss
            ),
            new Multiply(
                a,
                new Multiply(
                    gauss,
                    new Negate(
                        new Divide(
                            new Multiply(sub, sub),
                            new Multiply(Const.TWO, new Multiply(c, c))
                        )
                    ).diff(name)
                )
            )
        );
    }
    // (a * e^(-(x-b)^2 / 2*c^2))' = -(a*e^(-(x - b)^2/(2 c^2))*(x - b))/c^2
);

const Mean = createOperation(
    (...args) => args.reduce((a, b) => a + b, 0) / args.length,
    "mean",
    (name, ...args) => new Mean(...args.map(a => a.diff(name)))
);

const Var = createOperation(
    (...args) => {
        return args.map(x => x - args.reduce((a, b) => a + b, 0) / args.length) // a - E(a)
            .map(x => x * x) // (a - E(a))^2
            .reduce((a, b) => a + b, 0) / args.length; // E((a-E(a))^2)
    },
    "var",
    (x, ...operands) => {
        const mean = new Mean(...operands);
        return new Mean(...operands.map(a => {
            const prod = new Subtract(a, mean);
            return new Multiply(prod, prod).diff(x);
        }));
    });
// endregion

// region errors
function ParseError(message) {
    this.message = this.name + ": " + message;
}

ParseError.prototype = Object.create(Error.prototype);

function registerError(name) {
    function ErrorConstructor(message) {
        ParseError.call(this, message);
    }

    ErrorConstructor.prototype = Object.create(ParseError.prototype);
    ErrorConstructor.prototype.name = name;
    ErrorConstructor.prototype.constructor = ParseError;

    return ErrorConstructor;
}

const EOFError = registerError("EOFError");
const InvalidTokenError = registerError("InvalidTokenError");
const BracketError = registerError("BracketError");
const OperationExpectedError = registerError("OperationExpectedError");
const InvalidArgumentsError = registerError("InvalidArgumentsError");

// endregion

function parse(expression) {
    let stack = [];

    const parseToken = function (token) {
        if (token in OPS) {
            token = OPS[token];
            let len = token.prototype._operation.length === 0 ? stack.length : token.prototype._operation.length;
            stack.push(new token(...stack.splice(-len, len)));
        } else if (token in VARS) {
            stack.push(new Variable(token));
        } else {
            stack.push(new Const(Number.parseInt(token)));
        }
    };
    expression.trim().split(/\s+/).forEach(parseToken);
    return stack.pop();
}

// region parser
function Parser(sauce) {
    this.pos = 0;
    this.source = sauce;
}

Parser.prototype.getRegExp = function (regExp) {
    let token = "";
    while (this.pos < this.source.length && this.source[this.pos].match(regExp)) {
        token += this.source[this.pos++];
    }
    return token;
};
Parser.prototype.getToken = function () {
    return this.getRegExp(/[^\s()]/);
};
Parser.prototype.skipWhitespaces = function () {
    return this.getRegExp(/\s/);
};

Parser.prototype.parseOperation = function (stack) {
    let operationToken = this.getOperation(stack);

    if (operationToken in OPS) {
        let operation = OPS[operationToken];
        let len = operation.prototype._operation.length === 0 ? stack.length : operation.prototype._operation.length;
        if (stack.some(x => x in OPS) || len !== stack.length) {
            throw new InvalidArgumentsError("operation is argument of another operation at position: " + this.pos);
        } else {
            return new operation(...stack);
        }
    } else {
        throw new InvalidArgumentsError("many operations in one bracket at position " + this.pos);
    }
};

Parser.prototype.test = function (symbol) {
    if (this.pos < this.source.length && symbol === this.source[this.pos]) {
        this.pos++;
        return true;
    }
    return false;
};

Parser.prototype.parseNext = function () {
    this.skipWhitespaces();

    if (this.pos === this.source.length) {
        throw new EOFError("unexpected EOF at position: " + this.pos);
    } else if (this.test('(')) {
        let stack = [];

        this.skipWhitespaces();
        while (this.pos < this.source.length && this.source[this.pos] !== ')') {
            if (this.test('(')) {
                this.pos--;
                stack.push(this.parseNext());
            } else {
                let token = this.getToken();

                if (token in VARS) {
                    stack.push(new Variable(token));
                } else if (!isNaN(token)) {
                    stack.push(new Const(+token));
                } else if (token in OPS) {
                    stack.push(token);
                } else {
                    throw new InvalidTokenError("invalid token at position " + (this.pos - token.length) + ": '" + token + "'");
                }
            }
            this.skipWhitespaces();
        }

        if (!this.test(')')) {
            throw new BracketError("')' expected at position " + (this.pos - 1));
        }
        if (stack.length === 1 && !(stack[0] in OPS)) {
            throw new OperationExpectedError("operation expected at position " + this.pos);
        }
        if (stack.length === 0) {
            throw new InvalidArgumentsError("non-zero arguments expected at position " + this.pos);
        }

        return this.parseOperation(stack);
    } else {
        let token = this.getToken();

        if (token in VARS) {
            return new Variable(token);
        } else if (!isNaN(token)) {
            return new Const(+token);
        } else {
            throw new InvalidTokenError(token + " should be Const or Variable, position " + this.pos);
        }
    }
};

Parser.prototype.parse = function () {
    this.skipWhitespaces();
    if (this.pos === this.source.length) {
        throw new EOFError("empty expression");
    }
    let expr = this.parseNext();
    this.skipWhitespaces();

    if (this.pos !== this.source.length) {
        throw new EOFError("non-empty tail after parsing at position: " + this.pos);
    }

    return expr;
};
// endregion

const createParser = function (taker) {
    const ParserConstructor = function (input) {
        Parser.call(this, input);
    };

    ParserConstructor.prototype = Object.create(Parser.prototype);
    ParserConstructor.prototype.getOperation = taker;

    return ParserConstructor;
};

const PrefixParser = createParser(stack => stack.shift());
const PostfixParser = createParser(stack => stack.pop());

const parsePrefix = (input) => new PrefixParser(input).parse();
const parsePostfix = (input) => new PostfixParser(input).parse();