package markup;

import java.util.List;

public class UnorderedList extends AbstractListElement {
    public UnorderedList(List<ListItem> blocks) {
        super(blocks);
    }

    @Override
    public void toHtml(StringBuilder res) {
        super.toHtml(res, "<ul>", "</ul>");
    }

    @Override
    public void toMarkdown(StringBuilder res) {
        // do nothing
        // throw new NoSuchMethodError("No markdown here");
    }
}
