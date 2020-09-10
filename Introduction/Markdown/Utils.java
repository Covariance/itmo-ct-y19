package markup;

import javafx.util.Pair;

import java.util.Arrays;

public class Utils {
    public static Pair<Integer, Integer> findTagsOccurrence(String string, int left, int right, String beginningTag, String endingTag) {
        boolean leftBorderFound = false;
        int leftBorder = right, rightBorder = right;
        for (int i = left; i < right - endingTag.length() + 1; i++) {
            if (string.charAt(i) == '\\') {
                i++;
                continue;
            }
            if (leftBorderFound && string.substring(i, i + endingTag.length()).equals(endingTag)) {
                rightBorder = i;
                break;
            }
            if (!leftBorderFound && string.substring(i, i + beginningTag.length()).equals(beginningTag)) {
                leftBorder = i;
                leftBorderFound = true;
                i += beginningTag.length() - 1;
            }
        }
        return new Pair<>(leftBorder, rightBorder);
    }

    public static Pair<Integer, Integer> findTagsOccurrenceWithLinks(
            String string,
            int left,
            int right,
            String beginningTag,
            String endingTag,
            Pair<Integer, Integer>[] linkPositions,
            int lastLink
    ) {
        boolean leftBorderFound = false;
        int leftBorder = right, rightBorder = right;
        for (int i = left; i < right - endingTag.length() + 1; i++) {
            if (lastLink != linkPositions.length && i == linkPositions[lastLink].getKey()) {
                i = linkPositions[lastLink++].getValue() - 1;
            } else {
                if (string.charAt(i) == '\\') {
                    i++;
                    continue;
                }
                if (leftBorderFound && endingTag.equals(string.substring(i, i + endingTag.length()))) {
                    rightBorder = i;
                    break;
                }
                if (!leftBorderFound && beginningTag.equals(string.substring(i, i + beginningTag.length()))) {
                    leftBorder = i;
                    leftBorderFound = true;
                    i += beginningTag.length() - 1;
                }
            }
        }
        return new Pair<>(leftBorder, rightBorder);
    }
}
