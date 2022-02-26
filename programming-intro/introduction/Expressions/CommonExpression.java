package expression;

public interface CommonExpression extends Expression, TripleExpression {
    @Override
    default int evaluate(int x) {
        return evaluate(x, 0, 0);
    }

    default int getPriority() {
        return -1;
    }

    default boolean isCommutative() {
        return true;
    }
}
