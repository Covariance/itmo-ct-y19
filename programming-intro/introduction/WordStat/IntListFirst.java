public class IntListFirst {
    private IntList list = new IntList();
    private int lastLine = -1;
    private int totalCount;

    public void add(int value, int line) {
        if (line != lastLine) {
            lastLine = line;
            list.add(value);
        }
        totalCount++;
    }

    public String printEntry(String header) {
        StringBuilder result = new StringBuilder(header).append(' ').append(totalCount);
        for (int i = 0; i < list.size(); i++) {
            result.append(' ').append(list.get(i));
        }
        return result.toString();
    }
}
