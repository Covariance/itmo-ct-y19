package expression.parser;

import expression.*;
import expression.additionalUnary.Absolute;
import expression.additionalUnary.Digits;
import expression.additionalUnary.Reverse;
import expression.additionalUnary.Square;
import expression.bitwise.*;
import expression.exceptions.*;
import expression.exceptions.parsing.*;

import java.util.List;
import java.util.Map;

public class ExpressionParser implements Parser {

    @Override
    public CommonExpression parse(String expression) {
        return new InnerParser(new StringSource(expression)).parseTop();
    }

    private final static List<Map<String, BinOpsCreator>> BINARY_ORDER = List.of(
            Map.of("+", CheckedAdd::new,
                    "-", CheckedSubtract::new),
            Map.of("*", CheckedMultiply::new,
                    "/", CheckedDivide::new),
            Map.of("//", CheckedLog::new,
                    "**", CheckedPow::new)
    );

    private final static Map<String, UnOpsCreator> UNARY_ORDER = Map.of(
            "abs", Absolute::new,
            "digits", Digits::new,
            "reverse", Reverse::new,
            "square", Square::new,
            "~", BitwiseNot::new,
            "log2", CheckedLog2::new,
            "pow2", CheckedPow2::new
    );

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

    private class InnerParser extends BaseParser {

        protected InnerParser(Source source) {
            super(source);
        }

        private CommonExpression parseTop() throws ParserException {
            CommonExpression result = parse(0);
            if (chq.getLast() != '\0') {
                throw new NonEmptyTailException(errorMessage());
            }
            return result;
        }

        private CommonExpression parse(int type) throws ParserException {
            if (type == BINARY_ORDER.size()) {
                return parsePrimal();
            }

            CommonExpression left = parse(type + 1);
            Map<String, BinOpsCreator> level = BINARY_ORDER.get(type);
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

        private CommonExpression parsePrimal() throws ParserException {
            skipWhitespace();
            if (test('-')) {
                if (between('0', '9')) {
                    return checkedParseInteger("-" + parseNumber());
                    /* TODO
                    try {
                        return new Const(Integer.parseInt("-" + parseNumber()));
                    } catch (NumberFormatException e) {
                        throw new InvalidConstantException(e.getMessage());
                    }
                     */
                } else {
                    return new CheckedNegate(parsePrimal());
                }
            } else if (between('0', '9')) {
                return checkedParseInteger(parseNumber());
                /* TODO
                try {
                    return new Const(Integer.parseInt(parseNumber()));
                } catch (NumberFormatException e) {
                    throw new InvalidConstantException(e.getMessage());
                }
                 */
            } else if (test('(')) {
                CommonExpression result = parse(0);
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
                        return new Variable(op);
                    }
                } else {
                    throw exceptionSwitch(op);
                }
            }
        }

        private Const checkedParseInteger(String s) throws ParserException {
            try {
                return new Const(Integer.parseInt(s));
            } catch (NumberFormatException e) {
                throw new InvalidConstantException("Invalid integer: " + s + " in " + errorMessage());
            }
        }

        private ParserException exceptionSwitch(String op) {
            for (Map<String, BinOpsCreator> level : BINARY_ORDER) {
                if (level.containsKey(op)){
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
