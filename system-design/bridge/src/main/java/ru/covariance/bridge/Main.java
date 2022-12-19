package ru.covariance.bridge;

import ru.covariance.bridge.drawers.AwtDrawingApi;
import ru.covariance.bridge.drawers.DrawingApi;
import ru.covariance.bridge.drawers.JavaFxDrawingApi;
import ru.covariance.bridge.graphs.Graph;
import ru.covariance.bridge.graphs.ListGraph;
import ru.covariance.bridge.graphs.MatrixGraph;

import java.util.function.Function;

public final class Main {
  private static void printHelp(final String error) {
    System.out.println("Incorrect usage: " + error + "\n" +
        "Usage: java GraphDrawer <graph_type> <drawing_api>");
  }

  public static void main(String[] args) {
    if (args == null) {
      printHelp("args are null");
      return;
    }
    if (args.length != 2) {
      printHelp("incorrect number of args");
    }

    DrawingApi drawingApi;
    switch (args[0]) {
      case "awt" -> drawingApi = new AwtDrawingApi();
      case "jfx" -> drawingApi = new JavaFxDrawingApi();
      default -> {printHelp("unrecognized drawing api"); return;}
    }

    Graph graph;
    switch (args[1]) {
      case "list" -> graph = new ListGraph(drawingApi);
      case "matrix" -> graph = new MatrixGraph(drawingApi);
      default -> {printHelp("unrecognized graph type"); return;}
    }

    graph.drawGraph();
    drawingApi.show();
  }
}