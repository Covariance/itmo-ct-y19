package expression.exceptions.parsing;

/**
 * @author Pavel Martynov (git: CovarianceMomentum)
 */

public class MissingArgumentException extends ParserException {
    public MissingArgumentException(String message) {
        super("Missing argument: " + message);
    }
}
