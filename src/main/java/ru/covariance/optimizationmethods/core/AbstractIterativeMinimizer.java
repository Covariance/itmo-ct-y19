package ru.covariance.optimizationmethods.core;

import java.util.function.DoubleUnaryOperator;
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

  protected static class Display {
    private final NumberAxis xAxis = new NumberAxis();
    private final NumberAxis yAxis = new NumberAxis();
    private final LineChart<Number, Number> graphic;

    public Display() {
      xAxis.setLabel("x");
      yAxis.setLabel("y");
      graphic = new LineChart<>(xAxis, yAxis);
    }

    public void addSeries(Series<Number, Number> series) {
      graphic.getData().add(series);
    }

    public void clearGraphic() {
      graphic.getData().clear();
    }

    public LineChart<Number, Number> getGraphic() {
      return graphic;
    }
  }

  private final Display display = new Display();

  @Override
  public Node display() {
    display.clearGraphic();
    Series<Number, Number> series = new Series<>();
    series.getData().add(new Data<>(left, f.applyAsDouble(left)));
    series.getData().add(new Data<>(right, f.applyAsDouble(right)));
    display.addSeries(series);
    return display.getGraphic();
  }
}
