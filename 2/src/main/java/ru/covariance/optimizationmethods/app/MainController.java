package ru.covariance.optimizationmethods.app;

import java.util.function.ToDoubleFunction;
import java.util.function.UnaryOperator;

import javafx.fxml.FXML;
import javafx.scene.Node;
import javafx.scene.control.Button;
import javafx.scene.control.Control;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.VBox;
import ru.covariance.optimizationmethods.core.FunctionGeneratingData;
import ru.covariance.optimizationmethods.core.IterativeMinimizerDrawer;
import ru.covariance.optimizationmethods.core.Point;
import ru.covariance.optimizationmethods.core.methods.two.ConjugateGradientMethod;
import ru.covariance.optimizationmethods.core.methods.two.FastestDescentMethod;
import ru.covariance.optimizationmethods.core.methods.two.GradientMethod;

import java.util.HashMap;
import java.util.Map;
import java.util.stream.Collectors;

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

  // (x + 3)^2 + (y − 10)^2 + 1
  public static final ToDoubleFunction<Point> func1 = p -> (p.getX() + 3) * (p.getX() + 3) + (p.getY() - 10) * (p.getY() - 10) + 1;
  public static final UnaryOperator<Point> grad1 = p -> new Point(2 * p.getX() + 6, 2 * p.getY() - 20);
  public static final double[] form1 = new double[]{2, 2};

  // (x − 10)^2 + y − 3
  public static final ToDoubleFunction<Point> func3 = p -> (p.getValue(0) - 10) * (p.getValue(0) - 10) + p.getValue(1) - 3;
  public static final UnaryOperator<Point> grad3 = p -> new Point(2 * p.getX() - 20, 1);
  public static final double[] form3 = new double[]{2, 0};

  // @stepavly
  public static final ToDoubleFunction<Point> func4 = p -> (p.getX() - 10) * (p.getX() - 10) + 5 * (p.getY() - 4) * (p.getY() - 4);
  public static final UnaryOperator<Point> grad4 = p -> new Point(2 * (p.getX() - 10), 10 * (p.getY() - 4));
  public static final double[] form4 = new double[]{2, 10};

  // @korsun
  public static final ToDoubleFunction<Point> func5 = p -> (p.getX() - 10) * (p.getX() - 10) + 250 * (p.getY() - 10) * (p.getY() - 10);
  public static final UnaryOperator<Point> grad5 = p -> new Point(2 * p.getX() - 20, 500 * p.getY() - 5000);
  public static final double[] form5 = new double[]{2, 500};

  public static final ToDoubleFunction<Point> func6 = p -> p.getX() * p.getX() / 13.689181889 + p.getY() * p.getY() / 1.214718466 - 1;
  public static final UnaryOperator<Point> grad6 = p -> new Point(2 * p.getX() / 13.689181889, 2 * p.getY() / 1.214718466);
  public static final double[] form6 = new double[]{2 / 13.689181889, 2 / 1.214718466};


  public static final ToDoubleFunction<Point> func7 = p -> p.getX() * p.getX() + p.getY() * p.getY();
  public static final UnaryOperator<Point> grad7 = p -> new Point(2 * p.getX(), 2 * p.getY());
  public static final double[] form7 = new double[]{2, 500};

  private static FunctionGeneratingData getTargetFunction() {
    return new FunctionGeneratingData(func1, grad1, form1);
  }

  @FXML
  void initialize() {
    final FunctionGeneratingData data = getTargetFunction();

    VBox conjugateAnchor = new VBox();
    registerPage("Conjugate", conjugateAnchor);
    new IterativeMinimizerDrawer(ConjugateGradientMethod.class, data, conjugateAnchor);

    VBox gradientBox = new VBox();
    registerPage("Gradient", gradientBox);
    new IterativeMinimizerDrawer(GradientMethod.class, data, gradientBox);


    VBox descentBox = new VBox();
    registerPage("Descent", descentBox);
    new IterativeMinimizerDrawer(FastestDescentMethod.class, data, descentBox);

    choiceMenuVBox.getChildren().addAll(
        PAGES.keySet().stream()
            .map(this::createMenuButton)
            .collect(Collectors.toList())
    );
  }
}
