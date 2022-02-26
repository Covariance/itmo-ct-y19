package expression;

import expression.exceptions.calculating.CalculateDBZException;
import expression.exceptions.calculating.DivideOverflowException;
import expression.generic.Resolver;

public final class Divide<T> extends AbstractBinaryOperator<T> {
    public Divide(CommonGenericExpression<T> first, CommonGenericExpression<T> second, Resolver<T> resolver) {
        super(first, second, resolver);
    }

    @Override
    public String getSign() {
        return " / ";
    }

    @Override
    public int getPriority() {
        return 0;
    }

    @Override
    public boolean isCommutative() {
        return false;
    }

    @Override
    public T calculate(T x, T y) throws DivideOverflowException, CalculateDBZException {
        return resolver.div(x, y);
    }
}
