package markup;

import javafx.util.Pair;

import java.util.List;

public class Paragraph extends AbstractElement implements Listable {
    public Paragraph(List<Paragraphable> blocks) {
        super(blocks);
    }

    public static Pair<Integer, Integer> findMdOccurrence(String str, int l, int r) {
        return null;
    }

    public static Paragraphable parseMdOccurrence(String str, int l, int r, boolean[] exemplarFound) {
        return null;
    }

    @Override
    public void toHtml(StringBuilder res) {
        super.toHtml(res, "<p>", "</p>");
    }
}
