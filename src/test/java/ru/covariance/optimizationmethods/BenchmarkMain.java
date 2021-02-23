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

public class BenchmarkMain {

  public static final DoubleUnaryOperator f = x -> x * Math.sin(x) + 2 * Math.cos(x);
  public static final double leftBorder = -6;
  public static final double rightBorder = -4;

  @State(Scope.Benchmark)
  public static class FunctionState {
    public Random random = new Random(42);

    @Param(value = {"100", "1000", "1000"})
    public int iterations;

    public DoubleUnaryOperator f = BenchmarkMain.f;
  }

  @Benchmark
  @BenchmarkMode(Mode.All)
  @OutputTimeUnit(TimeUnit.NANOSECONDS)
  @Fork(value = 1, warmups = 1)
  public void functionCalculationBenchmark(FunctionState state, Blackhole blackhole) {
    for (int i = 0; i < state.iterations; i++) {
      blackhole.consume(state.f.applyAsDouble(100 * (state.random.nextDouble() - 0.5)));
    }
  }

  public static void main(String[] args) throws IOException {
    org.openjdk.jmh.Main.main(args);
  }
}


