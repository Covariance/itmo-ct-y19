package ru.covariance.optimizationmethods.core;

import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;
import java.util.Arrays;
import java.util.Comparator;
import java.util.HashMap;
import java.util.Map;

import javafx.scene.control.Button;
import javafx.scene.control.TextField;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.scene.text.Text;

public class IterativeMinimizerDrawer {

  private final Constructor<? extends AbstractFlatIterativeMinimizer> constructor;
  private final FunctionGeneratingData data;
  private final VBox anchor;

  private final VBox creation;
  private final VBox running;

  private final VBox drawingField;
  private final Text runningResult;

  private final Map<String, TextField> parameterRetriever = new HashMap<>();

  private AbstractFlatIterativeMinimizer current;

  @SuppressWarnings("unchecked")
  public IterativeMinimizerDrawer(Class<? extends AbstractFlatIterativeMinimizer> clazz,
                                  final FunctionGeneratingData data, VBox anchor) {
    this.data = data;
    this.anchor = anchor;

    anchor.getChildren().add(new Text(clazz.getSimpleName()));

    //noinspection OptionalGetWithoutIsPresent
    constructor = (Constructor<? extends AbstractFlatIterativeMinimizer>) Arrays
        .stream(clazz.getConstructors())
        .max(Comparator.comparingInt(Constructor::getParameterCount)).get();

    creation = new VBox();
    String[] parameterNames = new String[]{
        "Left X", "Right X", "Left Y", "Right Y"
    };

    int parameterIndex = 0;
    for (String parameter : parameterNames) {
      createField(parameter, parameterNames[parameterIndex++]);
    }

    Button runButton = new Button();
    runButton.setText("Run");
    runButton.setOnMouseClicked(mouseEvent -> run());

    creation.getChildren().add(runButton);

    running = new VBox();

    drawingField = new VBox();
    running.getChildren().add(drawingField);

    runningResult = new Text();
    running.getChildren().add(runningResult);

    HBox runningButtons = new HBox();

    Button nextStepButton = new Button();
    nextStepButton.setText("Next");
    nextStepButton.setOnMouseClicked(mouseEvent -> nextStep());
    runningButtons.getChildren().add(nextStepButton);

    Button minimizeButton = new Button();
    minimizeButton.setText("Minimize");
    minimizeButton.setOnMouseClicked(mouseEvent -> minimize());
    runningButtons.getChildren().add(minimizeButton);

    Button resetButton = new Button();
    resetButton.setText("Reset");
    resetButton.setOnMouseClicked(mouseEvent -> reset());
    runningButtons.getChildren().add(resetButton);

    running.getChildren().add(runningButtons);

    anchor.getChildren().add(creation);
  }

  private void reset() {
    anchor.getChildren().remove(running);
    anchor.getChildren().add(creation);
  }

  private void run() {
    createMinimizer();
    runningResult.setText("");
    drawingField.getChildren().clear();
    drawingField.getChildren().add(current.display());
    anchor.getChildren().remove(creation);
    anchor.getChildren().add(running);
  }

  private void nextStep() {
    if (!current.converged()) {
      current.iterate();
      drawingField.getChildren().clear();
      drawingField.getChildren().add(current.display());
      if (current.converged()) {
        runningResult.setText("result: " + current.min());
      }
    }
  }

  private void minimize() {
    if (!current.converged()) {
      runningResult.setText("result: " + current.min());
      drawingField.getChildren().clear();
      drawingField.getChildren().add(current.display());
    }
  }

  private void createField(String parameter, String parameterName) {
    HBox hBox = new HBox();
    hBox.getChildren().add(new Text(parameterName + ": "));
    TextField textField = new TextField();
    parameterRetriever.put(parameter, textField);
    hBox.getChildren().add(textField);

    creation.getChildren().add(hBox);
  }

  private double getDoubleParameter(String s) {
    try {
      return Double.parseDouble(parameterRetriever.get(s).getText());
    } catch (NumberFormatException ignored) {
      return 0;
    }
  }

  private void createMinimizer() {
    try {
      current = constructor.newInstance(
          new Point(new double[]{getDoubleParameter("Left X"), getDoubleParameter("Left Y")}),
          new Point(new double[]{getDoubleParameter("Right X"), getDoubleParameter("Right Y")}),
          data.getFunction(),
          data.getGradient(),
          data.getQuadraticForm()
      );
    } catch (InstantiationException | InvocationTargetException | IllegalAccessException ignored) {
    }
  }
}
