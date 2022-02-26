package expression.exceptions;

import expression.AbstractBinaryOperator;
import expression.CommonExpression;
import expression.exceptions.calculating.CalculateException;
import expression.exceptions.calculating.CheckedSubtractOverflowException;

/**
 * @author Pavel Martynov (git: CovarianceMomentum)
 */

public final class CheckedSubtract extends AbstractBinaryOperator {
    public CheckedSubtract(CommonExpression first, CommonExpression second) {
        super(first, second);
    }

    @Override
    public String getSign() {
        return " - ";
    }

    @Override
    public int getPriority() {
        return 1;
    }

    @Override
    public int calculate(int x, int y) {
        if ((y > 0 && Integer.MIN_VALUE + y > x)
                || (y < 0 && Integer.MAX_VALUE + y < x)) {
            throw new CheckedSubtractOverflowException(x, y);
        }
        return x - y;
    }

    @Override
    public boolean isCommutative() {
        return false;
    }
}
