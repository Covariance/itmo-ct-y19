package ru.covariance.optimizationmethods.core.methods;

import ru.covariance.optimizationmethods.core.AbstractIterativeMinimizer;

import java.util.Arrays;
import java.util.function.DoubleUnaryOperator;

import static java.lang.Math.abs;

public class BrentMinimizer extends AbstractIterativeMinimizer {
    private final double K = (3.0 - Math.sqrt(5)) / 2;
    private double minX, secondMinX, prevSecondMinX, minVal, secondMinVal, prevSecondMinVal, curLen, prevLen;

    public BrentMinimizer(double left, double right, DoubleUnaryOperator f) {
        super(left, right, f);
        minX = secondMinX = prevSecondMinX = left + K * (right - left);
        minVal = secondMinVal = prevSecondMinVal = f.applyAsDouble(minX);
        curLen = prevLen = right - left;
    }

    @Override
    public void iterate() {
        double g = prevLen;
        prevLen = curLen;
        double tol = EPSILON * abs(minX) + EPSILON / 10;
        if (abs(minX - (left + right) / 2) + (right - left) / 2 < 2 * tol + EPSILON) {
            return;
        }

        boolean isParabolaAccepted = false;
        double parabolaMinX = 0;
        if (areDistinct(minX, secondMinX, prevSecondMinX) && areDistinct(minVal, secondMinVal, prevSecondMinVal)) {
            // TODO: Insert: parabolaMinX = (parabola's approximation)
            if (left - EPSILON < parabolaMinX && parabolaMinX < right + EPSILON && abs(parabolaMinX - minX) < g / 2) {
                isParabolaAccepted = true;
                if (parabolaMinX - left < 2 * tol || right - parabolaMinX < 2 * tol) {
                    parabolaMinX = minX - Math.signum(minX - (left + right) / 2) * tol;
                }
            }
        }

        if (!isParabolaAccepted) {
            if (minX < (left + right) / 2) {
                parabolaMinX = minX + K * (right - minX);
                prevLen = right - minX;
            } else {
                parabolaMinX = minX - K * (minX - left);
                prevLen = minX - left;
            }
        }

        if (abs(parabolaMinX - minX) < tol) {
            parabolaMinX = minX + Math.signum(parabolaMinX - minX) * tol;
        }
        curLen = abs(parabolaMinX - minX);

        double f_u = super.f.applyAsDouble(parabolaMinX);
        if (f_u < minVal + EPSILON) {
            if (parabolaMinX + EPSILON > minX) {
                left = minX;
            } else {
                right = minX;
            }
            parabolaMinX = secondMinX;
            secondMinX = minX;
            minX = parabolaMinX;
            prevSecondMinVal = secondMinVal;
            secondMinVal = minVal;
            minVal = f_u;
        } else {
            if (parabolaMinX + EPSILON > minX) {
                right = parabolaMinX;
            } else {
                left = parabolaMinX;
            }
            if (f_u < secondMinVal + EPSILON || abs(secondMinX - minX) < EPSILON) {
                prevSecondMinX = secondMinX;
                secondMinX = parabolaMinX;
                prevSecondMinVal = secondMinVal;
                secondMinVal = f_u;
            } else if (abs(prevSecondMinX - minX) < EPSILON || abs(prevSecondMinX - secondMinX) < EPSILON) {
                prevSecondMinX = parabolaMinX;
                prevSecondMinVal = f_u;
            }
        }
    }

    private static boolean areDistinct(double... vals) {
        Arrays.sort(vals);
        for (int i = 1; i < vals.length; i++) {
            if (abs(vals[i] - vals[i - 1]) < EPSILON) {
                return false;
            }
        }
        return true;
    }
}
