package expression.exceptions;

import expression.*;
import expression.exceptions.calculating.CheckedNegateOverflowException;

/**
 * @author Pavel Martynov (git: CovarianceMomentum)
 */

public final class CheckedNegate extends AbstractUnaryOperator {
    public CheckedNegate(CommonExpression operand) {
        super(operand);
    }

    @Override
    public int calculate(int x) {
        if (x == Integer.MIN_VALUE) {
            throw new CheckedNegateOverflowException(x);
        }
        return -x;
    }

    @Override
    public String getSign() {
        return "-";
    }
}
