package expression.exceptions.calculating;

import expression.exceptions.calculating.CalculateOverflowException;

/**
 * @author Pavel Martynov (git: CovarianceMomentum)
 */

public class CheckedNegateOverflowException extends CalculateOverflowException {
    public CheckedNegateOverflowException(int x) {
        super("negate", "-" + x);
    }
}
