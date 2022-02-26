package expression.exceptions.calculating;

/**
 * @author Pavel Martynov (git: CovarianceMomentum)
 */

public class CalculateDBZException extends CalculateException {
    public CalculateDBZException(String error) {
        super("Division by zero in: " + error);
    }
}
