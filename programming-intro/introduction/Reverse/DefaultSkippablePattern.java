class DefaultSkippablePattern implements Skippable {
    public boolean isSkippable(int codePoint) {
        return Character.isWhitespace(codePoint) || (codePoint == '\n') || (codePoint == '\r');
    }
}