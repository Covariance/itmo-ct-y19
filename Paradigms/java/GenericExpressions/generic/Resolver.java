package expression.generic;

public interface Resolver<T> {
    T parse(String number);

    T add(T a, T b);

    T sub(T a, T b);

    T mul(T a, T b);

    T div(T a, T b);

    T min(T a, T b);

    T max(T a, T b);

    T neg(T a);

    T count(T a);

    T intValue(Integer a);

    String interpret(T a);
}
