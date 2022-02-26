package expression.exceptions.calculating;

import expression.exceptions.calculating.CalculateOverflowException;

/**
 * @author Pavel Martynov (git: CovarianceMomentum)
 */

public class CheckedSubtractOverflowException extends CalculateOverflowException {
    public CheckedSubtractOverflowException(int x, int y) {
        super("subtract", x + " - " + y);
    }
}
