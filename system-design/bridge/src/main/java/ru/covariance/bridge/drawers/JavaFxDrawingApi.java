package ru.covariance.bridge.drawers;

import javafx.application.Application;
import javafx.scene.Group;
import javafx.scene.Scene;
import javafx.scene.canvas.Canvas;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.paint.Color;
import javafx.stage.Stage;
import ru.covariance.bridge.geometry.Circle;
import ru.covariance.bridge.geometry.Point;

public final class JavaFxDrawingApi extends Application implements DrawingApi {
  public final static int DEFAULT_HEIGHT = 720;
  public final static int DEFAULT_WIDTH = 1280;
  private final int width;
  private final int height;
  private Stage primaryStage;
  private final Canvas canvas;
  private final GraphicsContext gc;


  public JavaFxDrawingApi(final int width, final int height) {
    this.width = width;
    this.height = height;
    this.canvas = new Canvas(width, height);
    this.gc = canvas.getGraphicsContext2D();
  }

  public JavaFxDrawingApi() {
    this(DEFAULT_WIDTH, DEFAULT_HEIGHT);
  }

  @Override
  public void start(final Stage primaryStage) {
    this.primaryStage = primaryStage;
  }

  @Override
  public long getDrawingAreaWidth() {
    return this.width;
  }

  @Override
  public long getDrawingAreaHeight() {
    return this.height;
  }

  @Override
  public void drawCircle(final Circle circle) {
    this.gc.setFill(Color.LAVENDER);
    this.gc.fillOval(circle.center().x() - circle.radius(),
        circle.center().y() - circle.radius(),
        circle.radius() * 2,
        circle.radius() * 2);
  }

  @Override
  public void drawLine(final Point from, final Point to) {
    this.gc.strokeLine(from.x(), from.y(), to.x(), to.y());
  }

  @Override
  public void show() {
    final Group root = new Group();
    root.getChildren().add(this.canvas);
    this.primaryStage.setScene(new Scene(root));
    this.primaryStage.show();
  }
}
