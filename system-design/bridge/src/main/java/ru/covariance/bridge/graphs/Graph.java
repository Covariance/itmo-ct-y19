package ru.covariance.bridge.graphs;

import ru.covariance.bridge.drawers.DrawingApi;
import ru.covariance.bridge.geometry.Circle;
import ru.covariance.bridge.geometry.Point;

import java.util.stream.Stream;

public abstract class Graph {
  /**
   * Bridge to drawing api
   */
  protected DrawingApi drawingApi;

  public Graph(DrawingApi drawingApi) {
    this.drawingApi = drawingApi;
  }

  public void drawGraph() {
    Stream.iterate(0, i -> i + 1).limit(verticesCount()).forEach(this::drawVertex);
    drawEdges();
  }

  protected abstract void drawEdges();

  protected abstract int verticesCount();

  protected void drawEdge(int from, int to) {
    final Point fromPoint = getVertexPoint(from);
    final Point toPoint = getVertexPoint(to);
    drawingApi.drawLine(fromPoint, toPoint);
  }

  private void drawVertex(int vertex) {
    final Point center = getVertexPoint(vertex);
    final int radius = 20;
    drawingApi.drawCircle(new Circle(center, radius));
  }

  private Point getVertexPoint(int vertex) {
    final long gridSide = (long) Math.ceil(Math.sqrt(verticesCount()));
    return new Point((float) (vertex % gridSide + 1) * drawingApi.getDrawingAreaWidth() / (gridSide + 1),
        (float) (vertex / gridSide + 1) * drawingApi.getDrawingAreaHeight() / (gridSide + 1));
  }
}
