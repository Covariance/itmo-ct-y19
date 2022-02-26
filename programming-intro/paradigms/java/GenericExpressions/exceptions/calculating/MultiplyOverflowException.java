package expression.exceptions.calculating;

import expression.exceptions.calculating.CalculateOverflowException;

/**
 * @author Pavel Martynov (git: CovarianceMomentum)
 */

public class MultiplyOverflowException extends CalculateOverflowException {
    public MultiplyOverflowException(int x, int y) {
        super("multiply", x + " * " + y);
    }
}
