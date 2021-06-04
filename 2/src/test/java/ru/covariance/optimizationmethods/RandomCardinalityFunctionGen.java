package ru.covariance.optimizationmethods;

import ru.covariance.optimizationmethods.core.FunctionGeneratingData;
import ru.covariance.optimizationmethods.core.Point;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Random;
import java.util.function.ToDoubleFunction;
import java.util.function.UnaryOperator;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

public class RandomCardinalityFunctionGen {

  public static final Random random = new Random(42);

  public static final Double TOP_BORDER = 100.;
  public static final Double BOT_BORDER = 0.;

  public static final Double COORDINATE_TOP_BORDER = 100.;
  public static final Double COORDINATE_BOT_BORDER = -100.0;

  private static ToDoubleFunction<Point> createFunction(final List<Double> a, final List<Double> b) {
    return p -> IntStream.range(0, a.size()).mapToDouble(
        i -> a.get(i) * (p.getValue(i) - b.get(i)) * (p.getValue(i) - b.get(i))
    ).boxed().reduce(0., Double::sum);
  }

  private static UnaryOperator<Point> createGradient(final List<Double> a, final List<Double> b) {
    return p -> {
      final double[] coord = new double[a.size()];
      for (int i = 0; i < a.size(); i++) {
        coord[i] = 2 * a.get(i) * (p.getValue(i) - b.get(i));
      }
      return new Point(coord);
    };
  }

  private static double[] createQuadraticForm(List<Double> a) {
    return a.stream().mapToDouble(x -> 2 * x).toArray();
  }

  public static FunctionGeneratingData gen(int n, int k) {
    List<Double> a =
//            new ArrayList<>(Collections.nCopies(n, 1.0));
            random.doubles(n).map(x -> x * (k - 1) + 1).boxed().collect(Collectors.toList());
    a.set(0, 1.0);
    a.set(a.size() - 1, (double)k);
    Collections.sort(a);
    List<Double> b =
//            Collections.nCopies(n, 5.0);
            random.doubles(n).map(x -> (x - 0.5) * 20).boxed().collect(Collectors.toList());
    return new FunctionGeneratingData(createFunction(a, b), createGradient(a, b), createQuadraticForm(a), new Point(b));
  }
}
