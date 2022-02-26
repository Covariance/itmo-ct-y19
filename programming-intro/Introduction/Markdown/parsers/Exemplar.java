package markup.parsers;

import markup.Paragraphable;

import java.util.List;

public class Exemplar {
    interface InstanceCreator {
        Paragraphable create(List<Paragraphable> children);
    }

    private String leftDelimiter;
    private String rightDelimiter;
    private InstanceCreator instance;

    public Exemplar(String leftDelimiter, String rightDelimiter, InstanceCreator instance) {
        this.leftDelimiter = leftDelimiter;
        this.rightDelimiter = rightDelimiter;
        this.instance = instance;
    }

    public Paragraphable createInstance(List<Paragraphable> content) {
        return this.instance.create(content);
    }

    public String getRightDelimiter() {
        return rightDelimiter;
    }

    public String getLeftDelimiter() {
        return leftDelimiter;
    }
}