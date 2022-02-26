package expression.exceptions.calculating;

/**
 * @author Pavel Martynov (git: CovarianceMomentum)
 */

public class PowerOverflowException extends CalculateOverflowException {
    public PowerOverflowException(String expression) {
        super("power", expression);
    }
}
