package expression;

import expression.exceptions.calculating.AddOverflowException;
import expression.generic.Resolver;

public final class Add<T> extends AbstractBinaryOperator<T> {
    public Add(CommonGenericExpression<T> first, CommonGenericExpression<T> second, Resolver<T> resolver) {
        super(first, second, resolver);
    }

    @Override
    public String getSign() {
        return " + ";
    }

    @Override
    public int getPriority() {
        return 1;
    }

    @Override
    public T calculate(T x, T y) throws AddOverflowException {
        return resolver.add(x, y);
    }
}
