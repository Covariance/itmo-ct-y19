package expression.exceptions.parsing;

/**
 * @author Pavel Martynov (git: CovarianceMomentum)
 */

public class InvalidPrimalException extends ParserException {
    public InvalidPrimalException(String message) {
        super("Primal value cannot be parsed: " + message);
    }
}
