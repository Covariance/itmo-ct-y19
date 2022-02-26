package expression.additionalUnary;

import expression.AbstractUnaryOperator;
import expression.CommonExpression;

public final class Reverse extends AbstractUnaryOperator {
    public Reverse(CommonExpression operand) {
        super(operand);
    }

    @Override
    public int calculate(int x) {
        int result = 0;
        while (x != 0) {
            result *= 10;
            result += x % 10;
            x /= 10;
        }
        return result;
    }

    @Override
    public String getSign() {
        return "reverse ";
    }
}
