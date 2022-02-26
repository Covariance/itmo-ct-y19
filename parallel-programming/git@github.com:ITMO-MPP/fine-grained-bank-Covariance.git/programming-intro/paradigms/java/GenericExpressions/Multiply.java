package expression;

import expression.exceptions.calculating.MultiplyOverflowException;
import expression.generic.Resolver;

public final class Multiply<T> extends AbstractBinaryOperator<T> {
    public Multiply(CommonGenericExpression<T> first, CommonGenericExpression<T> second, Resolver<T> resolver) {
        super(first, second, resolver);
    }

    @Override
    public T calculate(T x, T y) throws MultiplyOverflowException {
        return resolver.mul(x, y);
    }

    @Override
    public String getSign() {
        return " * ";
    }

    @Override
    public int getPriority() {
        return 0;
    }
}
