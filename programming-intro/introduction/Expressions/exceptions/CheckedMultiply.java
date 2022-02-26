package expression.exceptions;

import expression.*;
import expression.exceptions.calculating.CheckedMultiplyOverflowException;
import expression.CalculationUtilities;

/**
 * @author Pavel Martynov (git: CovarianceMomentum)
 */

public final class CheckedMultiply extends AbstractBinaryOperator {
    public CheckedMultiply(CommonExpression first, CommonExpression second) {
        super(first, second);
    }

    @Override
    public String getSign() {
        return " * ";
    }

    @Override
    public int getPriority() {
        return 0;
    }

    @Override
    public int calculate(int x, int y) {
        if (x != 0 && y != 0 && CalculationUtilities.checkNonZeroMultiply(x, y)) {
            throw new CheckedMultiplyOverflowException(x, y); //TODO
        }
        return x * y;
    }
}
