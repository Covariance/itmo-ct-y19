package expression.generic;

import expression.exceptions.calculating.CalculateDBZException;

/**
 * @author Pavel Martynov (git: CovarianceMomentum)
 */

public class UncheckedShortResolver implements Resolver<Short> {
    @Override
    public Short parse(String number) {
        return (short) Integer.parseInt(number);
    }

    @Override
    public Short add(Short a, Short b) {
        return (short) (a + b);
    }

    @Override
    public Short sub(Short a, Short b) {
        return (short) (a - b);
    }

    @Override
    public Short mul(Short a, Short b) {
        return (short) (a * b);
    }

    @Override
    public Short div(Short a, Short b) {
        if (b == 0) {
            throw new CalculateDBZException(a + " / " + b);
        }
        return (short) (a / b);
    }

    @Override
    public Short min(Short a, Short b) {
        return (a < b) ? a : b;
    }

    @Override
    public Short max(Short a, Short b) {
        return (a < b) ? b : a;
    }

    @Override
    public Short neg(Short a) {
        return (short) -a;
    }

    @Override
    public Short count(Short a) {
        return (short) Integer.bitCount(a);
    }

    @Override
    public Short intValue(Integer a) {
        return a.shortValue();
    }

    @Override
    public String interpret(Short a) {
        return a.toString();
    }
}
