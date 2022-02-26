package markup;

import javafx.util.Pair;
import markup.parsers.MdParser;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class Link extends AbstractParagraphElement {

    public Link(List<Paragraphable> blocks) {
        super(blocks);
    }

    public static Pair<Integer, Integer> findMdOccurrence(String str, int left, int right) {
       Pair<Integer, Integer> firstPart = markup.Utils.findTagsOccurrence(str, left, right, "[", "](");
       if (firstPart.getValue() == right) {
           return firstPart;
       }
       Pair<Integer, Integer> secondPart = markup.Utils.findTagsOccurrence(str, firstPart.getValue(), right, "(", ")");
       return new Pair<>(firstPart.getKey(), secondPart.getValue());
    }

    public static Paragraphable parseMdOccurrence(
            String str,
            int l,
            int r,
            boolean[] exemplarFound,
            Pair<Integer, Integer>[] linkPositions
    ) {
        int mid = str.indexOf("](", l);
        System.out.println(mid);
        List<Paragraphable> result = new ArrayList<>();
        result.add(new UntouchedText(str.substring(mid + 2, r)));
        boolean[] newExemplarFound = new boolean[exemplarFound.length];
        Arrays.fill(newExemplarFound, true);
        result.addAll(MdParser.parseText(str, l + 1, mid, newExemplarFound, linkPositions, linkPositions.length));
        return new Link(result);
    }

    @Override
    public void toHtml(StringBuilder res) {
        res.append("<a href='");
        blocks.get(0).toHtml(res);
        res.append("'>");
        for (int i = 1; i < blocks.size(); i++) {
            blocks.get(i).toHtml(res);
        }
        res.append("</a>");
    }

    @Override
    public void toMarkdown(StringBuilder res) {
        // do nothing
    }
}
