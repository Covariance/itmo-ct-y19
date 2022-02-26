package expression.additionalUnary;

import expression.AbstractUnaryOperator;
import expression.CommonExpression;

public final class Square extends AbstractUnaryOperator {
    public Square(CommonExpression operand) {
        super(operand);
    }

    @Override
    public int calculate(int x) {
        return x * x;
    }

    @Override
    public String getSign() {
        return "square ";
    }
}
