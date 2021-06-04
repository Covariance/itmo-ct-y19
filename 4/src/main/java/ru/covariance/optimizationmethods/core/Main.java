package ru.covariance.optimizationmethods.core;

import ru.covariance.optimizationmethods.core.methods.four.*;
import ru.covariance.optimizationmethods.core.methods.two.FastestDescentMethod;

import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;
import java.util.Collections;
import java.util.List;
import java.util.Random;
import java.util.function.DoubleToLongFunction;
import java.util.function.Function;
import java.util.function.ToDoubleFunction;
import java.util.function.UnaryOperator;
import java.util.stream.Collectors;

public class Main {
    private static double pow(double x, int p) {
        double px = 1;
        while (p-- > 0) {
            px *= x;
        }
        return px;
    }

    private static final FunctionGeneratingData SIMPLE_DATA_1 =
            new FunctionGeneratingData(
                    p -> pow(p.x() - 5, 2) + pow(p.y() - 10, 2),
                    p -> new Point(2 * p.x() - 10, 2 * p.y() - 20),
                    p -> new Matrix(new Point(2, 0), new Point(0, 2)
                    )
            );

    private static final FunctionGeneratingData SIMPLE_DATA_2 =
            new FunctionGeneratingData(
                    p -> pow(p.x(), 3) * p.y() + 5 * pow(p.x() * p.y(), 2) + pow(p.x() - 5, 4) + pow(p.y() + 2, 4),
                    p -> new Point(3 * pow(p.x(), 2) * p.y() + 10 * p.x() * pow(p.y(), 2) + 4 * pow(p.x() - 5, 3),
                                   pow(p.x(), 3) + 10 * pow(p.x(), 2) * p.y() + 4 * pow(p.y() + 2, 3)),
                    p -> new Matrix(
                            new Point(6 * p.x() * p.y() + 10 * p.y() * p.y() + 12 * pow(p.x() - 5, 2),
                                      3 * p.x() * p.x() + 20 * p.x() * p.y()),
                            new Point(3 * p.x() * p.x() + 20 * p.x() * p.y(),
                                      20 * p.x() * p.x() + 12 * pow(p.y() + 2, 2)
                            )
                    )
            );

    private static final FunctionGeneratingData SIMPLE_DATA_3 =
            new FunctionGeneratingData(
                    p -> pow(p.x() - 5, 6) + 100 * pow(p.y() - 2, 6) + pow(p.z() + 3, 4),
                    p -> new Point(6 * pow(p.x() - 5, 5), 600 * pow(p.y() - 2, 5), 4 * pow(p.z() + 3, 3)),
                    p -> new Matrix(
                            new Point(30 * pow(p.x() - 5, 4), 0, 0),
                            new Point(0, 3000 * pow(p.y() - 2, 4), 0),
                            new Point(0, 0, 12 * pow(p.z() + 3, 2))
                    )
            );

    private static final FunctionGeneratingData EXAMPLE_1 =
            new FunctionGeneratingData(
                    p -> pow(p.x(), 2) + pow(p.y(), 2) - 1.2 * p.x() * p.y(),
                    p -> new Point(2 * p.x() - 1.2 * p.y(), 2 * p.y() - 1.2 * p.x()),
                    p -> new Matrix(
                            new Point(2, -1.2),
                            new Point(-1.2, 2)
                    )
            );

    private static final FunctionGeneratingData EXAMPLE_2 =
            new FunctionGeneratingData(
                    p -> 100 * pow(p.y() - pow(p.x(), 2), 2) + pow(1 - p.x(), 2),
                    p -> new Point(400 * pow(p.x(), 3) - 400 * p.x() * p.y() + 2 * p.x() - 2,
                                   200 * p.y() - 200 * pow(p.x(), 2)),
                    p -> new Matrix(
                            new Point(1200 * pow(p.x(), 2) - 400 * p.y() + 2, -400 * p.x()),
                            new Point(-400 * p.x(), 200)
                    )
            );

    private static final FunctionGeneratingData TRICKY_2 =
            new FunctionGeneratingData(
                    p -> pow(pow(p.x(), 2) + p.y() - 11, 2) + pow(p.x() + pow(p.y(), 2) - 7, 2),
                    p -> new Point(p.x() * (4 * pow(p.x(), 2) + 4 * p.y() - 42) + 2 * pow(p.y(), 2) - 14,
                                   2 * pow(p.x(), 2) + p.y() * (4 * p.x() + 4 * pow(p.y(), 2) - 26) - 22),
                    p -> new Matrix(
                            new Point(12 * pow(p.x(), 2) + 4 * p.y() - 42,
                                      4 * (p.x() + p.y())),
                            new Point(4 * (p.x() + p.y()),
                                      12 * pow(p.y(), 2) + 4 * p.x() - 26))
            );

    private static final FunctionGeneratingData TRICKY_3 =
            new FunctionGeneratingData(
                    p -> pow(p.x() + 10 * p.y(), 2) + 5 * pow(p.z() - p.t(), 2) + pow(p.y() - 2 * p.z(), 4) + 10 * pow(p.x() - p.t(), 4),
                    p -> new Point(40 * pow(p.x() - p.t(), 3) + 2 * p.x() + 20 * p.y(),
                                   20 * (p.x() + 10 * p.y()) + 4 * pow(p.y() - 2 * p.z(), 3),
                                   -10 * p.t() - 8 * pow(p.y(), 3) + 48 * pow(p.y(), 2) * p.z() - 96 * p.y() * pow(p.z(), 2) + 64 * pow(p.z(), 3) + 10 * p.z(),
                                   -40 * pow(p.x() - p.t(), 3) + 10 * p.t() - 10 * p.z()),
                    p -> new Matrix(
                            new Point(120 * pow(p.x() - p.t(), 2) + 1, 20, 0, -120 * pow(p.x() - p.t(), 2)),
                            new Point(20, 12 * pow(p.y() - 2 * p.z(), 2) + 200, -24 * pow(p.y() - 2 * p.z(), 2), 0),
                            new Point(0, -24 * pow(p.y() - 2 * p.z(), 2), 48 * pow(p.y() - 2 * p.z(), 2) + 10, -10),
                            new Point(-120 * pow(p.x() - p.t(), 2), 0, -10, 120 * pow(p.x() - p.t(), 2) + 10)
                    )
            );

    private static final FunctionGeneratingData TRICKY_4 =
            new FunctionGeneratingData(
                    p -> 100 - 2 / (1 + pow((p.x() - 1) / 2, 2) + pow((p.y() - 1) / 3, 2)) - 1 / (1 + pow((p.x() - 2) / 2, 2) + pow((p.y() - 1) / 3, 2)),
                    p -> new Point((p.x() - 2) / (2 * pow(pow(p.x() - 2, 2) / 4 + pow(p.y() - 1, 2) / 9 + 1, 2)) + (p.x() - 1) / pow(pow(p.x() - 1, 2) / 4 + pow(p.y() - 1, 2) / 9 + 1, 2),
                                   2 * (p.y() - 1) / (9 * pow(pow(p.x() - 2, 2) / 4 + pow(p.y() - 1, 2) / 9 + 1, 2)) + 4 * (p.y() - 1) / (9 * pow(pow(p.x() - 1, 2) / 4 + pow(p.y() - 1, 2) / 9 + 1, 2))),
                    p -> new Matrix(
                            new Point(
                                    -1296 * (27 * pow(p.x(), 2) - 54 * p.x() - 4 * pow(p.y(), 2) + 8 * p.y() - 13) / pow(9 * pow(p.x(), 2) - 18 * p.x() + 4 * pow(p.y(), 2) - 8 * p.y() + 49, 3) - 648 * (27 * pow(p.x(), 2) - 108 * p.x() - 4 * (pow(p.y(), 2) - 2 * p.y() - 17)) / pow(9 * pow(p.x(), 2) - 36 * p.x() + 4 * (pow(p.y(), 2) - 2 * p.y() + 19), 3),
                                    10368 * (p.y() - 1) * (((2 - p.x()) / pow((9 * (p.x() - 4) * p.x() + 4 * (p.y() - 2) * p.y() + 76), 3)) - ((2 * p.x() - 2) / pow(9 * (p.x() - 2) * p.x() + 4 * (p.y() - 2) * p.y() + 49, 3)))
                            ),
                            new Point(
                                    10368 * (p.y() - 1) * (((2 - p.x()) / pow((9 * (p.x() - 4) * p.x() + 4 * (p.y() - 2) * p.y() + 76), 3)) - ((2 * p.x() - 2) / pow(9 * (p.x() - 2) * p.x() + 4 * (p.y() - 2) * p.y() + 49, 3))),
                                    1728 * (3 * p.x() * p.x() - 6 * p.x() - 4 * p.y() * p.y() + 8 * p.y() + 11) / pow(9 * p.x() * p.x() - 18 * p.x() + 4 * p.y() * p.y() - 8 * p.y() + 49, 3) + 864 * (3 * p.x() * p.x() - 12 * p.x() - 4 * (p.y() * p.y() - 2 * p.y() - 5)) / pow(9 * p.x() * p.x() - 36 * p.x() + 4 * (p.y() * p.y() - 2 * p.y() + 19), 3)
                            )
                    )
            );

    private static FunctionGeneratingData generate(final int n) {
        ToDoubleFunction<Point> function = p -> {
            double s = 0;
            for (int i = 0; i + 1 < n; i++) {
                s += 100 * pow(p.get(i + 1) - pow(p.get(i), 2), 2) + pow(1 - p.get(i), 2);
            }
            return s;
        };
        UnaryOperator<Point> gradient = p -> {
            Point s = new Point(new double[n]);
            for (int i = 0; i < n - 1; i++) {
                s.set(2 * (200 * pow(p.get(i), 3) - 200 * p.get(i) * p.get(i + 1) + p.get(i) - 1), i);
            }
            for (int i = 1; i < n; i++) {
                s.set(s.get(i) + 200 * (p.get(i) - pow(p.get(i - 1), 2)), i);
            }
            return s;
        };
        Function<Point, Matrix> gessian = p -> {
            Matrix a = new Matrix(n);
            for (int i = 0; i < n - 1; i++) {
                a.set(i, i, a.get(i, i) + 1200 * pow(p.get(i), 2) - 400 * p.get(i + 1) + 2);
                a.set(i, i + 1, -400 * p.get(i));
                a.set(i + 1, i, -400 * p.get(i));
                a.set(i + 1, i + 1, 200);
            }
            return a;
        };

        return new FunctionGeneratingData(function, gradient, gessian);
    }

    private static int N = 100;

    public static void main(final String[] args) {
//        test(NewtonMethod.class);
//        test(NewtonMethod1DMinimization.class);
//        for (Point p : new Point[]{new Point(), new Point(3, 3), new Point(-5, 0)}) {
//            System.out.printf("Начальное приближение (%s)%n", p.toString());
//            System.out.println("\\begin{tabular}{|c|c|}");
//            System.out.println("\\hline");
//            System.out.println("Метод & Итерации \\\\");
//            test(NewtonMethodDirectionResolveMinimization.class, "с направлением спуска", p);
//            test(FletcherMethod.class, "Давидона-Флетчера-Пауэлла", p);
//            test(PawelMethod.class, "Пауэлла", p);
        for (int j = 0; j < 2; j++) {
            Point p = new Point(new double[N]);
            Random r = new Random(1);
            for (int i = 0; i < N; i++) {
                if (j == 0) {
                    p.set(0, i);
                } else {
                    p.set(r.nextDouble(), i);
                }
            }
            test(NewtonMethodDirectionResolveMinimization.class, p, "с направлением спуска, " + (j == 0 ? "начало координат" : "случайное приближение"));
        }
    }

    private static void testConsumer(final Constructor<?> constructor, final FunctionGeneratingData data, final Point p, String name) {
        try {
            final Object method = constructor.newInstance(data.getFunction(), data.getGradient(), data.getGessian(), p);
            Integer iters = (Integer) method.getClass().getMethod("test").invoke(method);
//            System.out.println("\\hline");
            System.out.printf("%s & %d%n\\\\", name, iters);
        } catch (final InstantiationException | IllegalAccessException | InvocationTargetException | NoSuchMethodException e) {
            e.printStackTrace();
        }
    }

    private static void test(Class<?> clazz, Point p, String name) {
        try {
            final Constructor<?> c = clazz.getConstructor(ToDoubleFunction.class, UnaryOperator.class, Function.class, Point.class);

            testConsumer(c, generate(N), p, name);
        } catch (final NoSuchMethodException e) {
            e.printStackTrace();
        }
    }

    private static void testFastestDescent() {
        System.out.println("\\hline");
        System.out.printf("наискорейший спуск (1) & %d \\\\%n", new FastestDescentMethod(new Point(4, 1), EXAMPLE_1.getFunction(), EXAMPLE_1.getGradient()).test());
        System.out.println("\\hline");
        System.out.printf("наискорейший спуск (2) & %d \\\\%n", new FastestDescentMethod(new Point(-1.2, 1), EXAMPLE_2.getFunction(), EXAMPLE_2.getGradient()).test());
    }
}
