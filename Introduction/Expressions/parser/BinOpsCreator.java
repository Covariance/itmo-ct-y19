package expression.parser;

import expression.AbstractBinaryOperator;
import expression.CommonExpression;

public interface BinOpsCreator {
    AbstractBinaryOperator create(CommonExpression first, CommonExpression second);
}
