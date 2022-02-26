package expression.parser;

/**
 * @author Pavel Martynov (git: CovarianceMomentum)
 */

public class CharQueue {
    protected final Source source;
    protected char[] q;
    protected int head;
    protected int size;

    public CharQueue(Source source) {
        this.source = source;
        q = new char[1];
        head = 0;
        size = 0;
    }

    private void expand() {
        char[] newQ = new char[q.length * 2];
        for (int i = 0; i < size; i++) {
            newQ[i] = getIndex(i);
        }
        head = 0;
        q = newQ;
    }

    public char pop() {
        if (size == 0) {
            eat();
        }
        head = (head + 1) % q.length;
        size--;
        return q[head == 0 ? q.length - 1 : head - 1];
    }

    public void push(char c) {
        if (size == q.length) {
            expand();
        }
        q[(head + size) % q.length] = c;
        size++;
    }

    public void eat() {
        if (source.hasNext()) {
            push(source.next());
        } else {
            push('\0');
        }
    }

    @Override
    public String toString() {
        StringBuilder result = new StringBuilder();
        for (int i = 0; i < size; i++) {
            result.append(getIndex(i)).append(' ');
        }
        return result.toString();
    }

    public String getTokenByChecker(TokenChecker checker) {
        StringBuilder result = new StringBuilder();
        while (checker.check(getIndex(result.length()), result.length())) {
            result.append(getIndex(result.length()));
            if (result.length() == size) {
                eat();
            }
        }
        return result.toString();
    }

    public char getLast() {
        if (size == 0) {
            eat();
        }
        return q[head];
    }

    public int getSize() {
        return size;
    }

    public char getIndex(int i) {
        return q[(head + i) % q.length];
    }

    public String errorMessage() {
        return source.errorMessage();
    }
}
