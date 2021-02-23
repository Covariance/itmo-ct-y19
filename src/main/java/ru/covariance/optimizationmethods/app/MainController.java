package ru.covariance.optimizationmethods.app;

import java.util.HashMap;
import java.util.Map;
import java.util.function.DoubleUnaryOperator;
import java.util.stream.Collectors;
import javafx.fxml.FXML;
import javafx.scene.Node;
import javafx.scene.control.Button;
import javafx.scene.control.Control;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.VBox;
import ru.covariance.optimizationmethods.core.IterativeMinimizerDrawer;
import ru.covariance.optimizationmethods.core.methods.BrentMinimizer;
import ru.covariance.optimizationmethods.core.methods.DichotomyMinimizer;
import ru.covariance.optimizationmethods.core.methods.FibonacciMinimizer;
import ru.covariance.optimizationmethods.core.methods.GoldenRatioMinimizer;
import ru.covariance.optimizationmethods.core.methods.ParabolicMinimizer;

public class MainController {

  @FXML
  private BorderPane anchor;

  @FXML
  private VBox choiceMenuVBox;

  @FXML
  private BorderPane homePage;

  private static final Map<String, Node> PAGES = new HashMap<>();

  public static void registerPage(final String pageName, final Node page) {
    if (pageName == null) {
      return;
    }
    PAGES.put(pageName, page);
  }

  private void setPage(final String pageName) {
    if (pageName == null) {
      anchor.setCenter(homePage);
    }
    Node page = PAGES.get(pageName);
    if (page == null) {
      anchor.setCenter(homePage);
    } else {
      anchor.setCenter(page);
    }
  }

  @FXML
  void onMouseClickedMenuHouseButton(MouseEvent event) {
    setPage(null);
  }

  private Button createMenuButton(final String pageName) {
    Button btn = new Button();
    btn.setMaxWidth(Control.USE_COMPUTED_SIZE);
    btn.setMaxHeight(Control.USE_COMPUTED_SIZE);
    btn.setPrefWidth(200);
    btn.setPrefHeight(50);
    btn.setMaxWidth(Control.USE_COMPUTED_SIZE);
    btn.setMaxHeight(Control.USE_COMPUTED_SIZE);

    btn.setStyle("-fx-border-color : gray;" +
        "-fx-border-width: 0 0 2px 0;" +
        "-fx-border-radius: 0;" +
        "-fx-background-color: transparent;");

    btn.setText(pageName);
    btn.onMouseClickedProperty().set(mouseEvent -> setPage(pageName));
    return btn;
  }

  @FXML
  void initialize() {
    DoubleUnaryOperator f = x -> x * Math.sin(x) + 2 * Math.cos(x);

    VBox dichotomyAnchor = new VBox();
    registerPage("Dichotomy", dichotomyAnchor);
    new IterativeMinimizerDrawer(DichotomyMinimizer.class, f, dichotomyAnchor);

    VBox fibonacciAnchor = new VBox();
    registerPage("Fibonacci", fibonacciAnchor);
    new IterativeMinimizerDrawer(FibonacciMinimizer.class, f, fibonacciAnchor);

    VBox goldenAnchor = new VBox();
    registerPage("Golden Ratio", goldenAnchor);
    new IterativeMinimizerDrawer(GoldenRatioMinimizer.class, f, goldenAnchor);

    VBox parabolicAnchor = new VBox();
    registerPage("Parabolic", parabolicAnchor);
    new IterativeMinimizerDrawer(ParabolicMinimizer.class, f, parabolicAnchor);

    VBox brentAnchor = new VBox();
    registerPage("Brent", brentAnchor);
    new IterativeMinimizerDrawer(BrentMinimizer.class, f, brentAnchor);

    choiceMenuVBox.getChildren().addAll(
        PAGES.keySet().stream()
            .map(this::createMenuButton)
            .collect(Collectors.toList())
    );
  }
}
