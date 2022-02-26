package markup;
import java.util.List;

public abstract class AbstractParagraphElement extends AbstractElement implements Paragraphable {
    public AbstractParagraphElement(List<Paragraphable> blocks) {
        super(blocks);
    }
}
