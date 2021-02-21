package ru.covariance.optimizationmethods.core;

import javafx.scene.Node;
import javafx.scene.control.Slider;
import javafx.scene.layout.VBox;

public class IterativeDrawer {
  public static Node draw(AbstractIterativeMinimizer minimizer) {
    VBox container = new VBox();
    container.getChildren().add(minimizer.display());
    container.getChildren().add(new Slider());
    return container;
  }
}
