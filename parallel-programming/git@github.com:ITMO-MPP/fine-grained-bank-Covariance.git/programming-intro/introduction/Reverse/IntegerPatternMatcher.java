class IntegerPatternMatcher implements PatternMatcher {
    public boolean matchesPattern(String str) {
        try {
            int a = Integer.parseInt(str);
            return true;
        } catch (NumberFormatException e) {
            return false;
        }
    }
}