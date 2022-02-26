package expression;

/**
 * @author Pavel Martynov (git: CovarianceMomentum)
 */

public abstract class AbstractBinaryOperator implements CommonExpression {
    protected final CommonExpression first, second;

    public AbstractBinaryOperator(CommonExpression first, CommonExpression second) {
        this.first = first;
        this.second = second;
    }

    @Override
    public String toString() {
        return "(" + first.toString() + this.getSign() + second.toString() + ")";
    }


    private boolean checkSecond() {
        return checkFirst(second) || this.getPriority() == second.getPriority() &&
                (!this.isCommutative() || !second.isCommutative());
    }

    private boolean checkFirst(CommonExpression op) {
        return this.getPriority() < op.getPriority();
    }

    private void applyBracketer(StringBuilder result, CommonExpression op, boolean addBrackets) {
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

    public abstract int calculate(int x, int y);

    @Override
    public int evaluate(int x, int y, int z) {
        return calculate(first.evaluate(x, y, z), second.evaluate(x, y, z));
    }

    @Override
    public int hashCode() {
        return (first.hashCode() * 31 + second.hashCode()) * 31 + getClass().hashCode();
    }

    @Override
    public boolean equals(Object obj) {
        if (obj != null && getClass() == obj.getClass()) {
            AbstractBinaryOperator castedObj = (AbstractBinaryOperator) obj;
            return  this.first.equals(castedObj.first)
                    && this.second.equals(castedObj.second);
        }
        return false;
    }
}
