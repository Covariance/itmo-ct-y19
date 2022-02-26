package markup;

import java.util.List;

public abstract class AbstractElement implements Markable {
    protected List<? extends Markable> blocks;

    public AbstractElement(List<? extends Markable> blocks) {
        this.blocks = blocks;
    }

    public void toMarkdown(StringBuilder res, String firstBorder, String secondBorder) {
        res.append(firstBorder);
        for (Markable block: this.blocks) {
            block.toMarkdown(res);
        }
        res.append(secondBorder);
    }

    public void toHtml(StringBuilder res, String firstBorder, String secondBorder) {
        res.append(firstBorder);
        for (Markable block: this.blocks) {
            block.toHtml(res);
        }
        res.append(secondBorder);
    }

    @Override
    public void toMarkdown(StringBuilder res) {
        for (Markable block: this.blocks) {
            block.toMarkdown(res);
        }
    }

    @Override
    public void toHtml(StringBuilder res) {
        for (Markable block: this.blocks) {
            block.toHtml(res);
        }
    }
}
