package expression.additionalUnary;

import expression.AbstractUnaryOperator;
import expression.CommonExpression;

public final class Absolute extends AbstractUnaryOperator {
    public Absolute(CommonExpression operand) {
        super(operand);
    }

    @Override
    public int calculate(int x) {
        return Math.abs(x);
    }

    @Override
    public String getSign() {
        return "abs ";
    }
}
