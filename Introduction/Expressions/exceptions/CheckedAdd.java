package expression.exceptions;

import expression.AbstractBinaryOperator;
import expression.CommonExpression;
import expression.exceptions.calculating.CalculateException;
import expression.exceptions.calculating.CheckedAddOverflowException;

public final class CheckedAdd extends AbstractBinaryOperator {
    public CheckedAdd(CommonExpression first, CommonExpression second) {
        super(first, second);
    }

    @Override
    public String getSign() {
        return " + ";
    }

    @Override
    public int getPriority() {
        return 1;
    }

    @Override
    public int calculate(int x, int y) throws CalculateException {
        if ((x > 0 && Integer.MAX_VALUE - x < y)
                || (x < 0 && Integer.MIN_VALUE - x > y)) {
            throw new CheckedAddOverflowException(x, y);
        }
        return x + y;
    }
}
