package mnkGame.players;

import mnkGame.Cell;
import mnkGame.Move;
import mnkGame.Player;
import mnkGame.MnkPosition;

import java.util.Scanner;

public class HumanPlayer implements Player {

    protected final Scanner sc = new Scanner(System.in);

    @Override
    public mnkGame.Move makeMove(MnkPosition position, Cell playerType) {
        System.out.println("It's your turn, player " + playerType + ". Current position is:");
        position.print();
        int row, column;
        boolean firstTry = true;
        do {
            if (!firstTry) {
                System.out.println("Incorrect move, try again.");
            }
            firstTry = false;

            System.out.println("Enter row:");
            while (!sc.hasNextInt()) {
                System.out.println("Incorrect input, enter row again.");
                sc.next();
            }
            row = sc.nextInt();

            System.out.println("Enter column:");
            while (!sc.hasNextInt()) {
                System.out.println("Incorrect input, enter column again.");
                sc.next();
            }
            column = sc.nextInt();
        } while (!position.isValidMove(new Move(row, column, playerType)));
        return new Move(row, column, playerType);
    }
}
