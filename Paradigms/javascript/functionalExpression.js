"use strict";

const operation = (op, ...args) => (...vars) => op(...args.map(val => val(...vars)));

const negate = x => operation(x => -x, x);
const abs = x => operation(x => (x < 0 ? -x : x), x);

const multiply = (x, y) => operation((x, y) => x * y, x, y);
const subtract = (x, y) => operation((x, y) => x - y, x, y);
const add = (x, y) => operation((x, y) => x + y, x, y);
const divide = (x, y) => operation((x, y) => x / y, x, y);

const iff = (x, y, z) => operation((x, y, z) => x < 0 ? z : y, x, y, z);

const OPS = {
    "negate": negate, "abs": abs,
    "+": add, "-": subtract, "*": multiply, "/": divide,
    "iff": iff
};

const OPS_SHIFT = {
    "negate": 1, "abs": 1,
    "+": 2, "-": 2, "*": 2, "/": 2,
    "iff": 3
};

const VARS = {
    "x": 0,
    "y": 1,
    "z": 2
};

const variable = (variableName) => {
    const ind = VARS[variableName];
    return function (...args) {
        return args[ind];
    }
};

const cnst = (value) => () => value;
const one = cnst(1);
const two = cnst(2);
const CNSTS = {
    "one": one,
    "two": two
};


function parse(expression) {
    let stack = [];
    const parseToken = function (token) {
        if (token in OPS) {
            stack.push(OPS[token](...stack.splice(-OPS_SHIFT[token], OPS_SHIFT[token])));
        } else if (token in VARS) {
            stack.push(variable(token))
        } else if (token in CNSTS) {
            stack.push(CNSTS[token]);
        } else {
            stack.push(cnst(+token))
        }
    };
    expression.trim().split(/\s+/).forEach(parseToken);
    return stack.pop();
}