package expression;

public final class Multiply extends AbstractBinaryOperator {
    public Multiply(CommonExpression first, CommonExpression second) {
        super(first, second);
    }

    @Override
    public String getSign() {
        return " * ";
    }

    @Override
    public int getPriority() {
        return 0;
    }

    @Override
    public int calculate(int x, int y) {
        return x * y;
    }
}
