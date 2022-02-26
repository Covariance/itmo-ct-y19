package expression;

import expression.generic.Resolver;

/**
 * @author Pavel Martynov (git: CovarianceMomentum)
 */

public abstract class AbstractUnaryOperator<T> implements CommonGenericExpression<T> {
    protected final CommonGenericExpression<T> operand;
    protected final Resolver<T> resolver;

    public AbstractUnaryOperator(CommonGenericExpression<T> operand, Resolver<T> resolver) {
        this.operand = operand;
        this.resolver = resolver;
    }

    @Override
    public boolean isCommutative() {
        return false;
    }

    @Override
    public String toString() {
        return this.getSign() + "(" + operand.toString() + ")";
    }

    abstract public T calculate(T x);

    @Override
    public T evaluate(T x, T y, T z) {
        return calculate(operand.evaluate(x, y, z));
    }

    @Override
    public int hashCode() {
        return 6571 * operand.hashCode() + 7 * getSign().hashCode();
    }
}
