package ru.covariance.bridge.drawers;

import ru.covariance.bridge.geometry.Circle;
import ru.covariance.bridge.geometry.Point;

import java.awt.*;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

public final class AwtDrawingApi implements DrawingApi {
  public final static int THICKNESS = 5;
  public final static int DEFAULT_HEIGHT = 720;
  public final static int DEFAULT_WIDTH = 1280;

  private final int width;
  private final int height;

  private final Graphics2D graphics;

  public AwtDrawingApi(int width, int height) {
    this.width = width;
    this.height = height;

    Frame frame = new Frame();
    frame.addWindowListener(new WindowAdapter() {
      public void windowClosing(WindowEvent we) {
        System.exit(0);
      }
    });
    frame.setSize(width, height);
    frame.setVisible(true);
    this.graphics = (Graphics2D) frame.getGraphics();
    this.graphics.setStroke(new BasicStroke(THICKNESS));
  }

  public AwtDrawingApi() {
    this(DEFAULT_WIDTH, DEFAULT_HEIGHT);
  }

  @Override
  public long getDrawingAreaWidth() {
    return width;
  }

  @Override
  public long getDrawingAreaHeight() {
    return height;
  }

  @Override
  public void drawCircle(final Circle circle) {
    var center = circle.center();
    var radius = circle.radius();
    graphics.setColor(Color.BLUE);
    graphics.fillOval((int) (center.x() - radius), (int) (center.y() - radius), (int) radius * 2, (int) radius * 2);
  }

  @Override
  public void drawLine(final Point from, final Point to) {
    graphics.drawLine((int) from.x(), (int) from.y(), (int) to.x(), (int) to.y());
  }

  @Override
  public void show() {
    // do nothing
  }
}