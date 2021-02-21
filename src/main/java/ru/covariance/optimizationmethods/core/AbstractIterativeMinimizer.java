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
    return left + (right - left) / 2;
  }

  @Override
  public Node display() {
    NumberAxis xAxis = new NumberAxis();
    xAxis.setLabel("x");
    NumberAxis yAxis = new NumberAxis();
    yAxis.setLabel("y");
    LineChart<Number, Number> graphic = new LineChart<>(xAxis, yAxis);
    Series<Number, Number> series = new Series<>();
    series.getData().add(new Data<>(left, 0));
    series.getData().add(new Data<>(right, 0));
    graphic.getData().add(series);
    return graphic;
  }
}
