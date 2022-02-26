package expression.parser;

interface TokenChecker {
    boolean checkPrefix(char symbol);
    boolean check(char symbol, int length);
}
