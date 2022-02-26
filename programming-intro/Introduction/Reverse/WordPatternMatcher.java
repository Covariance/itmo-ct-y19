class WordPatternMatcher implements PatternMatcher {
    private boolean isWordCharacter(int codePoint) {
        return (codePoint == '\'' || Character.getType(codePoint) == Character.DASH_PUNCTUATION || Character.isLetter(codePoint));
    }

    public boolean matchesPattern(String str) {
        if (str.length() == 0) {
            return false;
        }
        for (int i = 0; i < str.length(); i++) {
            if (!isWordCharacter(str.codePointAt(i))) {
                return false;
            }
        }
        return true;
    }
}