package expression.exceptions.calculating;

import expression.exceptions.calculating.CalculateOverflowException;

/**
 * @author Pavel Martynov (git: CovarianceMomentum)
 */

public class CheckedAddOverflowException extends CalculateOverflowException {
    public CheckedAddOverflowException(int x, int y) {
        super("add", x + " + " + y);
    }
}
