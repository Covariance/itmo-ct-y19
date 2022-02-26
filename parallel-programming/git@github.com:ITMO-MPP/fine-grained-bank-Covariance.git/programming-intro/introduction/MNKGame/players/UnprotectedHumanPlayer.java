package mnkGame.players;

import mnkGame.Cell;
import mnkGame.Move;
import mnkGame.MnkPosition;

public class UnprotectedHumanPlayer extends HumanPlayer {
    @Override
    public Move makeMove(MnkPosition position, Cell playerType) {
        position.print();
        return new Move(sc.nextInt(), sc.nextInt(), playerType);
    }
}
