package expression;

/**
 * @author Pavel Martynov (git: CovarianceMomentum)
 */

public class CalculationUtilities {
    public static boolean checkNonZeroMultiply(int x, int y) {
        /*
            TODO
            Let this check be wrong, then:

             / (((x * y) mod INTMAX) - ((x * y) mod INTMAX) mod x)) / x = y
            |  (((x * y) mod INTMAX) - ((x * y) mod INTMAX) mod y)) / y = x
             \ x * y > INTMAX

            Let x >= y, then
             z = (((x * y) mod INTMAX) - ((x * y) mod INTMAX) mod x)) > 0, then
             z = xy, but z < INTMAX, !?!
         */
        return ((x * y) / y != x || (x * y) / x != y);
    }
}
