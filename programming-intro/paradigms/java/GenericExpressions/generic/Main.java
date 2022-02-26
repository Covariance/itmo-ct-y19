package expression.generic;

import expression.CommonGenericExpression;
import expression.parser.ExpressionParser;

import java.math.BigInteger;

/**
 * @author Pavel Martynov (git: CovarianceMomentum)
 */

public class Main {
    public static void main(String[] args) {
        ExpressionParser<BigInteger> parser = new ExpressionParser<>(new BigIntegerResolver());
        CommonGenericExpression<BigInteger> res = parser.parse("10 + 4 / 2 - 7");
        System.out.println(res.toMiniString());
        System.out.println(res.evaluate(new BigInteger("-1"), new BigInteger("-16"), new BigInteger("-16")));
    }
}
