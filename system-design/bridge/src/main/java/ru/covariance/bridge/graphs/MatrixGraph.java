package ru.covariance.bridge.graphs;

import ru.covariance.bridge.drawers.DrawingApi;

import java.util.List;
import java.util.Scanner;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public final class MatrixGraph extends Graph {
  private final List<List<Boolean>> matrix;
  public MatrixGraph(final List<List<Boolean>> matrix, final DrawingApi drawingApi) {
    super(drawingApi);
    if (!matrix.isEmpty() && matrix.size() != matrix.get(0).size()) {
      throw new IllegalArgumentException("Matrix should be square");
    }
    this.matrix = matrix;
  }

  public MatrixGraph(DrawingApi drawingApi) {
    this(readMatrix(), drawingApi);
  }

  private static List<List<Boolean>> readMatrix() {
    try (final Scanner scanner = new Scanner(System.in)) {
      final int vertexCount = scanner.nextInt();
      return Stream.generate(() -> 0)
          .limit(vertexCount)
          .map(i -> Stream.generate(() -> 0)
              .limit(vertexCount)
              .map(j -> scanner.nextBoolean())
              .collect(Collectors.toList()))
          .collect(Collectors.toList());
    }
  }

  @Override
  protected void drawEdges() {
    Stream.iterate(0, k -> k + 1)
        .limit(this.verticesCount())
        .forEach(i -> Stream.iterate(0, k -> k + 1)
            .limit(this.verticesCount())
            .filter(j -> this.matrix.get(i).get(j))
            .forEach(j -> drawEdge(i, j)));
  }

  @Override
  protected int verticesCount() {
    return this.matrix.size();
  }
}
