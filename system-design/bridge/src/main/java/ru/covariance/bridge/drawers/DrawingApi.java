package ru.covariance.bridge.drawers;

import ru.covariance.bridge.geometry.Circle;
import ru.covariance.bridge.geometry.Point;

public interface DrawingApi {
  long getDrawingAreaWidth();

  long getDrawingAreaHeight();

  void drawCircle(final Circle circle);

  void drawLine(final Point from, final Point to);

  void show();
}