package expression.parser;

import expression.AbstractUnaryOperator;
import expression.CommonGenericExpression;

public interface UnOpsCreator<T> {
    AbstractUnaryOperator<T> create(CommonGenericExpression<T> expression);
}
