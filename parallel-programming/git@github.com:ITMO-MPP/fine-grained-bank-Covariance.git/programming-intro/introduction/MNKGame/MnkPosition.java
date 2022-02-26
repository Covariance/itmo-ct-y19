package mnkGame;

public final class MnkPosition implements Position {
    private final int n, m, k;
    private int numberOfTurns;
    private Cell[][] field;

    public MnkPosition(int n, int m, int k) {
        this.n = n;
        this.m = m;
        this.k = k;
        this.field = new Cell[n][m];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                this.field[i][j] = Cell.EMPTY;
            }
        }
        this.numberOfTurns = 0;
    }

    public MnkPosition(MnkPosition position) {
        this(position.getN(), position.getM(), position.getK());
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                this.field[i][j] = position.getCell(i, j);
            }
        }
        this.numberOfTurns = position.getNumberOfTurns();
    }

    @Override
    public int getNumberOfTurns() {
        return numberOfTurns;
    }

    @Override
    public int getN() {
        return n;
    }

    @Override
    public int getM() {
        return m;
    }

    @Override
    public int getK() {
        return k;
    }

    @Override
    public Cell getCell(int i, int j) {
        return field[i][j];
    }

    private Character Interpret(Cell type) {
        switch (type) {
            case EMPTY:
                return '.';
            case CROSS:
                return 'X';
            case ZERO:
                return 'O';
            case MINUS:
                return '-';
            case STICK:
                return '|';
        }
        return null;
    }

    @Override
    public boolean isValidMove(Move move) {
        return isInnerPoint(move.getRow(), move.getColumn()) && field[move.getRow()][move.getColumn()] == Cell.EMPTY;
    }

    public boolean isInnerPoint(int x, int y) {
        return 0 <= x && x < n && 0 <= y && y < m;
    }

    public void fetch(Move move) {
        field[move.getRow()][move.getColumn()] = move.getType();
        numberOfTurns++;
    }

    public void print() {
        int maxLenN = Integer.toString(this.n).length() + 1, maxLenM = Integer.toString(this.m).length() + 1;
        System.out.println("Current position is:");
        for (int l = 0; l < maxLenN; l++) System.out.print(' ');
        for (int i = 0; i < m; i++) {
            for (int l = 0; l < maxLenM - Integer.toString(i).length(); l++) System.out.print(' ');
            System.out.print(i);
        }
        System.out.println();
        for (int i = 0; i < n; i++) {
            for (int l = 0; l < maxLenN - Integer.toString(i).length(); l++) System.out.print(' ');
            System.out.print(i);
            for (int j = 0; j < m; j++) {
                for (int l = 0; l < maxLenM - 1; l++) System.out.print(' ');
                System.out.print(Interpret(field[i][j]));
            }
            System.out.println();
        }
    }
}
