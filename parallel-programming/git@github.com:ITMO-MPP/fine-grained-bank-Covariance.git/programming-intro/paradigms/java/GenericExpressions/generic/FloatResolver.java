package expression.generic;

/**
 * @author Pavel Martynov (git: CovarianceMomentum)
 */

import java.lang.Float;

public class FloatResolver implements Resolver<Float> {
    @Override
    public Float parse(String number) {
        return Float.parseFloat(number);
    }

    @Override
    public Float add(Float a, Float b) {
        return a + b;
    }

    @Override
    public Float sub(Float a, Float b) {
        return a - b;
    }

    @Override
    public Float mul(Float a, Float b) {
        return a * b;
    }

    @Override
    public Float div(Float a, Float b) {
        return a / b;
    }

    @Override
    public Float min(Float a, Float b) {
        return (a < b) ? a : b;
    }

    @Override
    public Float max(Float a, Float b) {
        return (a < b) ? b : a;
    }

    @Override
    public Float neg(Float a) {
        return -a;
    }

    @Override
    public Float count(Float a) {
        return (float) Integer.bitCount(Float.floatToIntBits(a));
    }

    @Override
    public Float intValue(Integer a) {
        return a.floatValue();
    }

    @Override
    public String interpret(Float a) {
        return a.toString();
    }
}
