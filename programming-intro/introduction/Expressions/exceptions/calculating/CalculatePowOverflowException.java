package expression.exceptions.calculating;

/**
 * @author Pavel Martynov (git: CovarianceMomentum)
 */

public class CalculatePowOverflowException extends CalculateOverflowException {
    public CalculatePowOverflowException(int x, int y) {
        super("pow", x + " ** " + y);
    }
}
