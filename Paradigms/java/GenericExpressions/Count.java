package expression;

import expression.generic.Resolver;

/**
 * @author Pavel Martynov (git: CovarianceMomentum)
 */

public final class Count<T> extends AbstractUnaryOperator<T> {
    public Count(CommonGenericExpression<T> operand, Resolver<T> resolver) {
        super(operand, resolver);
    }

    @Override
    public T calculate(T x) {
        return resolver.count(x);
    }
}
