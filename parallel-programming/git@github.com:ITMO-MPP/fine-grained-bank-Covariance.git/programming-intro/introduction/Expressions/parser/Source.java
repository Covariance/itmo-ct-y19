package expression.parser;

public interface Source {
    boolean hasNext();
    char next();
    default String errorMessage() {
        return "";
    }
}
