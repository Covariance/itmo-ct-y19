package expression.parser;

import expression.AbstractBinaryOperator;
import expression.CommonExpression;

public final class BinaryOperatorExemplar {
    private final BinOpsCreator creator;
    private final String sign;

    public BinaryOperatorExemplar(BinOpsCreator creator, String sign) {
        this.creator = creator;
        this.sign = sign;
    }

    public char getPrefix() {
        return sign.charAt(0);
    }

    public String getContinuation() {
        return sign.substring(1);
    }

    public AbstractBinaryOperator create(CommonExpression first, CommonExpression second) {
        return creator.create(first, second);
    }
}
