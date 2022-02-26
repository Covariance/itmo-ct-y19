package expression.parser;

import expression.AbstractBinaryOperator;
import expression.CommonGenericExpression;

public interface BinOpsCreator<T> {
    AbstractBinaryOperator<T> create(CommonGenericExpression<T> first, CommonGenericExpression<T> second);
}
