package mnkGame;

public final class Move {
    private final int row;
    private final int column;
    private final Cell type;

    public Move(int row, int column, Cell type) {
        this.row = row;
        this.column = column;
        this.type = type;
    }

    public Cell getType() {
        return type;
    }

    public int getColumn() {
        return column;
    }

    public int getRow() {
        return row;
    }
}
