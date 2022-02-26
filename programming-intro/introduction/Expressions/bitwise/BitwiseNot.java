package expression.bitwise;

import expression.AbstractUnaryOperator;
import expression.CommonExpression;

public final class BitwiseNot extends AbstractUnaryOperator {
    public BitwiseNot(CommonExpression operand) {
        super(operand);
    }

    @Override
    public int calculate(int x) {
        return ~x;
    }

    @Override
    public String getSign() {
        return "~";
    }
}
