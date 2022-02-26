package expression;

import expression.generic.Resolver;

/**
 * @author Pavel Martynov (git: CovarianceMomentum)
 */

public final class Min<T> extends AbstractBinaryOperator<T> {
    public Min(CommonGenericExpression<T> first, CommonGenericExpression<T> second, Resolver<T> resolver) {
        super(first, second, resolver);
    }

    @Override
    public T calculate(T x, T y) {
        return resolver.min(x, y);
    }
}
