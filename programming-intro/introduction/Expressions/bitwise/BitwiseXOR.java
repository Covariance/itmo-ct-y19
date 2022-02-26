package expression.bitwise;

import expression.AbstractBinaryOperator;
import expression.CommonExpression;

public final class BitwiseXOR extends AbstractBinaryOperator {
    public BitwiseXOR(CommonExpression first, CommonExpression second) {
        super(first, second);
    }

    @Override
    public int getPriority() {
        return 2;
    }

    @Override
    public String getSign() {
        return " ^ ";
    }

    @Override
    public int calculate(int x, int y) {
        return x ^ y;
    }
}
