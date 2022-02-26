package expression.parser;

import expression.*;
import expression.exceptions.parsing.*;
import expression.generic.Resolver;

import java.util.List;
import java.util.Map;

public class ExpressionParser<T> {
    private final Resolver<T> resolver;
    private final List<Map<String, BinOpsCreator<T>>> BINARY_ORDER;
    private final Map<String, UnOpsCreator<T>> UNARY_ORDER;

    private final static List<String> VARIABLE_NAMES = List.of(
            "x", "y", "z"
    );

    private final static List<Character> SPEC_SYMBOLS = List.of(
            '+', '*', '/', '&', '|', '^', '%'
    );

    private final static TokenChecker MINUS_TOKEN_CHECKER = new TokenChecker() {
        @Override
        public boolean checkPrefix(char symbol) {
            return symbol == '-';
        }

        @Override
        public boolean check(char symbol, int length) {
            return length == 0;
        }
    };

    private final static TokenChecker SPEC_TOKEN_CHECKER = new TokenChecker() {
        @Override
        public boolean checkPrefix(char symbol) {
            return SPEC_SYMBOLS.contains(symbol);
        }

        @Override
        public boolean check(char symbol, int length) {
            return SPEC_SYMBOLS.contains(symbol);
        }
    };

    private final static TokenChecker WORD_TOKEN_CHECKER = new TokenChecker() {
        @Override
        public boolean checkPrefix(char symbol) {
            return Character.isAlphabetic(symbol);
        }

        @Override
        public boolean check(char symbol, int length) {
            return Character.isLetterOrDigit(symbol);
        }
    };

    private final static List<TokenChecker> TOKEN_CHECKERS = List.of(
            MINUS_TOKEN_CHECKER, SPEC_TOKEN_CHECKER, WORD_TOKEN_CHECKER
    );

    public ExpressionParser(Resolver<T> resolver) {
        this.resolver = resolver;
        BINARY_ORDER = List.of(
                Map.of(
                        "min", lift(Min::new),
                        "max", lift(Max::new)),
                Map.of("+", lift(Add::new),
                        "-", lift(Subtract::new)),
                Map.of("*", lift(Multiply::new),
                        "/", lift(Divide::new))
        );
        UNARY_ORDER = Map.of("count", expression -> new Count<>(expression, resolver));
    }

    interface BinOpFactory<T> {
        AbstractBinaryOperator<T> create(CommonGenericExpression<T> first, CommonGenericExpression<T> second, Resolver<T> resolver);
    }

    BinOpsCreator<T> lift(BinOpFactory<T> factory) {
        return (f, s) -> factory.create(f, s, resolver);
    }

    public CommonGenericExpression<T> parse(String expression) {
        return new InnerParser(new StringSource(expression), resolver).parseTop();
    }

    private class InnerParser extends BaseParser {
        private final Resolver<T> resolver;

        protected InnerParser(Source source, Resolver<T> resolver) {
            super(source);
            this.resolver = resolver;
        }

        private CommonGenericExpression<T> parseTop() throws ParserException {
            CommonGenericExpression<T> result = parse(0);
            if (chq.getLast() != '\0') {
                throw new NonEmptyTailException(errorMessage());
            }
            return result;
        }

        private CommonGenericExpression<T> parse(int type) throws ParserException {
            if (type == BINARY_ORDER.size()) {
                return parsePrimal();
            }

            CommonGenericExpression<T> left = parse(type + 1);
            Map<String, BinOpsCreator<T>> level = BINARY_ORDER.get(type);
            boolean found;
            do {
                found = false;
                String op = getToken(TOKEN_CHECKERS);
                if (level.containsKey(op)) {
                    skipToken(TOKEN_CHECKERS);
                    left = level.get(op).create(left, parse(type + 1));
                    found = true;
                }
            } while (found);
            return left;
        }

        private CommonGenericExpression<T> parsePrimal() throws ParserException {
            skipWhitespace();
            if (test('-')) {
                if (between('0', '9')) {
                    return new Const<T>(resolver.parse("-" + parseNumber()), resolver);
                } else {
                    return new Negate<T>(parsePrimal(), resolver);
                }
            } else if (between('0', '9')) {
                return new Const<T>(resolver.parse(parseNumber()), resolver);
            } else if (test('(')) {
                CommonGenericExpression<T> result = parse(0);
                if (!expect(')')) {
                    throw new AbsentClosingBracketException(errorMessage());
                }
                return result;
            } else {
                String op = getToken(TOKEN_CHECKERS);
                if (UNARY_ORDER.containsKey(op) || VARIABLE_NAMES.contains(op)) {
                    skipToken(TOKEN_CHECKERS);
                    if (UNARY_ORDER.containsKey(op)) {
                        return UNARY_ORDER.get(op).create(parsePrimal());
                    } else {
                        return new Variable<T>(op);
                    }
                } else {
                    throw exceptionSwitch(op);
                }
            }
        }

        private ParserException exceptionSwitch(String op) {
            for (Map<String, BinOpsCreator<T>> level : BINARY_ORDER) {
                if (level.containsKey(op)) {
                    return new MissingArgumentException("No argument for " + op + " in: " + errorMessage());
                }
            }
            if (op.length() == 0) {
                return new InvalidPrimalException("Empty primal expression: " + errorMessage());
            }
            return new InvalidPrimalException("Invalid primal expression: " + op);
        }
    }
}
