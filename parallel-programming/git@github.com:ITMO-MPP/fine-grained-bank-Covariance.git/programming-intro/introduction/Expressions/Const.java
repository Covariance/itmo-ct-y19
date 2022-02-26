package expression;

import java.util.Objects;

public final class Const implements CommonExpression {
    private final int value;

    public Const(int value) {
        this.value = value;
    }

    @Override
    public int evaluate(int x, int y, int z) {
        return value;
    }

    @Override
    public String toString() {
        return Integer.toString(value);
    }

    @Override
    public int hashCode() {
        return Objects.hashCode(value);
    }

    @Override
    public boolean equals(Object obj) {
        if (obj instanceof Const) {
            Const castedObj = (Const) obj;
            return Objects.equals(this.value, castedObj.value);
        } else {
            return false;
        }
    }
}
