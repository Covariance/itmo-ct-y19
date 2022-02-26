package markup;

public class Text implements Paragraphable {
    String text;

    public Text(String text) {
        this.text = text;
    }

    public static String htmlScreen(String string) {
        return string.replace("&", "&amp;")
                .replace("\\", "")
                .replace("<", "&lt;")
                .replace(">", "&gt;");
    }

    @Override
    public void toMarkdown(StringBuilder res) {
        res.append(text);
    }

    @Override
    public void toHtml(StringBuilder res) {
        res.append(Text.htmlScreen(text));
    }
}
