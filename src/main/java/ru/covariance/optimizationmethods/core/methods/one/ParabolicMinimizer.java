package ru.covariance.optimizationmethods.core.methods.one;

import java.util.function.DoubleUnaryOperator;
import java.util.stream.Collectors;
import java.util.stream.DoubleStream;
import javafx.scene.Node;
import javafx.scene.chart.XYChart.Data;
import javafx.scene.chart.XYChart.Series;
import ru.covariance.optimizationmethods.core.AbstractDoubleIterativeMinimizer;

public class ParabolicMinimizer extends AbstractDoubleIterativeMinimizer {

  private static final double DEFAULT_DELTA = 1e-6;

  private double mid;
  private final double delta;
  private boolean converged;

  private double fleft;
  private double fmid;
  private double fright;

  public ParabolicMinimizer(double left, double right, DoubleUnaryOperator f, double delta) {
    super(left, right, f);
    this.mid = (left + right) / 2;
    this.delta = delta;
    this.converged = false;

    this.fleft = f.applyAsDouble(left);
    this.fmid = f.applyAsDouble(mid);
    this.fright = f.applyAsDouble(right);
  }

  public ParabolicMinimizer(double left, double right, DoubleUnaryOperator f) {
    this(left, right, f, DEFAULT_DELTA);
  }

  @Override
  public void iterate() {
    double xopt = mid - ((mid - left) * (mid - left) * (fmid - fright) - (mid - right)
        * (mid - right) * (fmid - fleft)) / (2 * ((mid - left) * (fmid - fright) - (mid - right)
        * (fmid - fleft)));

    if (Math.abs(xopt - mid) < delta) {
      converged = true;
    }

    double fxopt = f.applyAsDouble(xopt);

    if (xopt < mid) {
      if (fxopt < fmid) {
        fright = fmid;
        right = mid;

        fmid = fxopt;
        mid = xopt;
      } else {
        fleft = fxopt;
        left = xopt;
      }
    } else {
      if (fxopt < fmid) {
        fleft = fmid;
        left = mid;

        fmid = fxopt;
        mid = xopt;
      } else {
        fright = fxopt;
        right = xopt;
      }
    }

    if (mid == left || mid == right) {
      converged = true;
    }
  }

  @Override
  public Node display() {
    if (display == null) {
      display = new Display();
    } else {
      display.clearGraphic();
      display.clearGraphic();
    }

    DoubleUnaryOperator par = x -> fleft * (x - mid) * (x - right) / (left - mid) / (left - right)
        + fmid * (x - left) * (x - right) / (mid - left) / (mid - right)
        + fright * (x - left) * (x - mid) / (right - left) / (right - mid);

    Series<Number, Number> series = new Series<>();

    series.getData().addAll(
        DoubleStream
            .iterate(left, x -> x + Display.DELTA_STEP <= right, x -> x + Display.DELTA_STEP)
            .boxed().map(x -> new Data<Number, Number>(x, par.applyAsDouble(x)))
            .collect(Collectors.toList())
    );
    series.setName("Параболическое приближение");

    display.addSeries(series);

    Series<Number, Number> segment = new Series<>();
    segment.getData().add(new Data<>(left, f.applyAsDouble(left)));
    segment.getData().add(new Data<>(right, f.applyAsDouble(right)));
    segment.setName("Текущее приближение");
    display.addSeries(segment);

    return display.getGraphic();
  }

  @Override
  public boolean converged() {
    return converged;
  }

  @Override
  public double getMin() {
    return mid;
  }
}
