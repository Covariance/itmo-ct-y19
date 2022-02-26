package expression.exceptions.parsing;

/**
 * @author Pavel Martynov (git: CovarianceMomentum)
 */

public class ExpressionEndException extends ParserException {
    public ExpressionEndException(String message) {
        super("Sudden exception end: " + message);
    }
}
