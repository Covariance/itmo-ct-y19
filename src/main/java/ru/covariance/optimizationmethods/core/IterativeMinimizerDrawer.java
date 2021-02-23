package ru.covariance.optimizationmethods.core;

import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Parameter;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Comparator;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.function.DoubleUnaryOperator;
import javafx.scene.control.Button;
import javafx.scene.control.TextField;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.scene.text.Text;

public class IterativeMinimizerDrawer {

  private final Class<? extends AbstractIterativeMinimizer> clazz;
  private final Constructor<? extends AbstractIterativeMinimizer> constructor;
  private final DoubleUnaryOperator f;
  private final VBox anchor;

  private final VBox creation;
  private final VBox running;

  private final VBox drawingField;
  private final Text runningResult;

  private final Map<Parameter, TextField> parameterRetriever = new HashMap<>();

  private AbstractIterativeMinimizer current;

  @SuppressWarnings("unchecked")
  public IterativeMinimizerDrawer(Class<? extends AbstractIterativeMinimizer> clazz,
      DoubleUnaryOperator f, VBox anchor) {
    this.clazz = clazz;
    this.f = f;
    this.anchor = anchor;

    anchor.getChildren().add(new Text(clazz.getSimpleName()));

    constructor = (Constructor<? extends AbstractIterativeMinimizer>) Arrays
        .stream(clazz.getConstructors())
        .max(Comparator.comparingInt(Constructor::getParameterCount)).get();

    creation = new VBox();
    for (Parameter parameter : constructor.getParameters()) {
      if (!parameter.getType().equals(DoubleUnaryOperator.class)) {
        createField(parameter);
      }
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

  private void createField(Parameter parameter) {
    HBox hBox = new HBox();
    hBox.getChildren().add(new Text(parameter.getName() + ": "));
    TextField textField = new TextField();
    parameterRetriever.put(parameter, textField);
    hBox.getChildren().add(textField);

    creation.getChildren().add(hBox);
  }

  private double getParameter(Parameter parameter) {
    try {
      // TODO int
      return Double.parseDouble(parameterRetriever.get(parameter).getText());
    } catch (NumberFormatException ignored) {
      return 0;
    }
  }

  private void createMinimizer() {
    List<Object> parameters = new ArrayList<>();
    for (Parameter parameter : constructor.getParameters()) {
      if (parameter.getType().equals(DoubleUnaryOperator.class)) {
        parameters.add(f);
      } else {
        parameters.add(getParameter(parameter));
      }
    }
    try {
      current = constructor.newInstance(parameters.toArray());
    } catch (InstantiationException | IllegalAccessException | InvocationTargetException ignored) {
      throw new IllegalArgumentException("Can't instantiate drawer");
    }
  }
}
