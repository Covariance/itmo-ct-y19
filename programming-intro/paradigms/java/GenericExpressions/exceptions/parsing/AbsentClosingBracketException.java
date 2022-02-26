package expression.exceptions.parsing;

/**
 * @author Pavel Martynov (git: CovarianceMomentum)
 */

public class AbsentClosingBracketException extends ClosingBracketException {
    public AbsentClosingBracketException(String message) {
        super("Expected", message);
    }
}