package ru.covariance.bridge.graphs;

import ru.covariance.bridge.drawers.DrawingApi;

import java.util.List;
import java.util.Scanner;
import java.util.stream.Collectors;
import java.util.stream.IntStream;
import java.util.stream.Stream;

public final class ListGraph extends Graph {
  private final List<ListGraphEdge> edges;

  public ListGraph(final List<ListGraphEdge> edges, final DrawingApi drawingApi) {
    super(drawingApi);
    this.edges = edges;
  }

  public ListGraph(final DrawingApi drawingApi) {
    this(readEdges(), drawingApi);
  }

  private static List<ListGraphEdge> readEdges() {
    try (final Scanner scanner = new Scanner(System.in)) {
      final int edgeCount = scanner.nextInt();
      return Stream.generate(() -> 0)
          .limit(edgeCount)
          .map(i -> new ListGraphEdge(scanner.nextInt(), scanner.nextInt()))
          .collect(Collectors.toList());
    }
  }

  @Override
  public void drawEdges() {
    this.edges.forEach(edge -> drawEdge(edge.from(), edge.to()));
  }

  @Override
  protected int verticesCount() {
    return this.edges.stream().flatMapToInt(edge -> IntStream.of(edge.from(), edge.to())).max().orElse(0);
  }
}
