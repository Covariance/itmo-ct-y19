package markup;

import java.util.List;

public class Content extends AbstractElement implements Paragraphable{
    public Content(List<? extends Markable> blocks) {
        super(blocks);
    }
}
