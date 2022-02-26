package expression.exceptions.calculating;

/**
 * @author Pavel Martynov (git: CovarianceMomentum)
 */

public class CheckedPowerOverflowException extends CalculateOverflowException {
    public CheckedPowerOverflowException(String expression) {
        super("power", expression);
    }
}
