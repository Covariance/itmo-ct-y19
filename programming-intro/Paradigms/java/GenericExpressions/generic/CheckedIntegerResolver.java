package expression.generic;

import expression.CalculationUtilities;
import expression.exceptions.calculating.*;
import expression.exceptions.parsing.InvalidConstantException;

/**
 * @author Pavel Martynov (git: CovarianceMomentum)
 */

public class CheckedIntegerResolver implements Resolver<Integer> {
    @Override
    public Integer parse(String number) throws InvalidConstantException {
        try {
            return Integer.parseInt(number);
        } catch (NumberFormatException e) {
            throw new InvalidConstantException(number);
        }
    }

    @Override
    public Integer add(Integer a, Integer b) throws AddOverflowException {
        if ((a > 0 && Integer.MAX_VALUE - a < b)
                || (a < 0 && Integer.MIN_VALUE - a > b)) {
            throw new AddOverflowException(a, b);
        }
        return a + b;
    }

    @Override
    public Integer sub(Integer a, Integer b) {
        if ((b > 0 && Integer.MIN_VALUE + b > a)
                || (b < 0 && Integer.MAX_VALUE + b < a)) {
            throw new SubtractOverflowException(a, b);
        }
        return a - b;
    }

    @Override
    public Integer mul(Integer a, Integer b) {
        if (a != 0 && b != 0 && CalculationUtilities.checkNonZeroMultiply(a, b)) {
            throw new MultiplyOverflowException(a, b);
        }
        return a * b;
    }

    @Override
    public Integer div(Integer a, Integer b) {
        if (b == 0) {
            throw new CalculateDBZException(a.toString() + " / " + b.toString());
        }
        if (b == -1 && a == Integer.MIN_VALUE) {
            throw new DivideOverflowException(a, b);
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
        if (a == Integer.MIN_VALUE) {
            throw new NegateOverflowException(a);
        }
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
