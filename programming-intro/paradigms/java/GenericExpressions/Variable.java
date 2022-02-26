package expression;

import expression.exceptions.parsing.InvalidPrimalException;

import java.util.Objects;

public final class Variable<T> implements CommonGenericExpression<T> {
    private final String name;

    public Variable(String name) {
        this.name = name;
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
    public T evaluate(T x, T y, T z) {
        if (name.equals("x")) {
            return x;
        }
        if (name.equals("y")) {
            return y;
        }
        if (name.equals("z")) {
            return z;
        }
        throw new InvalidPrimalException("Non-existent variable " + name + " calculated");
    }
}
