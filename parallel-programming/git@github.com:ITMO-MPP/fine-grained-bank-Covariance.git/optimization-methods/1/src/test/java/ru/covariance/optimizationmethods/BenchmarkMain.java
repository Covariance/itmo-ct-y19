package ru.covariance.optimizationmethods;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;
import java.util.concurrent.TimeUnit;
import java.util.function.DoubleUnaryOperator;
import java.util.stream.Collectors;
import java.util.stream.IntStream;
import org.openjdk.jmh.annotations.Benchmark;
import org.openjdk.jmh.annotations.BenchmarkMode;
import org.openjdk.jmh.annotations.Fork;
import org.openjdk.jmh.annotations.Mode;
import org.openjdk.jmh.annotations.OutputTimeUnit;
import org.openjdk.jmh.annotations.Param;
import org.openjdk.jmh.annotations.Scope;
import org.openjdk.jmh.annotations.State;
import org.openjdk.jmh.infra.Blackhole;
import ru.covariance.optimizationmethods.core.AbstractDoubleIterativeMinimizer;
import ru.covariance.optimizationmethods.core.methods.one.BrentMinimizer;
import ru.covariance.optimizationmethods.core.methods.one.DichotomyMinimizer;
import ru.covariance.optimizationmethods.core.methods.one.FibonacciMinimizer;
import ru.covariance.optimizationmethods.core.methods.one.GoldenRatioMinimizer;
import ru.covariance.optimizationmethods.core.methods.one.ParabolicMinimizer;

public class BenchmarkMain {

  public static final DoubleUnaryOperator f = x -> x * Math.sin(x) + 2 * Math.cos(x);
  public static final double leftBorder = -6;
  public static final double rightBorder = -4;
  public static final double eps = 1e-9;

  @State(Scope.Benchmark)
  public static class FunctionState {

    public Random random = new Random(42);

    @Param(value = {"100", "1000", "10000"})
    public int iterations;

    public DoubleUnaryOperator f = BenchmarkMain.f;
  }

  @Benchmark
  @BenchmarkMode(Mode.AverageTime)
  @OutputTimeUnit(TimeUnit.NANOSECONDS)
  @Fork(value = 1, warmups = 1)
  public void functionCalculationBenchmark(FunctionState state, Blackhole blackhole) {
    for (int i = 0; i < state.iterations; i++) {
      blackhole.consume(state.f.applyAsDouble(100 * (state.random.nextDouble() - 0.5)));
    }
  }

  @Benchmark
  @BenchmarkMode(Mode.AverageTime)
  @OutputTimeUnit(TimeUnit.NANOSECONDS)
  @Fork(value = 1, warmups = 1)
  public void dichotomyCalculationBenchmark(Blackhole blackhole) {
    blackhole.consume(new DichotomyMinimizer(leftBorder, rightBorder, f, eps).min());
  }

  @Benchmark
  @BenchmarkMode(Mode.AverageTime)
  @OutputTimeUnit(TimeUnit.NANOSECONDS)
  @Fork(value = 1, warmups = 1)
  public void goldenRationCalculationBenchmark(Blackhole blackhole) {
    blackhole.consume(new GoldenRatioMinimizer(leftBorder, rightBorder, f).min());
  }

  @Benchmark
  @BenchmarkMode(Mode.AverageTime)
  @OutputTimeUnit(TimeUnit.NANOSECONDS)
  @Fork(value = 1, warmups = 1)
  public void fibonacciCalculationBenchmark(Blackhole blackhole) {
    blackhole.consume(new FibonacciMinimizer(leftBorder, rightBorder, f).min());
  }

  @Benchmark
  @BenchmarkMode(Mode.AverageTime)
  @OutputTimeUnit(TimeUnit.NANOSECONDS)
  @Fork(value = 1, warmups = 1)
  public void parabolicCalculationBenchmark(Blackhole blackhole) {
    blackhole.consume(new ParabolicMinimizer(leftBorder, rightBorder, f, eps).min());
  }

  @Benchmark
  @BenchmarkMode(Mode.AverageTime)
  @OutputTimeUnit(TimeUnit.NANOSECONDS)
  @Fork(value = 1, warmups = 1)
  public void brentCalculationBenchmark(Blackhole blackhole) {
    blackhole.consume(new BrentMinimizer(leftBorder, rightBorder, f).min());
  }

  public static class DoubleUnaryOperatorRecording implements DoubleUnaryOperator {

    public static class FunctionCall {

      double x, fx;

      public FunctionCall(double x, double fx) {
        this.x = x;
        this.fx = fx;
      }
    }

    private final DoubleUnaryOperator inner;
    private final List<FunctionCall> calls = new ArrayList<>();

    public DoubleUnaryOperatorRecording(DoubleUnaryOperator inner) {
      this.inner = inner;
    }

    @Override
    public double applyAsDouble(double x) {
      double fx = inner.applyAsDouble(x);
      this.calls.add(new FunctionCall(x, fx));
      return fx;
    }

    public List<FunctionCall> getCalls() {
      return calls;
    }

    public void clear() {
      calls.clear();
    }
  }

  public static void calculateIterationValuesForMinimizer(AbstractDoubleIterativeMinimizer minimizer,
      DoubleUnaryOperatorRecording recorder) {
    recorder.clear();
    double lastLeft = leftBorder;
    double lastRight = rightBorder;

    System.out.print(
        "\\begin{center}\n\\begin{tabular}{|c|c|c|c|}\n\\hline\nЛевая граница & Правая граница & Коэффициент & Вызовы функции\\\\\n\\hline\n");
    while (!minimizer.converged()) {
      System.out.printf("%.4f & %.4f & %.4f & %s \\\\\n\\hline\n",
          minimizer.getLeft(),
          minimizer.getRight(),
          (minimizer.getRight() - minimizer.getLeft()) / (lastRight - lastLeft),
          recorder.getCalls().stream().map(call -> String.format("<%.4f; %.4f>", call.x, call.fx))
              .collect(Collectors.joining(" ")));
      lastLeft = minimizer.getLeft();
      lastRight = minimizer.getRight();
      recorder.clear();
      minimizer.iterate();
    }
    System.out.print("\\end{tabular}\n\\end{center}");
  }

  public static void calculateIterationValuesForEpsilon(double eps) {
    DoubleUnaryOperatorRecording recorder = new DoubleUnaryOperatorRecording(f);

    {
      System.out.println("Дихотомия, " + eps);
      AbstractDoubleIterativeMinimizer minimizer = new DichotomyMinimizer(leftBorder, rightBorder,
          recorder, eps);
      minimizer.setEpsilon(eps);
      calculateIterationValuesForMinimizer(minimizer, recorder);
      recorder.clear();
    }

    {
      System.out.println("Золотое сечение, " + eps);
      AbstractDoubleIterativeMinimizer minimizer = new GoldenRatioMinimizer(leftBorder, rightBorder,
          recorder);
      minimizer.setEpsilon(eps);
      calculateIterationValuesForMinimizer(minimizer, recorder);
      recorder.clear();
    }

    {
      System.out.println("Фибоначчи, " + eps);
      AbstractDoubleIterativeMinimizer minimizer = new FibonacciMinimizer(leftBorder, rightBorder,
          recorder);
      minimizer.setEpsilon(eps);
      calculateIterationValuesForMinimizer(minimizer, recorder);
      recorder.clear();
    }

    {
      System.out.println("Параболы, " + eps);
      AbstractDoubleIterativeMinimizer minimizer = new ParabolicMinimizer(leftBorder, rightBorder,
          recorder);
      minimizer.setEpsilon(eps);
      calculateIterationValuesForMinimizer(minimizer, recorder);
      recorder.clear();
    }

    {
      System.out.println("Брент, " + eps);
      AbstractDoubleIterativeMinimizer minimizer = new BrentMinimizer(leftBorder, rightBorder,
          recorder);
      minimizer.setEpsilon(eps);
      calculateIterationValuesForMinimizer(minimizer, recorder);
      recorder.clear();
    }
  }

  public static class DoubleUnaryOperatorCounter implements DoubleUnaryOperator {

    private final DoubleUnaryOperator inner;
    private int counter = 0;

    public DoubleUnaryOperatorCounter(DoubleUnaryOperator inner) {
      this.inner = inner;
    }

    @Override
    public double applyAsDouble(double operand) {
      counter++;
      return inner.applyAsDouble(operand);
    }

    public int getCounter() {
      return counter;
    }

    public void resetCounter() {
      counter = 0;
    }
  }

  public static void calculateCounts() {
    List<Double> epsilons = IntStream.range(1, 10)
        .mapToDouble(i -> Math.pow(10, -i))
        .boxed()
        .collect(Collectors.toList());

    DoubleUnaryOperatorCounter counter = new DoubleUnaryOperatorCounter(f);

    System.out.print("Dichotomy: ");
    for (Double e : epsilons) {
      AbstractDoubleIterativeMinimizer minimizer = new DichotomyMinimizer(leftBorder, rightBorder,
          counter, e);
      minimizer.setEpsilon(e);
      minimizer.min();
      System.out.print(counter.getCounter() + " ");
      counter.resetCounter();
    }

    System.out.println();
    System.out.print("Golden Ration: ");
    for (Double e : epsilons) {
      AbstractDoubleIterativeMinimizer minimizer = new GoldenRatioMinimizer(leftBorder, rightBorder,
          counter);
      minimizer.setEpsilon(e);
      minimizer.min();
      System.out.print(counter.getCounter() + " ");
      counter.resetCounter();
    }

    System.out.println();
    System.out.print("Fibonacci: ");
    for (Double e : epsilons) {
      AbstractDoubleIterativeMinimizer minimizer = new FibonacciMinimizer(leftBorder, rightBorder,
          counter);
      minimizer.setEpsilon(e);
      minimizer.min();
      System.out.print(counter.getCounter() + " ");
      counter.resetCounter();
    }

    System.out.println();
    System.out.print("Parabolic: ");
    for (Double e : epsilons) {
      AbstractDoubleIterativeMinimizer minimizer = new ParabolicMinimizer(leftBorder, rightBorder,
          counter, e);
      minimizer.setEpsilon(e);
      minimizer.min();
      System.out.print(counter.getCounter() + " ");
      counter.resetCounter();
    }

    System.out.println();
    System.out.print("Brent: ");
    for (Double e : epsilons) {
      AbstractDoubleIterativeMinimizer minimizer = new BrentMinimizer(leftBorder, rightBorder, counter);
      minimizer.setEpsilon(e);
      minimizer.min();
      System.out.print(counter.getCounter() + " ");
      counter.resetCounter();
    }
  }

  public static void runBenchmarks(String[] args) throws IOException {
    org.openjdk.jmh.Main.main(args);
  }
}


