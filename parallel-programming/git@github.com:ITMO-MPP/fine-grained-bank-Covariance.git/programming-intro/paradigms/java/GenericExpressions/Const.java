package expression;

import expression.generic.Resolver;

import java.util.Objects;

public final class Const<T> implements CommonGenericExpression<T> {
    private final T value;
    private final Resolver<T> resolver;

    public Const(T value, Resolver<T> resolver) {
        this.value = value;
        this.resolver = resolver;
    }

    @Override
    public T evaluate(T x, T y, T z) {
        return value;
    }

    @Override
    public String toString() {
        return resolver.interpret(value);
    }

    @Override
    public int hashCode() {
        return Objects.hashCode(value);
    }
}
