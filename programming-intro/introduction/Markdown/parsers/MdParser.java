package markup.parsers;

import javafx.util.Pair;
import markup.*;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class MdParser {

    final static protected Exemplar[] tags = new Exemplar[]{
            new Exemplar("**", "**", Strong::new),
            new Exemplar("__", "__", Strong::new),
            new Exemplar("*", "*", Emphasis::new),
            new Exemplar("_", "_", Emphasis::new),
            new Exemplar("`", "`", Code::new),
            new Exemplar("~~", "~~", Strikeout::new),
            new Exemplar("--", "--", Strikeout::new),
            new Exemplar("++", "++", Underline::new)
    };

    protected static int isHeader(String string) {
        int len = 0;
        while (len < string.length() && string.charAt(len) == '#') {
            len++;
        }
        return (len == string.length() || len == 0 || string.charAt(len) != ' ') ? -1 : len;
    }

    protected static List<String> divideByIndents(String string) {
        List<String> result = new ArrayList<>();
        int l = 0, m;
        // String divider = System.lineSeparator() + System.lineSeparator();
        while ((m = string.indexOf("\n\n", l)) != -1) {
            result.add(string.substring(l, m));
            l = m + 2;
        }
        if (l != string.length()) {
            result.add(string.substring(l));
        }
        return result;
    }

    public static List<Paragraphable> parseText(
            String text,
            int left,
            int right,
            boolean[] exemplarFound,
            Pair<Integer, Integer>[] linkPositions,
            int lastLink
    ) {
        List<Paragraphable> result = new ArrayList<>();
        Pair<Integer, Integer> segmentBorders, closest;
        for (int i = left; i < right; i++) {
            while (lastLink != linkPositions.length && linkPositions[lastLink].getKey() < i) {
                lastLink++;
            }
            closest = new Pair<>(right, right);
            Exemplar closestTag = null;
            for (int j = 0; j < tags.length; j++) {
                if (exemplarFound[j]) {
                    segmentBorders = markup.Utils.findTagsOccurrenceWithLinks(
                            text,
                            i,
                            right,
                            tags[j].getLeftDelimiter(),
                            tags[j].getRightDelimiter(),
                            linkPositions,
                            lastLink
                    );
                    if (segmentBorders.getKey() < closest.getKey() && segmentBorders.getValue() != right) {
                        closestTag = tags[j];
                        closest = segmentBorders;
                    }
                    exemplarFound[j] = (segmentBorders.getValue() != right);
                }
            }
            if (lastLink == linkPositions.length || linkPositions[lastLink].getKey() > closest.getKey()) {
                if (closestTag == null) {
                    result.add(new Text(text.substring(i, right)));
                    i = right;
                } else {
                    result.add(new Text(text.substring(i, closest.getKey())));
                    result.add(closestTag.createInstance(
                            parseText(
                                    text,
                                    closest.getKey() + closestTag.getLeftDelimiter().length(),
                                    closest.getValue(),
                                    exemplarFound.clone(),
                                    linkPositions,
                                    lastLink
                            )
                    ));
                    i = closest.getValue() + closestTag.getRightDelimiter().length() - 1;
                }

            } else if (closestTag == null || closest.getKey() > linkPositions[lastLink].getKey()) {
                result.add(new Text(text.substring(i, linkPositions[lastLink].getKey())));
                result.add(markup.Link.parseMdOccurrence(
                        text,
                        linkPositions[lastLink].getKey(),
                        linkPositions[lastLink].getValue(),
                        exemplarFound,
                        linkPositions
                ));
                i = linkPositions[lastLink++].getValue();
            }
        }
        return result;
    }

    public static Pair<Integer, Integer>[] generateLinkPositions(String text) {
        Pair<Integer, Integer>[] result = new Pair[1];
        int currentSize = 0;
        Pair<Integer, Integer> currentPair;
        int currentPos = 0;
        while ((currentPair = markup.Link.findMdOccurrence(text, currentPos, text.length())).getValue() != text.length()) {
            result = (result.length == currentSize) ? Arrays.copyOf(result, 2 * result.length) : result;
            result[currentSize++] = currentPair;
            currentPos = currentPair.getValue();
        }
        return Arrays.copyOf(result, currentSize);
    }

    protected static Markable parseIndent(String indent) {
        while (indent.length() > 0 && indent.charAt(0) == '\n') {
            indent = indent.substring(1);
        }
        boolean[] exemplarFound = new boolean[tags.length];
        Arrays.fill(exemplarFound, true);
        int len = isHeader(indent);
        if (len != -1) {
            String blockWithoutHeader = indent.substring(len + 1);
            Pair<Integer, Integer>[] linkPositions = generateLinkPositions(blockWithoutHeader);
            return (blockWithoutHeader.length() == 0) ? null : new Header(
                    parseText(blockWithoutHeader, exemplarFound, linkPositions),
                    len);
        }
        Pair<Integer, Integer>[] linkPositions = generateLinkPositions(indent);
        return (indent.length() == 0) ? null : new Paragraph(parseText(indent, exemplarFound, linkPositions));
    }

    private static List<Paragraphable> parseText(String indent, boolean[] exemplarFound, Pair<Integer, Integer>[] linkPositions) {
        return parseText(
                indent,
                0,
                indent.length(),
                exemplarFound,
                linkPositions,
                0
        );
    }

    public static Content parseMd(String string) {
        List<String> indents = divideByIndents(string);
        List<Markable> parsedIndents = new ArrayList<>();
        Markable parsedIndent;
        for (String indent : indents) {
            if ((parsedIndent = MdParser.parseIndent(indent)) != null) {
                parsedIndents.add(parsedIndent);
                parsedIndents.add(new Text("\n"));
            }
        }
        return new Content(parsedIndents);
    }
}
