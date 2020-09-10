package expression.exceptions.calculating;

import expression.exceptions.calculating.CalculateOverflowException;

/**
 * @author Pavel Martynov (git: CovarianceMomentum)
 */

public class NegateOverflowException extends CalculateOverflowException {
    public NegateOverflowException(int x) {
        super("negate", "-" + x);
    }
}
