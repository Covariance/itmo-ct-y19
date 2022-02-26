package expression.parser;

import expression.AbstractUnaryOperator;
import expression.CommonGenericExpression;

public final class UnaryOperatorExemplar<T> {
    private final UnOpsCreator<T> creator;
    private final String sign;

    public UnaryOperatorExemplar(UnOpsCreator<T> creator, String sign) {
        this.creator = creator;
        this.sign = sign;
    }

    public char getPrefix() {
        return sign.charAt(0);
    }

    public String getContinuation() {
        return sign.substring(1);
    }

    public AbstractUnaryOperator<T> create(CommonGenericExpression<T> operand) {
        return creator.create(operand);
    }
}
