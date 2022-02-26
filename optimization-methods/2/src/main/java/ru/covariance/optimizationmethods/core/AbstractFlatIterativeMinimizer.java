package ru.covariance.optimizationmethods.core;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;
import java.util.function.ToDoubleFunction;
import java.util.function.UnaryOperator;

import javafx.scene.Group;
import javafx.scene.Node;
import javafx.scene.paint.Color;
import javafx.scene.shape.Line;
import javafx.scene.shape.Rectangle;
import javafx.scene.text.Text;

public abstract class AbstractFlatIterativeMinimizer
    extends AbstractIterativeMinimizer<Point>
    implements Displayable {

  protected Point left;
  protected Point right;
  private final double leftX;
  private final double leftY;
  private final double rightX;
  private final double rightY;
  protected UnaryOperator<Point> gradient;
  protected double[] quadraticForm;
  protected double epsilon = 1e-6;

  public AbstractFlatIterativeMinimizer(Point left, Point right, ToDoubleFunction<Point> f, UnaryOperator<Point> gradient, double[] quadraticForm) {
    super(f);
    this.left = left;
    this.right = right;
    this.gradient = gradient;
    this.quadraticForm = quadraticForm;

    this.leftX = left.getX();
    this.leftY = left.getY();
    this.rightX = right.getX();
    this.rightY = right.getY();
  }

  protected class Displayer implements Displayable {

    private static final int DELTA_X_PARTITION = 500;
    private static final int DELTA_Y_PARTITION = 500;
    private static final int LINE_COUNT = 20;
    private static final double CANVAS_WIDTH = 400;
    private static final double CANVAS_HEIGHT = 400;
    private static final double CANVAS_SHIFT = 10;
    private final Group canvas = new Group();

    private Arrow currentDirection = null;

    private void addLevelLines() {
      double deltaStepX = (rightX - leftX) / DELTA_X_PARTITION;
      double deltaStepY = (rightY - leftY) / DELTA_Y_PARTITION;

      List<Point> points = new ArrayList<>();
      for (int i = 0; i < DELTA_X_PARTITION; i++) {
        for (int j = 0; j < DELTA_Y_PARTITION; j++) {
          double x = leftX + deltaStepX * (i + 0.5);
          double y = leftY + deltaStepY * (j + 0.5);
          points.add(new Point(x, y));
        }
      }

      points.sort(Comparator.comparing(f::applyAsDouble));

      Color maxColor = new Color(1, 0.3, 0, 1);
      Color minColor = new Color(0, 0.5, 1, 1);

      for (int i = 0; i < LINE_COUNT; i++) {
        double alpha = i * 1.0 / (LINE_COUNT - 1);
        Color curColor = new Color(
                minColor.getRed() + (maxColor.getRed() - minColor.getRed()) * alpha,
                minColor.getGreen() + (maxColor.getGreen() - minColor.getGreen()) * alpha,
                minColor.getBlue() + (maxColor.getBlue() - minColor.getBlue()) * alpha,
                minColor.getBrightness() + (maxColor.getBrightness() - minColor.getBrightness()) * alpha
        );
        for (int j = points.size() / LINE_COUNT * i; j < (int)(points.size() / LINE_COUNT * (i + 0.1)); j++) {
          Rectangle rectangle = new Rectangle(
              getRealX(points.get(j).getX() - deltaStepX / 2), getRealY(points.get(j).getY() - deltaStepY / 2),
              getRealWidth(deltaStepX), getRealHeight(deltaStepY)
          );
          rectangle.setFill(curColor);
          canvas.getChildren().add(rectangle);
        }
      }
    }

    private double getRealX(double x) {
      return getRealWidth(x - leftX) + CANVAS_SHIFT;
    }

    private double getRealWidth(double x) {
      x /= (rightX - leftX);
      x = Math.max(0, Math.min(x, 1)) * CANVAS_WIDTH;
      return x;
    }

    private double getRealY(double y) {
      return getRealHeight(rightY - y) + CANVAS_SHIFT;
    }

    private double getRealHeight(double y) {
      y /= (rightY - leftY);
      y = Math.max(0, Math.min(y, 1)) * CANVAS_HEIGHT;
      return y;
    }

    public Displayer() {
      for (int x = (int) Math.ceil(leftX); x <= Math.floor(rightX); x += Math.ceil((rightX - leftX) / 10)) {
        Line line = new Line(getRealX(x), CANVAS_SHIFT, getRealX(x), CANVAS_HEIGHT + CANVAS_SHIFT);
        line.setStrokeWidth(0.3);
        canvas.getChildren().add(line);
        canvas.getChildren().add(new Text(getRealX(x) - 10, CANVAS_HEIGHT + CANVAS_SHIFT + 20, Integer.toString(x)));
      }
      for (int y = (int) Math.ceil(leftY); y <= Math.floor(rightY); y += Math.ceil((rightY - leftY) / 10)) {
        Line line = new Line(CANVAS_SHIFT, getRealY(y), CANVAS_WIDTH + CANVAS_SHIFT, getRealY(y));
        line.setStrokeWidth(0.3);
        canvas.getChildren().add(line);
        canvas.getChildren().add(new Text(CANVAS_WIDTH + CANVAS_SHIFT + 10, getRealY(y) + 10, Integer.toString(y)));
      }
      this.addLevelLines();
    }

    @Override
    public Node display() {
      return canvas;
    }

    public void iterate(Point currentPoint, Point previousPoint) {
      Arrow arrow = new Arrow(getRealX(previousPoint.getX()), getRealY(previousPoint.getY()),
              getRealX(currentPoint.getX()), getRealY(currentPoint.getY()));
      canvas.getChildren().add(arrow);
      if (resetDirections()) {
        canvas.getChildren().remove(currentDirection);
      }
      currentDirection = new Arrow(getRealX(currentPoint.getX()), getRealY(currentPoint.getY()),
              getRealX(getDirection().getX()), getRealY(getDirection().getY()));
      currentDirection.setFill(Color.GREEN);
      canvas.getChildren().add(currentDirection);
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

  @Override
  public void iterate() {
    if (displayer != null) {
      displayer.iterate(getCurrentPoint(), getPreviousPoint());
    }
  }

  public abstract Point getCurrentPoint();

  public abstract Point getPreviousPoint();

  public Point getDirection() {
    return gradient.apply(getCurrentPoint()).multiply(-1);
  }

  protected boolean resetDirections() {
    return true;
  }
}
