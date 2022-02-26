package expression.exceptions.parsing;

/**
 * @author Pavel Martynov (git: CovarianceMomentum)
 */

public class ExtraClosingBracketException extends ClosingBracketException {
    public ExtraClosingBracketException(String message) {
        super("Unexpected", message);
    }
}
