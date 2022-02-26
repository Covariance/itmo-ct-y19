package search;

import java.util.Arrays;

/**
 * @author Pavel Martynov (git: CovarianceMomentum)
 */

public class BinarySearchMissing {
    // pre:
    // args.length >= 1
    // && \forall i = 0...args.length - 1: args[i] is Integer
    // && \forall i = 1...args.length - 2: int(args[i]) <= int(args[i + 1])
    // && if
    public static void main(String[] args) {
        // pre
        int x = Integer.parseInt(args[0]);
        // pre && x == int(args[0])
        int[] arr = new int[args.length - 1];
        // -""- && arr.length == args.length - 1
        int i = 0;
        // -""- && i = 0
        // Inv: pre && forall j \in [0; i) arr[i] = int(args[i + 1])
        while (i < arr.length) {
            // Inv &&
            arr[i] = Integer.parseInt(args[i + 1]);
            i++;
        }
        System.out.println(missingBinarySearch(x, arr));
    }
    // post:
    // i: x >= arr[i] && !\exists j < i: x >= arr[j]
    // i printed

    static int missingBinarySearch(int x, int[] arr) {
        int r = BinarySearch.iterativeBinarySearch(x, arr);
        if (r == arr.length || arr[r] != x) {
            return -r-1;
        } else {
            return r;
        }
    }
}
