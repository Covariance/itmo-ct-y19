package ru.covariance.optimizationmethods.core;

import java.util.function.Supplier;
import javafx.scene.Node;
import javafx.scene.layout.VBox;

public class IterativeMinimizerDrawer {

  private final Supplier<AbstractIterativeMinimizer> abstractIterativeMinimizerSupplier;
  private final VBox anchor;

  public IterativeMinimizerDrawer(Supplier<AbstractIterativeMinimizer> supplier) {
    this.abstractIterativeMinimizerSupplier = supplier;
    this.anchor = new VBox();
  }

  public Node anchor() {
    return anchor;
  }
}
