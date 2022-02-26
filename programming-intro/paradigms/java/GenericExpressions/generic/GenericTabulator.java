package expression.generic;

import expression.CommonGenericExpression;
import expression.exceptions.calculating.CalculateException;
import expression.exceptions.parsing.ParserException;
import expression.parser.ExpressionParser;

import java.util.Map;

/**
 * @author Pavel Martynov (git: CovarianceMomentum)
 */

public class GenericTabulator implements Tabulator {
    private final static Map<String, Resolver<?>> MODE_SWITCHER = Map.of(
            "i", new CheckedIntegerResolver(),
            "d", new DoubleResolver(),
            "bi", new BigIntegerResolver(),
            "u", new UncheckedIntegerResolver(),
            "l", new UncheckedLongResolver(),
            "s", new UncheckedShortResolver(),
            "b", new ByteResolver(),
            "f", new FloatResolver()
    );

    @Override
    public Object[][][] tabulate(final String mode, final String expression, final int x1, final int x2, final int y1, final int y2, final int z1, final int z2) throws Exception {
        final Resolver<?> resolver = MODE_SWITCHER.get(mode);
        if (resolver == null) {
            throw new IllegalArgumentException("Mode not supported");
        }
        return generateTable(resolver, expression, x1, x2, y1, y2, z1, z2);
    }

    // TODO
    // Поставил <T> в этой функции, она вынесена отдельно
    // потому что надо обозначить, с каким типом мы работаем
    private static <T> Object[][][] generateTable(final Resolver<T> resolver, final String expression, final int x1, final int x2, final int y1, final int y2, final int z1, final int z2) {
        final Object[][][] result = new Object[x2 - x1 + 1][y2 - y1 + 1][z2 - z1 + 1];
        final CommonGenericExpression<T> processedExpression;
        final ExpressionParser<T> parser = new ExpressionParser<>(resolver);
        try {
            processedExpression = parser.parse(expression);
        } catch (final ParserException e) {
            return result;
        }

        for (int i = x1; i <= x2; i++) {
            for (int j = y1; j <= y2; j++) {
                for (int k = z1; k <= z2; k++) {
                    try {
                        result[i - x1][j - y1][k - z1] = processedExpression.evaluate(
                                resolver.intValue(i),// TODO
                                resolver.intValue(j),// Раньше здесь было resolver.parse(Integer.toString(i,j,k)) =>
                                resolver.intValue(k) // хромала производительность
                        );
                    } catch (final CalculateException ignored) {
                    } // TODO
                    // Раньше здесь ловился эксепшн и значение ставилось в null
                }
            }
        }
        return result;
    }
}
