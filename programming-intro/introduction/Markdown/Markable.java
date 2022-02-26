package markup;

public interface Markable {
    void toHtml(StringBuilder res);
    void toMarkdown(StringBuilder res);
}
