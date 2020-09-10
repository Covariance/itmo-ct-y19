package expression.exceptions;

import expression.AbstractUnaryOperator;
import expression.CommonExpression;
import expression.exceptions.calculating.NegativeLogarithmException;

/**
 * @author Pavel Martynov (git: CovarianceMomentum)
 */

public final class CheckedLog2 extends AbstractUnaryOperator {
    public CheckedLog2(CommonExpression operand) {
        super(operand);
    }

    @Override
    public int getPriority() {
        return -1;
    }

    @Override
    public String getSign() {
        return "log2 ";
    }

    @Override
    public int calculate(int x) {
        if (x < 1) {
            throw new NegativeLogarithmException("Negative logarithm exception: log2(" + x + ")");
        }
        int cnt = 0, n = 1;
        while (2 * n <= x && n <= Integer.MAX_VALUE / 2) {
            cnt++;
            n *= 2;
        }
        return cnt;
    }
}
