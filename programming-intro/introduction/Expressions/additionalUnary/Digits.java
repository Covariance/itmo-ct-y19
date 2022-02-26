package expression.additionalUnary;

import expression.AbstractUnaryOperator;
import expression.CommonExpression;

public final class Digits extends AbstractUnaryOperator {
    public Digits(CommonExpression operand) {
        super(operand);
    }

    @Override
    public int calculate(int x) {
        int result = 0;
        while (x != 0) {
            result += x % 10;
            x /= 10;
        }
        return Math.abs(result);//((result < 0) ? -1 : 1) * result;
    }

    @Override
    public String getSign() {
        return "digits ";
    }
}
