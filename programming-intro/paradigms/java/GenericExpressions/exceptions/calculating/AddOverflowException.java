package expression.exceptions.calculating;

import expression.exceptions.calculating.CalculateOverflowException;

/**
 * @author Pavel Martynov (git: CovarianceMomentum)
 */

public class AddOverflowException extends CalculateOverflowException {
    public AddOverflowException(int x, int y) {
        super("add", x + " + " + y);
    }
}
