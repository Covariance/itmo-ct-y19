package expression.exceptions.calculating;

import expression.exceptions.calculating.CalculateOverflowException;

/**
 * @author Pavel Martynov (git: CovarianceMomentum)
 */

public class DivideOverflowException extends CalculateOverflowException {
    public DivideOverflowException(int x, int y) {
        super("division", x + " / " + y);
    }
}
