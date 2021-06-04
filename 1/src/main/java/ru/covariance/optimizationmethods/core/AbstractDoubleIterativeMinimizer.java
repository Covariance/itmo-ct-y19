package ru.covariance.optimizationmethods.core;

import java.util.List;
import java.util.function.DoubleUnaryOperator;
import java.util.stream.Collectors;
import java.util.stream.DoubleStream;
import javafx.scene.Node;
import javafx.scene.chart.LineChart;
import javafx.scene.chart.NumberAxis;
import javafx.scene.chart.XYChart.Data;
import javafx.scene.chart.XYChart.Series;

public abstract class AbstractDoubleIterativeMinimizer
    extends AbstractIterativeMinimizer<Double>
    implements Displayable {

  protected double left;
  protected double right;
  protected double epsilon = 1e-6;

  public AbstractDoubleIterativeMinimizer(double left, double right, DoubleUnaryOperator f) {
    super(List.of(left, right), f::applyAsDouble);
    this.left = left;
    this.right = right;
  }

  @Override
  public Double getMin() {
    return left + (right - left) / 2;
  }

  @Override
  public boolean converged() {
    return right - left < epsilon;
  }

  public void setEpsilon(double epsilon) {
    this.epsilon = epsilon;
  }

  public double getLeft() {
    return left;
  }

  public double getRight() {
    return right;
  }

  protected class Display {

    private final LineChart<Number, Number> graphic;

    public static final double DELTA_STEP = 1e-4;

    public Display() {
      NumberAxis xAxis = new NumberAxis();
      xAxis.setLabel("x");
      xAxis.setForceZeroInRange(false);
      NumberAxis yAxis = new NumberAxis();
      yAxis.setLabel("y");
      yAxis.setForceZeroInRange(false);
      graphic = new LineChart<>(xAxis, yAxis);
      graphic.setCreateSymbols(false);

      Series<Number, Number> fseries = new Series<>();
      fseries.getData().addAll(
          DoubleStream.iterate(left, x -> x + DELTA_STEP <= right, x -> x + DELTA_STEP)
              .boxed()
              .map(x -> new Data<Number, Number>(x, f.applyAsDouble(x)))
              .collect(Collectors.toList())
      );
      fseries.setName("f");
      addSeries(fseries);
    }

    public void addSeries(Series<Number, Number> series) {
      graphic.getData().add(series);
    }

    public void clearGraphic() {
      graphic.getData().remove(graphic.getData().size() - 1);
    }

    public LineChart<Number, Number> getGraphic() {
      return graphic;
    }
  }

  protected Display display;

  @Override
  public Node display() {
    if (display == null) {
      display = new Display();
    } else {
      display.clearGraphic();
    }
    Series<Number, Number> series = new Series<>();
    series.getData().add(new Data<>(left, f.applyAsDouble(left)));
    series.getData().add(new Data<>(right, f.applyAsDouble(right)));
    series.setName("Текущее приближение");
    display.addSeries(series);
    return display.getGraphic();
  }
}
