package mnkGame.players;

import mnkGame.Cell;
import mnkGame.Move;
import mnkGame.Player;
import mnkGame.MnkPosition;

public class MirrorPlayer implements Player {
    private final RandomPlayer lastHope = new RandomPlayer();
    @Override
    public Move makeMove(MnkPosition position, Cell playerType) {
        int n = position.getN(), m = position.getM();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (position.isValidMove(new Move(n - i - 1, m - j - 1, playerType))) {
                    return new Move(n - i - 1, m - j - 1, playerType);
                }
            }
        }
        return lastHope.makeMove(position, playerType);
    }
}
