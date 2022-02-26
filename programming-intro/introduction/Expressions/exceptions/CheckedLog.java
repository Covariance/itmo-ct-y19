package expression.exceptions;

import expression.AbstractBinaryOperator;
import expression.CommonExpression;
import expression.exceptions.calculating.NegativeLogarithmException;

/**
 * @author Pavel Martynov (git: CovarianceMomentum)
 */

public final class CheckedLog extends AbstractBinaryOperator {
    public CheckedLog(CommonExpression first, CommonExpression second) {
        super(first, second);
    }

    @Override
    public int getPriority() {
        return 0;
    }

    @Override
    public String getSign() {
        return " // ";
    }

    @Override
    public int calculate(int x, int y) {
        if (x < 1 || y <= 0 || y == 1) {
            throw new NegativeLogarithmException("Negative logarithm exception: log(" + x + ")" + y);
        }
        int cnt = 0, n = 1, mem = x / y;
        while (n <= mem) {
            cnt++;
            n *= y;
        }
        return cnt;
    }
}
