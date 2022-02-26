package expression;

import expression.generic.Resolver;

public final class Subtract<T> extends AbstractBinaryOperator<T> {
    public Subtract(CommonGenericExpression<T> first, CommonGenericExpression<T> second, Resolver<T> resolver) {
        super(first, second, resolver);
    }

    @Override
    public String getSign() {
        return " - ";
    }

    @Override
    public int getPriority() {
        return 1;
    }

    @Override
    public boolean isCommutative() {
        return false;
    }

    @Override
    public T calculate(T x, T y) {
        return resolver.sub(x, y);
    }
}
