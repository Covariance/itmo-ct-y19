package expression;

import java.util.Objects;

public final class Variable implements CommonExpression {
    private final String name;

    public Variable(String name) {
        this.name = name;
    }

    @Override
    public int evaluate(int x, int y, int z) {
        switch(name) {
            case "x":
                return x;
            case "y":
                return y;
            case "z":
                return z;
            default:
                throw new AssertionError("Unknown variable");
        }
    }

    @Override
    public String toString() {
        return name;
    }

    @Override
    public int hashCode() {
        return Objects.hashCode(name);
    }

    @Override
    public boolean equals(Object obj) {
        if (obj instanceof Variable) {
            Variable castedObj = (Variable) obj;
            return Objects.equals(this.name, castedObj.name);
        } else {
            return false;
        }
    }
}
