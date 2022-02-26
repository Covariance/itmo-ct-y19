package expression.parser;

import expression.AbstractUnaryOperator;
import expression.CommonExpression;

public interface UnOpsCreator {
    AbstractUnaryOperator create(CommonExpression operand);
}
