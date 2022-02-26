package expression.generic;

import expression.exceptions.calculating.CalculateDBZException;

/**
 * @author Pavel Martynov (git: CovarianceMomentum)
 */

public class UncheckedIntegerResolver implements Resolver<Integer> {
    @Override
    public Integer parse(String number) {
        return Integer.parseInt(number);
    }

    @Override
    public Integer add(Integer a, Integer b) {
        return a + b;
    }

    @Override
    public Integer sub(Integer a, Integer b) {
        return a - b;
    }

    @Override
    public Integer mul(Integer a, Integer b) {
        return a * b;
    }

    @Override
    public Integer div(Integer a, Integer b) {
        if (b == 0) {
            throw new CalculateDBZException(a + " / " + b);
        }
        return a / b;
    }

    @Override
    public Integer min(Integer a, Integer b) {
        return (a < b) ? a : b;
    }

    @Override
    public Integer max(Integer a, Integer b) {
        return (a < b) ? b : a;
    }

    @Override
    public Integer neg(Integer a) {
        return -a;
    }

    @Override
    public Integer count(Integer a) {
        return Integer.bitCount(a);
    }

    @Override
    public Integer intValue(Integer a) {
        return a;
    }

    @Override
    public String interpret(Integer a) {
        return a.toString();
    }
}
