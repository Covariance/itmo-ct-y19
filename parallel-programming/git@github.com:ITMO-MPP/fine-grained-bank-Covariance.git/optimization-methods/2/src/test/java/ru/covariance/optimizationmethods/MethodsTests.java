package ru.covariance.optimizationmethods;

import org.junit.jupiter.api.AfterAll;
import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.api.RepeatedTest;
import org.junit.jupiter.api.RepetitionInfo;
import ru.covariance.optimizationmethods.core.AbstractFlatIterativeMinimizer;
import ru.covariance.optimizationmethods.core.FunctionGeneratingData;
import ru.covariance.optimizationmethods.core.Point;
import ru.covariance.optimizationmethods.core.methods.two.ConjugateGradientMethod;
import ru.covariance.optimizationmethods.core.methods.two.FastestDescentMethod;
import ru.covariance.optimizationmethods.core.methods.two.GradientMethod;

import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;
import java.util.*;
import java.util.function.ToDoubleFunction;
import java.util.function.UnaryOperator;
import java.util.stream.Collectors;

import static org.junit.jupiter.api.Assertions.assertTrue;

public class MethodsTests {

  final int[] dims = new int[]{2, 5, 10, 100, 1000, 5000};
  final int[] cardinality = new int[]{1, 200, 400, 600, 800, 1000, 1200, 1400, 1600, 1800, 2000};

  private static final Map<String, List<String>> tables = new HashMap<>();

  private static Point generatePoint(int dim, double x) {
    final double[] p = new double[dim];
    Arrays.fill(p, x);
    return new Point(p);
  }

  @RepeatedTest(6)
  @DisplayName("Conjugate method")
  void test_conjugateGradient(final RepetitionInfo info) {
    int n = dims[info.getCurrentRepetition() - 1];

    runMethod(n, ConjugateGradientMethod.class);
  }

  @RepeatedTest(6)
  @DisplayName("Fastest descent method")
  void test_fastestDescent(final RepetitionInfo info) {
    int n = dims[info.getCurrentRepetition() - 1];

    runMethod(n, FastestDescentMethod.class);
  }

  @RepeatedTest(6)
  @DisplayName("Gradient descent method")
  void test_gradientDescent(final RepetitionInfo info) {
    int n = dims[info.getCurrentRepetition() - 1];

    runMethod(n, GradientMethod.class);
  }

  private int calcIterations(final AbstractFlatIterativeMinimizer minimizer) {
    int iterations = 0;
    while (!minimizer.converged()) {
      iterations++;
      minimizer.iterate();
    }
    return iterations;
  }

  private void runMethod(final int n, final Class<?> minimizer) {
    final Point left = generatePoint(n, -100);
    final Point right = generatePoint(n, 100);

    final String collect = Arrays.stream(cardinality).mapToLong(k -> {
      final FunctionGeneratingData data = RandomCardinalityFunctionGen.gen(n, k);
      try {
        final Constructor<?> declaredConstructor = minimizer.getDeclaredConstructor(Point.class, Point.class,
            ToDoubleFunction.class, UnaryOperator.class, double[].class);

        return calcIterations(
            (AbstractFlatIterativeMinimizer) declaredConstructor.newInstance(left, right,
                data.getFunction(), data.getGradient(), data.getQuadraticForm()));
      } catch (Exception e) {
        e.printStackTrace();
      }
      return -1;
    }).mapToObj(Long::toString).collect(Collectors.joining(",", "[", "]"));

    List<String> toPut = tables.computeIfAbsent(minimizer.getSimpleName(), k -> new ArrayList<>());
    toPut.add(collect);
  }

  @AfterAll
  public static void printAll() {
    for (final Map.Entry<String, List<String>> e : tables.entrySet()) {
      System.out.println(e.getKey());
      System.out.println(e.getValue().stream().collect(Collectors.joining(",", "[", "]")));
    }
  }
}
