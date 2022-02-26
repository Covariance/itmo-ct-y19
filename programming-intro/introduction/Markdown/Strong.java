package markup;

import javafx.util.Pair;

import java.util.List;

public class Strong extends AbstractParagraphElement {
    public Strong(List<Paragraphable> blocks) {
        super(blocks);
    }

    public static Pair<Integer, Integer> findMdOccurrence(String str, int l, int r) {
        Pair<Integer, Integer> firstDelimiter = markup.Utils.findTagsOccurrence(str, l, r, "**", "**"),
                secondDelimiter = markup.Utils.findTagsOccurrence(str, l, r, "__", "__");
        if (secondDelimiter.getKey() < firstDelimiter.getKey() && secondDelimiter.getValue() != r) {
            return secondDelimiter;
        }
        return firstDelimiter;
    }

    public static Paragraphable parseMdOccurrence(String str, int l, int r, boolean[] exemplarFound) {
        return null;
    }

    @Override
    public void toMarkdown(StringBuilder res) {
        super.toMarkdown(res, "__", "__");
    }

    @Override
    public void toHtml(StringBuilder res) {
        super.toHtml(res, "<strong>", "</strong>");
    }
}
