package expression.exceptions.calculating;

import expression.exceptions.calculating.CalculateException;

/**
 * @author Pavel Martynov (git: CovarianceMomentum)
 */

public class CalculateOverflowException extends CalculateException {
    public CalculateOverflowException(String operation, String expression) {
        super("Overflow in " + operation + ": " + expression);
    }
}
