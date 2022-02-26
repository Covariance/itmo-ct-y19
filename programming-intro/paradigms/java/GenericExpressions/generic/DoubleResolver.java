package expression.generic;

/**
 * @author Pavel Martynov (git: CovarianceMomentum)
 */

public class DoubleResolver implements Resolver<Double> {
    @Override
    public Double parse(String number) {
        return Double.parseDouble(number);
    }

    @Override
    public Double add(Double a, Double b) {
        return a + b;
    }

    @Override
    public Double sub(Double a, Double b) {
        return a - b;
    }

    @Override
    public Double mul(Double a, Double b) {
        return a * b;
    }

    @Override
    public Double div(Double a, Double b) {
        return a / b;
    }

    @Override
    public Double min(Double a, Double b) {
        return (a < b) ? a : b;
    }

    @Override
    public Double max(Double a, Double b) {
        return (a < b) ? b : a;
    }

    @Override
    public Double neg(Double a) {
        return -a;
    }

    @Override
    public Double count(Double a) {
        return (double) Long.bitCount(Double.doubleToLongBits(a));
    }

    @Override
    public Double intValue(Integer a) {
        return a.doubleValue();
    }

    @Override
    public String interpret(Double a) {
        return a.toString();
    }
}
