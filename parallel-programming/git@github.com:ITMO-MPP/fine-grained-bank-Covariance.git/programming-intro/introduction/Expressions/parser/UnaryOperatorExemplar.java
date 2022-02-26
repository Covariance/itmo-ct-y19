package expression.parser;

import expression.AbstractUnaryOperator;
import expression.CommonExpression;

import java.util.function.Function;

public final class UnaryOperatorExemplar {
    private final Function<CommonExpression, AbstractUnaryOperator> creator;
    private final String sign;

    public UnaryOperatorExemplar(Function<CommonExpression, AbstractUnaryOperator> creator, String sign) {
        this.creator = creator;
        this.sign = sign;
    }

    public char getPrefix() {
        return sign.charAt(0);
    }

    public String getContinuation() {
        return sign.substring(1);
    }

    public AbstractUnaryOperator create(CommonExpression operand) {
        return creator.apply(operand);
    }
}
