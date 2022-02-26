package expression.parser;

public class StringSource implements Source {
    private final String data;
    private int pos;
    private final static int NEIGHBORHOOD_SIZE = 15;

    public StringSource(final String data) {
        this.data = data;
    }

    @Override
    public boolean hasNext() {
        return pos < data.length();
    }

    @Override
    public char next() {
        return data.charAt(pos++);
    }

    @Override
    public String errorMessage() {
        return "position: "
                + pos
                + "  [---->"
                + data.substring(Integer.max(0, pos - NEIGHBORHOOD_SIZE), Integer.min(data.length(), pos + NEIGHBORHOOD_SIZE))
                + "<----]";
    }
}
