package expression;

public interface CommonGenericExpression<T> extends TripleGenericExpression<T> {
    default int getPriority() {
        return -1;
    }

    default boolean isCommutative() {
        return true;
    }

    default String getSign() {
        return "";
    }

    default String toMiniString() {
        return toString();
    }
}
