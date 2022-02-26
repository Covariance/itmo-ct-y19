package expression.exceptions.calculating;

import expression.exceptions.calculating.CalculateOverflowException;

/**
 * @author Pavel Martynov (git: CovarianceMomentum)
 */

public class SubtractOverflowException extends CalculateOverflowException {
    public SubtractOverflowException(int x, int y) {
        super("subtract", x + " - " + y);
    }
}
