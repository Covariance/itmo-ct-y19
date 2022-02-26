package mnkGame.players;

import mnkGame.Cell;
import mnkGame.Move;
import mnkGame.Player;
import mnkGame.MnkPosition;

public class SequentialPlayer implements Player {
    @Override
    public Move makeMove(MnkPosition position, Cell type) {
        for (int i = 0; i < position.getN(); i++) {
            for (int j = 0; j < position.getM(); j++) {
                if (position.isValidMove(new mnkGame.Move(i, j, type))) {
                    return new mnkGame.Move(i, j, type);
                }
            }
        }
        return null;
    }
}
