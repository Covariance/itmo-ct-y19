package expression.bitwise;

import expression.AbstractBinaryOperator;
import expression.CommonExpression;

public final class BitwiseLeftShift extends AbstractBinaryOperator {
    public BitwiseLeftShift(CommonExpression first, CommonExpression second) {
        super(first, second);
    }

    @Override
    public int calculate(int x, int y) {
        return x << y;
    }

    @Override
    public String getSign() {
        return " << ";
    }

    @Override
    public int getPriority() {
        return 3;
    }

    @Override
    public boolean isCommutative() {
        return false;
    }
}
