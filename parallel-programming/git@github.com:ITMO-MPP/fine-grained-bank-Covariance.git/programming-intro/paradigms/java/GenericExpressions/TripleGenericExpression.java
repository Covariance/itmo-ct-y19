package expression;

public interface TripleGenericExpression<T> {
    T evaluate(T x, T y, T z);
}
