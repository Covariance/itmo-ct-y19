package expression.generic;

import expression.exceptions.calculating.CalculateDBZException;

/**
 * @author Pavel Martynov (git: CovarianceMomentum)
 */

public class ByteResolver implements Resolver<Byte> {
    @Override
    public Byte parse(String number) {
        return (byte) Integer.parseInt(number);
    }

    @Override
    public Byte add(Byte a, Byte b) {
        return (byte) (a + b);
    }

    @Override
    public Byte sub(Byte a, Byte b) {
        return (byte) (a - b);
    }

    @Override
    public Byte mul(Byte a, Byte b) {
        return (byte) (a * b);
    }

    @Override
    public Byte div(Byte a, Byte b) {
        if (b == 0) {
            throw new CalculateDBZException(a + " / "  + b);
        }
        return (byte) (a / b);
    }

    @Override
    public Byte min(Byte a, Byte b) {
        return (a < b) ? a : b;
    }

    @Override
    public Byte max(Byte a, Byte b) {
        return (a < b) ? b : a;
    }

    @Override
    public Byte neg(Byte a) {
        return (byte) (-a);
    }

    @Override
    public Byte count(Byte a) {
        return a == -1 ? 8 : (byte) (Integer.bitCount(a) % 8);
    }

    @Override
    public Byte intValue(Integer a) {
        return a.byteValue();
    }

    @Override
    public String interpret(Byte a) {
        return a.toString();
    }
}
