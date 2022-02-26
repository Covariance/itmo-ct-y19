import java.io.IOException;
import java.util.Arrays;

import java.io.File;
import java.io.IOException;

public class ReverseSort {

    public static void main(String[] args) throws Exception {
        OneCharScanner scan = new OneCharScanner(System.in);
        MatrixLine[] matrix = new MatrixLine[1];
        int[] tmpLineElements = new int[1];
        int i = 0;
        try {
            while (scan.hasNextLine()) {
                OneCharScanner sScan = new OneCharScanner(scan.nextLine());

                int tmpCnt = 0;

                while (sScan.hasNextInt()) {
                    int tmpInt = sScan.nextInt();
                    if (tmpCnt == tmpLineElements.length) {
                        tmpLineElements = Arrays.copyOf(tmpLineElements, 2 * tmpLineElements.length);
                    }
                    tmpLineElements[tmpCnt++] = tmpInt;
                }

                if (i == matrix.length) {
                    matrix = Arrays.copyOf(matrix, 2 * matrix.length);
                }

                matrix[i++] = new MatrixLine(i, tmpLineElements, tmpCnt);
                matrix[i - 1].sortElements();
            }
        } catch (IOException e) {
            System.out.println("I/O error occurred during reading: " + e.getMessage());
        }
        try {
            scan.close();
        } catch (IOException e) {
            System.out.println("I/O error occurred while closing input scanner: " + e.getMessage());
        }

        matrix = Arrays.copyOf(matrix, i);
        Arrays.sort(matrix);

        for (int k = 0; k < i; k++)
        {
            matrix[k].printReversed(System.out);
            System.out.println();
        }

    }
}