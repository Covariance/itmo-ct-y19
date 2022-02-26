package markup;

import javafx.util.Pair;

import java.util.List;

public class Header extends AbstractElement implements Listable {
    protected int level;
    public Header(List<Paragraphable> blocks, int level) {
        super(blocks);
        this.level = level;
    }

    public static Pair<Integer, Integer> findMdOccurrence(String str, int l, int r) {
        return null;
    }

    public static Paragraphable parseMdOccurrence(String str, int l, int r, boolean[] exemplarFound) {
        return null;
    }

    @Override
    public void toMarkdown(StringBuilder res) {
        StringBuilder firstBorder = new StringBuilder("\n");
        for (int i = 0; i < level; i++) {
            firstBorder.append('#');
        }
        firstBorder.append(' ');
        super.toMarkdown(res, firstBorder.toString(), "\n");
    }

    @Override
    public void toHtml(StringBuilder res) {
        super.toHtml(res, "<h" + Integer.toString(level) + ">", "</h" + Integer.toString(level) + ">");
    }
}
