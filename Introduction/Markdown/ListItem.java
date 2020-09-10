package markup;

import java.util.List;

public class ListItem extends AbstractElement {
    public ListItem(List<Listable> blocks) {
        super(blocks);
    }

    @Override
    public void toHtml(StringBuilder res) {
        super.toHtml(res, "<li>", "</li>");
    }

    @Override
    public void toMarkdown(StringBuilder res) {
        // do nothing
        // throw new NoSuchMethodError("No markdown here");
    }
}
