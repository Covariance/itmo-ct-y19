package expression.exceptions.parsing;

/**
 * @author Pavel Martynov (git: CovarianceMomentum)
 */

public class InvalidConstantException extends ParserException {
    public InvalidConstantException(String message) {
        super("Invalid constant: " + message);
    }
}
