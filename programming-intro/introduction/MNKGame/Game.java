package mnkGame;

import java.util.List;

public final class Game {
    private final List<Player> players;

    public Game(List<Player> players) {
        this.players = players;
    }

    public GameResult startGame(final MnkEngine engine) {
        int playerIndex = -1;
        MoveResult state;
        do {
            playerIndex = (playerIndex + 1) % players.size();
            Move move = players.get(playerIndex).makeMove(engine.processPosition(playerIndex), engine.getPlayerType(playerIndex));
            state = engine.processMove(move, playerIndex);
        } while (state == MoveResult.UNKNOWN);
        return new GameResult(playerIndex, state);
    }
}
