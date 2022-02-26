package expression;

public final class Negate extends AbstractUnaryOperator {
    public Negate(CommonExpression operand) {
        super(operand);
    }

    @Override
    public int calculate(int x) {
        return -x;
    }

    @Override
    public String getSign() {
        return "-";
    }
}
