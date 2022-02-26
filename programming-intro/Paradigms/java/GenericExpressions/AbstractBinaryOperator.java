package expression;

import expression.generic.Resolver;

/**
 * @author Pavel Martynov (git: CovarianceMomentum)
 */

public abstract class AbstractBinaryOperator<T> implements CommonGenericExpression<T> {
    protected final CommonGenericExpression<T> first, second;
    protected final Resolver<T> resolver;

    public AbstractBinaryOperator(CommonGenericExpression<T> first, CommonGenericExpression<T> second, Resolver<T> resolver) {
        this.first = first;
        this.second = second;
        this.resolver = resolver;
    }

    @Override
    public String toString() {
        return "(" + first.toString() + this.getSign() + second.toString() + ")";
    }


    private boolean checkSecond() {
        return checkFirst(second) || this.getPriority() == second.getPriority() &&
                (!this.isCommutative() || !second.isCommutative());
    }

    private boolean checkFirst(CommonGenericExpression<T> op) {
        return this.getPriority() < op.getPriority();
    }

    private void applyBracketer(StringBuilder result, CommonGenericExpression<T> op, boolean addBrackets) {
        if (addBrackets) {
            result.append("(").append((op).toMiniString()).append(")");
        } else {
            result.append((op).toMiniString());
        }
    }

    @Override
    public String toMiniString() {
        StringBuilder result = new StringBuilder();
        applyBracketer(result, first, checkFirst(first));
        result.append(this.getSign());
        applyBracketer(result, second, checkSecond());
        return result.toString();
    }

    public abstract T calculate(T x, T y);

    @Override
    public T evaluate(T x, T y, T z) {
        return calculate(first.evaluate(x, y, z), second.evaluate(x, y, z));
    }

    @Override
    public int hashCode() {
        return (first.hashCode() * 31 + second.hashCode()) * 31 + getClass().hashCode();
    }
}
