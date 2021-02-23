package ru.covariance.optimizationmethods;

import java.io.IOException;
import java.util.Random;
import java.util.concurrent.TimeUnit;
import java.util.function.DoubleUnaryOperator;
import org.openjdk.jmh.annotations.Benchmark;
import org.openjdk.jmh.annotations.BenchmarkMode;
import org.openjdk.jmh.annotations.Fork;
import org.openjdk.jmh.annotations.Mode;
import org.openjdk.jmh.annotations.OutputTimeUnit;
import org.openjdk.jmh.annotations.Param;
import org.openjdk.jmh.annotations.Scope;
import org.openjdk.jmh.annotations.State;
import org.openjdk.jmh.infra.Blackhole;
import ru.covariance.optimizationmethods.core.methods.BrentMinimizer;
import ru.covariance.optimizationmethods.core.methods.DichotomyMinimizer;
import ru.covariance.optimizationmethods.core.methods.FibonacciMinimizer;
import ru.covariance.optimizationmethods.core.methods.GoldenRatioMinimizer;
import ru.covariance.optimizationmethods.core.methods.ParabolicMinimizer;

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

  public static void main(String[] args) throws IOException {
    DoubleUnaryOperatorCounter counter = new DoubleUnaryOperatorCounter(f);

    new DichotomyMinimizer(leftBorder, rightBorder, counter, eps).min();
    System.out.println("Dichotomy: " + counter.getCounter());
    counter.resetCounter();

    new GoldenRatioMinimizer(leftBorder, rightBorder, counter).min();
    System.out.println("Golden ratio: " + counter.getCounter());
    counter.resetCounter();

    new FibonacciMinimizer(leftBorder, rightBorder, counter).min();
    System.out.println("Fibonacci: " + counter.getCounter());
    counter.resetCounter();

    new ParabolicMinimizer(leftBorder, rightBorder, counter, eps).min();
    System.out.println("Parabolic: " + counter.getCounter());
    counter.resetCounter();

    new BrentMinimizer(leftBorder, rightBorder, counter).min();
    System.out.println("Brent: " + counter.getCounter());
    counter.resetCounter();

    org.openjdk.jmh.Main.main(args);
  }
}


