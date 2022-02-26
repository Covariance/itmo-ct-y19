package mnkGame;

public interface Position {
    int getNumberOfTurns();

    int getN();

    int getM();

    int getK();

    Cell getCell(int i, int j);

    boolean isValidMove(Move move);
}
