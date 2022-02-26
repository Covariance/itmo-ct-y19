package expression.exceptions;

import expression.*;
import expression.exceptions.calculating.CalculateDBZException;
import expression.exceptions.calculating.CalculateException;
import expression.exceptions.calculating.CheckedDivideOverflowException;

/**
 * @author Pavel Martynov (git: CovarianceMomentum)
 */

public final class CheckedDivide extends AbstractBinaryOperator {
    public CheckedDivide(CommonExpression first, CommonExpression second) {
        super(first, second);
    }

    @Override
    public String getSign() {
        return " / ";
    }

    @Override
    public int getPriority() {
        return 0;
    }

    @Override
    public int calculate(int x, int y) {
        if (y == 0) {
            throw new CalculateDBZException(x, y);
        }
        if (y == -1 && x == Integer.MIN_VALUE) {
            throw new CheckedDivideOverflowException(x, y);
        }
        return x / y;
    }

    @Override
    public boolean isCommutative() {
        return false;
    }
}
