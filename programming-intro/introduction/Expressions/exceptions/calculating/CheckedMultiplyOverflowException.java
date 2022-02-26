package expression.exceptions.calculating;

import expression.exceptions.calculating.CalculateOverflowException;

/**
 * @author Pavel Martynov (git: CovarianceMomentum)
 */

public class CheckedMultiplyOverflowException extends CalculateOverflowException {
    public CheckedMultiplyOverflowException(int x, int y) {
        super("multiply", x + " * " + y);
    }
}
