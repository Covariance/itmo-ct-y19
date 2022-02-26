package expression.exceptions;

import expression.CommonExpression;
import expression.exceptions.calculating.CalculateException;
import expression.exceptions.parsing.ParserException;
import expression.parser.ExpressionParser;
import expression.parser.Parser;

import java.util.Scanner;

/**
 * @author Pavel Martynov (git: CovarianceMomentum)
 */

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        Parser parser = new ExpressionParser();
        CommonExpression expression;
        try {
             expression = parser.parse(scanner.nextLine());
        } catch(ParserException e) {
            System.err.println("Exception while parsing given expression: " + e.getMessage());
            return;
        }
        System.out.println("Parsed expression: " + expression.toMiniString());
        System.out.println("x\t\tf");
        for (int i = -10; i <= 10; i++) {
            StringBuilder result = new StringBuilder(i + " ".repeat(7 - Integer.toString(i).length()));
            try {
                result.append(expression.evaluate(i));
            } catch (CalculateException e) {
                result.append(e.getMessage());
            }
            System.out.println(result.toString());
        }
    }
}
