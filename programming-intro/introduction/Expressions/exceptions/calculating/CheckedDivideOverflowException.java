package expression.exceptions.calculating;

import expression.exceptions.calculating.CalculateOverflowException;

/**
 * @author Pavel Martynov (git: CovarianceMomentum)
 */

public class CheckedDivideOverflowException extends CalculateOverflowException {
    public CheckedDivideOverflowException(int x, int y) {
        super("division", x + " / " + y);
    }
}
