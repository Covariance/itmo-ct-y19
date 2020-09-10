package expression.exceptions;

import expression.AbstractUnaryOperator;
import expression.CommonExpression;
import expression.exceptions.calculating.CheckedPowerOverflowException;
import expression.exceptions.calculating.NegativePowerCalculateException;

/**
 * @author Pavel Martynov (git: CovarianceMomentum)
 */

public final class CheckedPow2 extends AbstractUnaryOperator {
    public CheckedPow2(CommonExpression operand) {
        super(operand);
    }

    @Override
    public int getPriority() {
        return -1;
    }

    @Override
    public String getSign() {
        return "pow2";
    }

    @Override
    public int calculate(int x) {
        if (x < 0) {
            throw new NegativePowerCalculateException("2^" + x);
        }
        if (x >= 31) {
            throw new CheckedPowerOverflowException("2^" + x);
        }
        return 1 << x;
    }
}
