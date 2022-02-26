package expression.exceptions.calculating;


/**
 * @author Pavel Martynov (git: CovarianceMomentum)
 */

public class NegativePowerCalculateException extends CalculateException {
    public NegativePowerCalculateException(String expression) {
        super("Negative power in: " + expression);
    }
}
