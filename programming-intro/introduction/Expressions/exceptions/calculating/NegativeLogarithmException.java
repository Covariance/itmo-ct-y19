package expression.exceptions.calculating;

import expression.exceptions.calculating.CalculateException;

/**
 * @author Pavel Martynov (git: CovarianceMomentum)
 */

public class NegativeLogarithmException extends CalculateException {
    public NegativeLogarithmException(String message) {
        super(message);
    }
}
