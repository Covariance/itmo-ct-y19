package markup;

import java.util.List;

public class OrderedList extends AbstractListElement {
    public OrderedList(List<ListItem> blocks) {
        super(blocks);
    }

    @Override
    public void toHtml(StringBuilder res) {
        super.toHtml(res, "<ol>", "</ol>");
    }

    @Override
    public void toMarkdown(StringBuilder res) {
        // do nothing
        // throw new NoSuchMethodError("No markdown here");
    }
}