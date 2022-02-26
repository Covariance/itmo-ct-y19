package mnkGame;

import java.util.List;

public final class MnkEngine {
    private MnkPosition realPosition;

    private final static List<Cell> ORDER = List.of(
            Cell.CROSS,
            Cell.ZERO,
            Cell.STICK,
            Cell.MINUS
    );

    public MnkEngine(MnkPosition realPosition) {
        this.realPosition = realPosition;
    }

    public MnkPosition processPosition(int index) {
        return new MnkPosition(realPosition);
    }

    public MoveResult processMove(Move move, int playerIndex) {
        if (realPosition.isValidMove(move) && move.getType() == ORDER.get(playerIndex)) {
            realPosition.fetch(move);
            realPosition.print();
            return this.checkState(move);
        }
        return MoveResult.CHEATING;
    }

    private int countDir(int x, int y, int dx, int dy) {
        Cell type = realPosition.getCell(x, y);
        int res = 0;
        while (realPosition.isInnerPoint(x + (res + 1) * dx, y + (res + 1) * dy) && realPosition.getCell(x + (res + 1) * dx, y + (res + 1) * dy) == type) {
            res++;
        }
        return res;
    }

    private boolean isWon(int x, int y, int dx, int dy) {
        return countDir(x, y, dx, dy) + countDir(x, y, -dx, -dy) + 1 >= realPosition.getK();
    }

    private MoveResult checkState(Move move) {
        int x = move.getRow(), y = move.getColumn();
        Cell type = move.getType();
        if (isWon(x, y, 0, 1)
                || isWon(x, y, 1, 0)
                || isWon(x, y, 1, 1)
                || isWon(x, y, -1, 1)
        ) {
            return MoveResult.WIN;
        }

        if (realPosition.getN() * realPosition.getM() == realPosition.getNumberOfTurns()) {
            return MoveResult.DRAW;
        }

        return MoveResult.UNKNOWN;
    }

    public Cell getPlayerType(int playerIndex) {
        return ORDER.get(playerIndex);
    }
}
