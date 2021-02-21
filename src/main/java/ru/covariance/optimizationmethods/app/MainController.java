package ru.covariance.optimizationmethods.app;

import javafx.fxml.FXML;
import javafx.scene.Node;
import javafx.scene.control.Button;
import javafx.scene.control.Control;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.VBox;
import javafx.scene.text.Text;

import java.io.File;
import java.util.HashMap;
import java.util.Map;
import java.util.stream.Collectors;
import ru.covariance.optimizationmethods.core.IterativeDrawer;
import ru.covariance.optimizationmethods.core.methods.TernaryMinimizer;

public class MainController {

  @FXML
  private BorderPane anchor;

  @FXML
  private VBox choiceMenuVBox;

  @FXML
  private Button menuHomeButton;

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
    MainController.registerPage("Ternary", IterativeDrawer.draw(new TernaryMinimizer(-4, 4, x -> x * x)));

    choiceMenuVBox.getChildren().addAll(
        PAGES.keySet().stream()
            .map(this::createMenuButton)
            .collect(Collectors.toList())
    );
  }
}
