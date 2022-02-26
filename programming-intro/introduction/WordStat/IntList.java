import java.util.Arrays;

public class IntList {
    // Current size
    private int size;

    // List itself
    private int[] list;

    public IntList() {
        this.size = 0;
        this.list = new int[1];
    }

    public IntList(int value) {
        this.size = 1;
        this.list = new int[2];
        this.list[0] = value;
    }

    public IntList(int[] arr) {
        this(arr, arr.length);
    }

    public IntList(int[] arr, int length) {
        this.size = length;
        this.list = Arrays.copyOf(arr, length);
    }

    private void expand() {
        this.list = Arrays.copyOf(this.list, 2*this.list.length);
    }

    public void add(int value) {
        if (size == list.length) {
            this.expand();
        }
        list[size++] = value;
    }

    public int get(int position) throws ArrayIndexOutOfBoundsException {
        return this.list[position];
    }

    public int size() {
        return this.size;
    }
}
