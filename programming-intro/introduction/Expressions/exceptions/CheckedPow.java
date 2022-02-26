package expression.exceptions;

import expression.AbstractBinaryOperator;
import expression.CommonExpression;
import expression.exceptions.calculating.CheckedPowerOverflowException;
import expression.exceptions.calculating.NegativePowerCalculateException;
import expression.CalculationUtilities;

/**
 * @author Pavel Martynov (git: CovarianceMomentum)
 */

public final class CheckedPow extends AbstractBinaryOperator {
    public CheckedPow(CommonExpression first, CommonExpression second) {
        super(first, second);
    }

    @Override
    public int calculate(int x, int y) {
        if ((x == 0 && y == 0) || (y < 0)) {
            throw new NegativePowerCalculateException(x + "**" + y);
        }
        if (x == 1 || x == 0) {
            return x;
        }
        if (x == -1) {
            return 1 - 2 * (y % 2);
        }
        return binaryPower(x, y);

    }

    private void checkPowerOverflow(int x, int y, int realX, int realY) {
        if (CalculationUtilities.checkNonZeroMultiply(x, y)) { //TODO
            throw new CheckedPowerOverflowException(realX + "**" + realY);
        }
    }

    private int binaryPower(int x, int y) {
        int realX = x, realY = y;
        if (y == 0) {
            return 1;
        }
        int r = 1;
        while (y != 0) {
            if (y % 2 == 1) {
                checkPowerOverflow(x, r, realX, realY); // TODO
                r *= x;
                y--;
            }
            y /= 2;
            if (y != 0) {
                checkPowerOverflow(x, x, realX, realY); //TODO
            }
            x = x * x;
        }
        return r;
    }

    @Override
    public int getPriority() {
        return -1;
    }

    @Override
    public String getSign() {
        return " ** ";
    }
}
