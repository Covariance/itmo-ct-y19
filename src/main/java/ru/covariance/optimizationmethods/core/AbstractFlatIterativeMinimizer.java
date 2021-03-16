package ru.covariance.optimizationmethods.core;

import java.util.List;
import java.util.function.ToDoubleFunction;
import java.util.stream.Collectors;
import java.util.stream.DoubleStream;
import javafx.geometry.Point2D;
import javafx.scene.Node;
import javafx.scene.chart.LineChart;
import javafx.scene.chart.NumberAxis;

public abstract class AbstractFlatIterativeMinimizer
    extends AbstractIterativeMinimizer<Point2D>
    implements Displayable {

  protected double leftX;
  protected double rightX;
  protected double leftY;
  protected double rightY;

  public AbstractFlatIterativeMinimizer(double leftX, double rightX, double leftY, double rightY,
      ToDoubleFunction<Point2D> f) {
    super(List.of(new Point2D(leftX, leftY), new Point2D(rightX, rightY)), f);
    this.leftX = leftX;
    this.leftY = leftY;
    this.rightX = rightX;
    this.rightY = rightY;
  }

  protected class Displayer implements Displayable {

    private void addLevelLines() {
      double deltaStepX = (borders.get(1).getX() - borders.get(0).getX()) / 1000;
      double deltaStepY = (borders.get(1).getY() - borders.get(0).getY()) / 1000;
      List<List<Double>> valueMatrix = DoubleStream
          .iterate(
              borders.get(0).getX(),
              x -> x <= borders.get(1).getX(),
              x -> x + deltaStepX)
          .mapToObj(x ->
              DoubleStream
                  .iterate(
                      borders.get(0).getY(),
                      y -> y <= borders.get(1).getY(),
                      y -> y + deltaStepY)
              .mapToObj(y -> f.applyAsDouble(new Point2D(x, y)))
              .collect(Collectors.toList()))
          .collect(Collectors.toList());


    }

    private final LineChart<Number, Number> graphic;

    public Displayer() {
      NumberAxis xAxis = new NumberAxis();
      xAxis.setLabel("x");
      xAxis.setForceZeroInRange(false);
      NumberAxis yAxis = new NumberAxis();
      yAxis.setLabel("y");
      yAxis.setForceZeroInRange(false);
      graphic = new LineChart<>(xAxis, yAxis);
      graphic.setCreateSymbols(false);

      displayer.addLevelLines();
    }

    @Override
    public Node display() {
      return graphic;
    }
  }

  protected Displayer displayer;

  @Override
  public Node display() {
    if (displayer == null) {
      displayer = new Displayer();
    }
    return displayer.display();
  }
}
