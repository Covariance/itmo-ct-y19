package ru.covariance.optimizationmethods;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.function.ToDoubleFunction;
import java.util.function.UnaryOperator;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

import ru.covariance.optimizationmethods.BenchmarkMain.Recorder.FunctionCall;
import ru.covariance.optimizationmethods.app.MainController;
import ru.covariance.optimizationmethods.core.AbstractFlatIterativeMinimizer;
import ru.covariance.optimizationmethods.core.FunctionGeneratingData;
import ru.covariance.optimizationmethods.core.Point;
import ru.covariance.optimizationmethods.core.methods.two.ConjugateGradientMethod;
import ru.covariance.optimizationmethods.core.methods.two.FastestDescentMethod;
import ru.covariance.optimizationmethods.core.methods.two.GradientMethod;

public class BenchmarkMain {

  public static class Counter implements ToDoubleFunction<Point> {

    private final ToDoubleFunction<Point> inner;
    private int counter = 0;

    public Counter(ToDoubleFunction<Point> inner) {
      this.inner = inner;
    }

    public int getCounter() {
      return counter;
    }

    public void resetCounter() {
      counter = 0;
    }

    @Override
    public double applyAsDouble(Point value) {
      counter++;
      return inner.applyAsDouble(value);
    }
  }

  public static class CounterGrad implements UnaryOperator<Point> {

    private final UnaryOperator<Point> inner;
    private int counter = 0;

    public CounterGrad(UnaryOperator<Point> inner) {
      this.inner = inner;
    }

    public int getCounter() {
      return counter;
    }

    public void resetCounter() {
      counter = 0;
    }

    @Override
    public Point apply(Point point) {
      counter++;
      return inner.apply(point);
    }
  }

  public static int calculateGrad(int n, int k) {
    final FunctionGeneratingData data = RandomCardinalityFunctionGen.gen(n, k);

    double[] leftArr = new double[n];
    Arrays.fill(leftArr, -100.);
    Point left = new Point(leftArr);

    double[] rightArr = new double[n];
    Arrays.fill(rightArr, 100.);
    Point right = new Point(rightArr);

    CounterGrad c = new CounterGrad(data.getGradient());
    new FastestDescentMethod(left, right, data.getFunction(), c, data.getQuadraticForm()).min();
    return c.getCounter();
  }

  public static int calculateCounts(int n, int k) {
    final FunctionGeneratingData data = RandomCardinalityFunctionGen.gen(n, k);

    double[] leftArr = new double[n];
    Arrays.fill(leftArr, -100.);
    Point left = new Point(leftArr);

    double[] rightArr = new double[n];
    Arrays.fill(rightArr, 100.);
    Point right = new Point(rightArr);

    Counter c = new Counter(data.getFunction());
    new FastestDescentMethod(left, right, c, data.getGradient(), data.getQuadraticForm()).min();
    System.out.println(n + " " + k);
    return c.getCounter();
  }

  public static class Recorder implements ToDoubleFunction<Point> {

    public static class FunctionCall {

      double[] coords;

      public FunctionCall(Point pnt) {
        this.coords = Arrays.copyOf(pnt.getCoordinates(), pnt.getCoordinates().length);
      }

      @Override
      public String toString() {
        return "(" + Arrays.stream(coords).mapToObj(i -> String.format("%.4f", i))
            .collect(Collectors.joining("; ")) + ")";
      }
    }

    private final ToDoubleFunction<Point> inner;
    private final List<FunctionCall> calls = new ArrayList<>();

    public Recorder(ToDoubleFunction<Point> inner) {
      this.inner = inner;
    }

    @Override
    public double applyAsDouble(Point value) {
      calls.add(new FunctionCall(value));
      return inner.applyAsDouble(value);
    }

    public List<FunctionCall> getCalls() {
      return calls;
    }

    public void clear() {
      calls.clear();
    }
  }

  public static class RecorderGrad implements UnaryOperator<Point> {

    public static class FunctionCall {

      double[] coords;

      public FunctionCall(Point pnt) {
        this.coords = Arrays.copyOf(pnt.getCoordinates(), pnt.getCoordinates().length);
      }

      @Override
      public String toString() {
        return "(" + Arrays.stream(coords).mapToObj(i -> String.format("%.4f", i))
            .collect(Collectors.joining("; ")) + ")";
      }
    }

    private final UnaryOperator<Point> inner;
    private final List<FunctionCall> calls = new ArrayList<>();

    public RecorderGrad(UnaryOperator<Point> inner) {
      this.inner = inner;
    }

    @Override
    public Point apply(Point point) {
      calls.add(new FunctionCall(point));
      return inner.apply(point);
    }

    public List<FunctionCall> getCalls() {
      return calls;
    }

    public void clear() {
      calls.clear();
    }
  }


  public static void forMinimizer(Recorder recorder, RecorderGrad recorderGrad,
                                  AbstractFlatIterativeMinimizer minimizer) {
    int i = 0;
    System.out.print(
        "\\begin{center}\n\\begin{tabular}{|c|c|c|c|c|c|}\n\\hline\n Номер итерации & Текущая точка & Количество вызовов функции & Количество вызовов градиента & $\\alpha$\\\\\n\\hline\n");
    while (!minimizer.converged()) {
      System.out.printf("%s & %s & %s & %s & %.04f\\\\\n\\hline\n",
          i,
          new FunctionCall(minimizer.getCurrentPoint()).toString(),
          (long) recorder.getCalls().size(),
          (long) recorderGrad.getCalls().size(),
          ((GradientMethod) minimizer).alpha);
      recorder.clear();
      recorderGrad.clear();
      minimizer.iterate();
      i++;
    }
    System.out.printf("%s & %s & %s & %s & %.04f\\\\\n\\hline\n",
        i,
        new FunctionCall(minimizer.getCurrentPoint()).toString(),
        (long) recorder.getCalls().size(),
        (long) recorderGrad.getCalls().size(),
        ((GradientMethod) minimizer).alpha);
    recorder.clear();
    recorderGrad.clear();
    minimizer.iterate();
    System.out.print("\\end{tabular}\n\\end{center}");
  }

  public static void calculateIterationValues(ToDoubleFunction<Point> f, UnaryOperator<Point> grad,
                                              double[] form) {
    Recorder recorder = new Recorder(f);
    RecorderGrad recorderGrad = new RecorderGrad(grad);

    double[] leftArr = new double[2];
    Arrays.fill(leftArr, -20.);
    Point left = new Point(leftArr);

    double[] rightArr = new double[2];
    Arrays.fill(rightArr, 20.);
    Point right = new Point(rightArr);

    forMinimizer(recorder, recorderGrad,
        new GradientMethod(left, right, recorder, recorderGrad, form));
  }

  public static void main(String[] args) {
//    System.out.println("[[" + IntStream.of(2, 3, 4, 5, 10, 100, 1000).mapToObj(
//        n -> IntStream.range(1, 20).mapToObj(k -> calculateCounts(n, k))
//            .map(i -> Integer.toString(i)).collect(Collectors.joining(", "))
//    ).collect(Collectors.joining("], [")) + "]]");

    calculateIterationValues(MainController.func1, MainController.grad1, MainController.form1);
  }
}
