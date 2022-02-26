package markup;

public class UntouchedText implements Paragraphable {
    String text;

    public UntouchedText(String text) {
        this.text = text;
    }

    @Override
    public void toMarkdown(StringBuilder res) {
        res.append(text);
    }

    @Override
    public void toHtml(StringBuilder res) {
        res.append(text);
    }
}