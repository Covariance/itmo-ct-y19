package mnkGame.players;

import mnkGame.Cell;
import mnkGame.Move;
import mnkGame.Player;
import mnkGame.MnkPosition;

import java.util.Random;

public class RandomPlayer implements Player {
    private final Random random;

    public RandomPlayer(long seed) {
        this.random = new Random(seed);
    }

    public RandomPlayer() {
        this.random = new Random();
    }

    @Override
    public Move makeMove(MnkPosition position, Cell type) {
        int n = position.getN(), m = position.getM();
        int i = random.nextInt(n),
                j = random.nextInt(m);
        while (!position.isValidMove(new Move(i, j, type))) {
            i = random.nextInt(n);
            j = random.nextInt(m);
        }
        return new mnkGame.Move(i, j, type);
    }
}
