package markup;

import java.util.List;

public abstract class AbstractListElement extends AbstractElement implements Listable {
    public AbstractListElement(List<ListItem> blocks) {
        super(blocks);
    }
}
