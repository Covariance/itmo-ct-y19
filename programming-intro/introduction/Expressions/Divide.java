package expression;

public final class Divide extends AbstractBinaryOperator {
    public Divide(CommonExpression first, CommonExpression second) {
        super(first, second);
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
    public int calculate(int x, int y) {
        return x / y;
    }

    @Override
    public boolean isCommutative() {
        return false;
    }
}
