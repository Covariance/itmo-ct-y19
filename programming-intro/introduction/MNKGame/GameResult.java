package mnkGame;

public final class GameResult {
    private final int playerNum;
    private final MoveResult result;

    public GameResult(int playerNum, MoveResult result) {
        this.playerNum = playerNum;
        this.result = result;
    }

    public int getPlayerNum() {
        return playerNum;
    }

    public MoveResult getResult() {
        return result;
    }

    @Override
    public String toString() {
        return "Player " + playerNum + " finished the game with " + result;
    }
}
