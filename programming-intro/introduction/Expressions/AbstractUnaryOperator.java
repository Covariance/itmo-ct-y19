package expression;

/**
 * @author Pavel Martynov (git: CovarianceMomentum)
 */

public abstract class AbstractUnaryOperator implements CommonExpression {
    protected final CommonExpression operand;

    @Override
    public boolean isCommutative() {
        return false;
    }

    public AbstractUnaryOperator(CommonExpression operand) {
        this.operand = operand;
    }

    @Override
    public String toString() {
        return this.getSign() + "(" + operand.toString() + ")";
    }

    abstract public int calculate(int x);

    @Override
    public int evaluate(int x, int y, int z) {
        return calculate(operand.evaluate(x, y, z));
    }

    @Override
    public int hashCode() {
        return 6571 * operand.hashCode() + 7 * getSign().hashCode();
    }

    @Override
    public boolean equals(Object obj) {
        if (obj != null && getClass() == obj.getClass()) {
            AbstractUnaryOperator castedObj = (AbstractUnaryOperator) obj;
            return  this.operand.equals(castedObj.operand);
        }
        return false;
    }
}
