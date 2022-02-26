package expression;

import expression.generic.Resolver;

/**
 * @author Pavel Martynov (git: CovarianceMomentum)
 */

public final class Max<T> extends AbstractBinaryOperator<T> {
    public Max(CommonGenericExpression<T> first, CommonGenericExpression<T> second, Resolver<T> resolver) {
        super(first, second, resolver);
    }

    @Override
    public T calculate(T x, T y) {
        return resolver.max(x, y);
    }
}
