package search;

/**
 * @author Pavel Martynov (git: CovarianceMomentum)
 */

public class BinarySearch {
    // pre:
    // args.length >= 1
    // && \forall i = 0...args.length - 1: args[i] is Integer
    // && \forall i = 1...args.length - 2: int(args[i]) >= int(args[i + 1])
    public static void main(String[] args) {
        // pre
        int x = Integer.parseInt(args[0]);
        // pre && x == int(args[0])
        int[] arr = new int[args.length - 1];
        // -""- && arr.length == args.length - 1
        int i = 0;
        // -""- && i = 0
        // Inv: pre && \forall j \in [0; i): arr[j] == int(args[j + 1])
        while (i < arr.length) {
            // Inv && i < arr.length = args.length - 1 => (args[i + 1] != null && args[i + 1] is Integer)
            arr[i] = Integer.parseInt(args[i + 1]);
            // -""- && arr[i] == int(args[i + 1])
            i++;
            // Inv
        }
        // \forall i = 1...args.length - 2: int(args[i]) >= int(args[i + 1]) && \forall j in [0; arr.length): arr[j] == int(args[j + 1])
        System.out.println(recursiveBinarySearch(x, arr, -1, arr.length));
    }
    // post:
    // i: x >= arr[i] && !\exists j < i: x >= arr[j]
    // i printed

    // pre:
    // \forall i = 0...arr.length - 2: arr[i] >= arr[i + 1]
    // (define as A)
    static int iterativeBinarySearch(int x, int[] arr) {
        int l = -1, r = arr.length;
        // A && l == -1 && r == arr.length

        // Inv: A && (l == -1 || arr[l] > x) && (r == arr.length || arr[r] <= x) && l > -2 && r < arr.length + 1 && l < r && r - l
        while (l < r - 1) {
            // Inv && r - l > 1
            int m = l + (r - l) / 2;
            // Inv && l < m < r => 0 <= m <= arr.length - 1 => arr[m] exists
            if (arr[m] > x) {
                // Inv && arr[m] exists && l < m < r && arr[m] > x
                // // (arr[m] > x && m != l) => (arr[m] > x && m > -1) => arr[m] > x && m > -2 && m < r
                l = m;
            } else {
                // Inv && arr[m] exists && l < m < r && arr[m] <= x
                // // (arr[m] <= x && m != r) => (arr[m] <= x && m < arr.length) => arr[m] <= x && m < arr.length + 1 && l < m
                r = m;
            }
            // Inv && |l' - r'| < |l - r|
        }
        // A && (l == -1 || arr[l] > x) && (r == arr.length || arr[r] <= x) && l > -2 && r < arr.length + 1 && l == r - 1
        // A && (r == 0 || arr[r - 1] > x) && (r == arr.length || arr[r] <= x) && -1 < r < arr.length + 1
        // |arr.length == 0  =>  r == arr.length  =>  arr not contains x && [x] is sorted
        // |arr.length != 0  =>  | r == arr.length  =>  arr[arr.length - 1] > x  =>  arr not contains x && arr[:] + x is sorted
        // |                     | r != arr.length  =>  arr[r] <= x  =>  | r == 0  =>  | arr[0] == x  =>  arr contains x && !\exists i < r: arr[i] > x
        // |                     |                                       |             | arr[0] != x  =>  arr not contains x && x + arr[:] is sorted
        // |                     |                                       | r > 0  =>  arr[r - 1] > x && arr[r] <= x  =>  | arr[r] == x  =>  arr contains x && !\exists i < r: arr[i] > x
        // |                     |                                       |                                               | arr[r] != x  =>  arr not contains x && arr[:r] + x + arr[r:] is sorted
        // (define as B)
        return r;
    }
    // post:
    // A &&
    // R == first insertion pos of x in arr:
    // arr contains x => R: !\exists i < R: arr[i] > x
    // arr !contains x => R: (arr[:R] + x + arr[R:]) is sorted




    // pre:
    // \forall i = 0...arr.length - 2: arr[i] >= arr[i + 1]
    // && (l == -1 || arr[l] > x) && (r == arr.length || arr[r] <= x) && l > -2 && r < arr.length + 1 && l < r
    // (define as C)
    static int recursiveBinarySearch(int x, int[] arr, int l, int r) {
        if (l >= r - 1) {
            // C && l >= r - 1  =>  B
            return r;
        } else {
            // C && r - l > 1
            int m = l + (r - l) / 2;
            // C && l < m < r => 0 <= m <= arr.length - 1 => arr[m] exists
            if (arr[m] > x) {
                // C && arr[m] exists && l < m < r && arr[m] > x
                // // (arr[m] > x && m != l) => (arr[m] > x && m > -1) => arr[m] > x && m > -2 && m < r && r - m < r - l
                return recursiveBinarySearch(x, arr, m, r);
                // C &&
                // R == first insertion pos of x in (arr' = arr[m:r]):
                // arr' contains x => R: !\exists i < R: arr'[i] > x
                // arr' !contains x => R: (arr'[:R] + x + arr'[R:]) is sorted
            } else {
                // C && arr[m] exists && l < m < r && arr[m] <= x
                // // (arr[m] <= x && m != r) => (arr[m] <= x && m < arr.length) => arr[m] <= x && m < arr.length + 1 && l < m && m - l < r - l
                return recursiveBinarySearch(x, arr, l, m);
                // C &&
                // R == first insertion pos of x in (arr' = arr[l:m]):
                // arr' contains x => R: !\exists i < R: arr'[i] > x
                // arr' !contains x => R: (arr'[:R] + x + arr'[R:]) is sorted
            }
        }
    }
    // post:
    // A &&
    // R == first insertion pos of x in (arr' = arr[l:r]):
    // arr' contains x => R: !\exists i < R: arr'[i] > x
    // arr' !contains x => R: (arr'[:R] + x + arr'[R:]) is sorted
}
