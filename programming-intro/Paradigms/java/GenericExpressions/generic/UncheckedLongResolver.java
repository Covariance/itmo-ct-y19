package expression.generic;

import expression.exceptions.calculating.CalculateDBZException;

/**
 * @author Pavel Martynov (git: CovarianceMomentum)
 */

public class UncheckedLongResolver implements Resolver<Long> {
    @Override
    public Long parse(String number) {
        return Long.parseLong(number);
    }

    @Override
    public Long add(Long a, Long b) {
        return a + b;
    }

    @Override
    public Long sub(Long a, Long b) {
        return a - b;
    }

    @Override
    public Long mul(Long a, Long b) {
        return a * b;
    }

    @Override
    public Long div(Long a, Long b) {
        if (b == 0) {
            throw new CalculateDBZException(a + " / " + b);
        }
        return a / b;
    }

    @Override
    public Long min(Long a, Long b) {
        return (a < b) ? a : b;
    }

    @Override
    public Long max(Long a, Long b) {
        return (a < b) ? b : a;
    }

    @Override
    public Long neg(Long a) {
        return -a;
    }

    @Override
    public Long count(Long a) {
        return (long) Long.bitCount(a);
    }

    @Override
    public Long intValue(Integer a) {
        return a.longValue();
    }

    @Override
    public String interpret(Long a) {
        return a.toString();
    }
}
