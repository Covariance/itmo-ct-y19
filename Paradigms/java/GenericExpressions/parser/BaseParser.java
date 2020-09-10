package expression.parser;

import java.util.List;

public class BaseParser {
    protected CharQueue chq;

    protected BaseParser(final Source source) {
        this.chq = new CharQueue(source);
    }

    protected boolean test(char expected) {
        if (chq.getLast() == expected) {
            chq.pop();
            return true;
        }
        return false;
    }

    protected boolean expect(final char c) {
        if (chq.getLast() != c) {
            return false;
        }
        chq.pop();
        return true;
    }

    protected String getToken(List<TokenChecker> checkers) {
        skipWhitespace();
        for (TokenChecker checker : checkers) {
            if (checker.checkPrefix(chq.getLast())) {
                return chq.getTokenByChecker(checker);
            }
        }
        return "";
    }

    public void skipToken(List<TokenChecker> checkers) {
        int k = getToken(checkers).length();
        while (k-- > 0) {
            chq.pop();
        }
    }

    protected String errorMessage() {
        return chq.errorMessage();
    }

    protected String parseNumber() {
        StringBuilder result = new StringBuilder();
        while (between('0', '9')) {
            result.append(chq.pop());
        }
        return result.toString();
    }

    protected void skipWhitespace() {
        while (test(' ') || test('\r') || test('\n') || test('\t')) {
            // do nothng
        }
    }

    protected boolean between(final char from, final char to) {
        return from <= chq.getLast() && chq.getLast() <= to;
    }
}
