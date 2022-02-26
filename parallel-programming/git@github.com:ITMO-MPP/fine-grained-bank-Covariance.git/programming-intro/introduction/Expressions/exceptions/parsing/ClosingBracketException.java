package expression.exceptions.parsing;

/**
 * @author Pavel Martynov (git: CovarianceMomentum)
 */

public class ClosingBracketException extends ParserException {
    public ClosingBracketException(String type, String message) {
        super(type + " closing bracket exception: " + message);
    }
}
