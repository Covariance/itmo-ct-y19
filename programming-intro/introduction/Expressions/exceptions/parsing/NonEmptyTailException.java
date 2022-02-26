package expression.exceptions.parsing;

/**
 * @author Pavel Martynov (git: CovarianceMomentum)
 */

public class NonEmptyTailException extends ParserException {
    public NonEmptyTailException(String message) {
        super("Non-empty tail after parsing expression: " + message);
    }
}
