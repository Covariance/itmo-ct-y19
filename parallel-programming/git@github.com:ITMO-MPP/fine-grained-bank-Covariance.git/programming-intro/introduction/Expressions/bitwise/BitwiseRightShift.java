package expression.bitwise;

import expression.AbstractBinaryOperator;
import expression.CommonExpression;

public final class BitwiseRightShift extends AbstractBinaryOperator {
    public BitwiseRightShift(CommonExpression first, CommonExpression second) {
        super(first, second);
    }

    @Override
    public int calculate(int x, int y) {
        return x >> y;
    }

    @Override
    public int getPriority() {
        return 3;
    }

    @Override
    public boolean isCommutative() {
        return false;
    }

    @Override
    public String getSign() {
        return null;
    }
}
