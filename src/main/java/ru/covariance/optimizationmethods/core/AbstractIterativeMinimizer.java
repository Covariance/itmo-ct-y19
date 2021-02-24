package ru.covariance.optimizationmethods.core;

import java.util.function.DoubleUnaryOperator;
import java.util.stream.Collectors;
import java.util.stream.DoubleStream;
import javafx.scene.Node;
import javafx.scene.chart.LineChart;
import javafx.scene.chart.NumberAxis;
import javafx.scene.chart.XYChart.Data;
import javafx.scene.chart.XYChart.Series;

public abstract class AbstractIterativeMinimizer extends AbstractMinimizer implements Displayable {

  public AbstractIterativeMinimizer(double left, double right, DoubleUnaryOperator f) {
    super(left, right, f);
  }

  public abstract void iterate();

  @Override
  public double min() {
    while (!this.converged()) {
      iterate();
    }
    return getMin();
  }

  @Override
  public double getMin() {
    return left + (right - left) / 2;
  }

  protected class Display {

    private final NumberAxis xAxis = new NumberAxis();
    private final NumberAxis yAxis = new NumberAxis();
    private final LineChart<Number, Number> graphic;

    private final Series<Number, Number> fseries;

    public static final double DELTA_STEP = 1e-4;

    public Display() {
      xAxis.setLabel("x");
      yAxis.setLabel("y");
      graphic = new LineChart<>(xAxis, yAxis);
      graphic.setCreateSymbols(false);

      fseries = new Series<>();
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
