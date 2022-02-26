package expression.exceptions.calculating;

/**
 * @author Pavel Martynov (git: CovarianceMomentum)
 */

public class CalculateDBZException extends CalculateException {
    public CalculateDBZException(int x, int y) {
        super("Division by zero in: " + x + " / " + y);
    }
}
