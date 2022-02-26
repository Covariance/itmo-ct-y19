package expression.generic;

import expression.exceptions.calculating.CalculateDBZException;

import java.math.BigInteger;

/**
 * @author Pavel Martynov (git: CovarianceMomentum)
 */

public class BigIntegerResolver implements Resolver<BigInteger> {
    @Override
    public BigInteger parse(String number) {
        return new BigInteger(number);
    }

    @Override
    public BigInteger add(BigInteger a, BigInteger b) {
        return a.add(b);
    }

    @Override
    public BigInteger sub(BigInteger a, BigInteger b) {
        return a.subtract(b);
    }

    @Override
    public BigInteger mul(BigInteger a, BigInteger b) {
        return a.multiply(b);
    }

    @Override
    public BigInteger div(BigInteger a, BigInteger b) {
        if (b.equals(BigInteger.ZERO)) {
            throw new CalculateDBZException(a.toString() + " / " + b.toString());
        }
        return a.divide(b);
    }

    @Override
    public BigInteger min(BigInteger a, BigInteger b) {
        return a.min(b);
    }

    @Override
    public BigInteger max(BigInteger a, BigInteger b) {
        return a.max(b);
    }

    @Override
    public BigInteger neg(BigInteger a) {
        return a.negate();
    }

    @Override
    public BigInteger count(BigInteger a) {
        return new BigInteger(Integer.toString(a.bitCount()));
    }

    @Override
    public BigInteger intValue(Integer a) {
        return new BigInteger(a.toString());
    }

    @Override
    public String interpret(BigInteger a) {
        return a.toString();
    }
}
