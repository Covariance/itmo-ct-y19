module ru.covariance.mythkeeperpackager {
    requires javafx.fxml;
    requires javafx.controls;
    requires javafx.base;
    requires javafx.graphics;

    opens ru.covariance.optimizationmethods.app to javafx.fxml;

    exports ru.covariance.optimizationmethods.app;
    exports ru.covariance.optimizationmethods.core;
}