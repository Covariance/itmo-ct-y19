package markup;

import javafx.util.Pair;

import java.util.List;

public class Underline extends AbstractParagraphElement {
    public Underline(List<Paragraphable> blocks) {
        super(blocks);
    }

    public static Pair<Integer, Integer> findMdOccurrence(String str, int l, int r) {
        return markup.Utils.findTagsOccurrence(str, l, r, "++", "++");
    }

    public static Paragraphable parseMdOccurrence(String str, int l, int r, boolean[] exemplarFound) {
        return null;
    }

    @Override
    public void toMarkdown(StringBuilder res) {
        super.toMarkdown(res, "++", "++");
    }

    @Override
    public void toHtml(StringBuilder res) {
        super.toHtml(res, "<u>", "</u>");
    }
}