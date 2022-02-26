package expression.parser;

import expression.AbstractBinaryOperator;
import expression.CommonGenericExpression;

public final class BinaryOperatorExemplar<T> {
    private final BinOpsCreator<T> creator;
    private final String sign;

    public BinaryOperatorExemplar(BinOpsCreator<T> creator, String sign) {
        this.creator = creator;
        this.sign = sign;
    }

    public char getPrefix() {
        return sign.charAt(0);
    }

    public String getContinuation() {
        return sign.substring(1);
    }

    public AbstractBinaryOperator<T> create(CommonGenericExpression<T> first, CommonGenericExpression<T> second) {
        return creator.create(first, second);
    }
}
