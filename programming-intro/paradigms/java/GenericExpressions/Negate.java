package expression;

import expression.generic.Resolver;

public final class Negate<T> extends AbstractUnaryOperator<T> {
    public Negate(CommonGenericExpression<T> operand, Resolver<T> resolver) {
        super(operand, resolver);
    }

    @Override
    public T calculate(T x) {
        return resolver.neg(x);
    }

    @Override
    public String getSign() {
        return "-";
    }
}
