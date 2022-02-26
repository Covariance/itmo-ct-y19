package search;

/**
 * @author Pavel Martynov (git: CovarianceMomentum)
 */
public class BinarySearchShift {
    private final static boolean RECURSIVE = true;
    // pre:
    // for i in 0...args.length : args[i] is Integer
    // && \forall i, j in args: i != j
    // && \exists i: int(args[i:]) + int(args[:i]) is sorted
    public static void main(String[] args) {
        // pre1 = pre

        if (args.length == 0) {
            System.out.println(0);
            return;
        }
        // pre1 && args.length > 0

        int[] arr = new int[args.length];
        // arr.length == args.length

        int i = 0;
        // pre1 && arr.length == args.length > 0
        // Inv(i): for j in [0; i) : arr[i] == int(args[i])
        while (i < args.length) {
            // pre1 && arr.length == args.length > 0 && Inv(i - 1) && i < args.length  =>  exists args[i]
            arr[i] = Integer.parseInt(args[i]);
            // pre1 && arr.length == args.length > 0 && Inv(i - 1) && arr[i] == int(args[i])
            i++;
            // pre1 && arr.length == args.length > 0 && Inv(i)
        }
        // pre1 && arr.length == args.length > 0 && i == args.length  =>
        // for j in [0; args.length): arr[j] == int(args[j]) && pre1 && arr.length == args.length > 0  (define as A)
        // arr.length == args.length > 0  =>  arr[0] exists
        System.out.println( (RECURSIVE) ? recursive(-1, arr.length, arr, arr[0]) : iterative(arr, arr[0]) );
    }
    // post:
    // A && printed integer i from pre

    // pre: A
    private static int iterative(int[] arr, int x) {
        int l = -1, r = arr.length;
        // A && l == -1 && r == arr.length
        // Inv: A && (l == -1 || arr[l] < arr[0]) && (r == arr.length || arr[r] >= arr[0]) && l > -2 && r < arr.length + 1 && l < r
        while (l < r - 1) {
            // Inv && r - l > 1
            int m = l + (r - l) / 2;
            // Inv && r - l > 1 && l < m < r && arr[m] exists
            if (arr[m] < x) {
                // Inv && arr[m] < arr[0] && l < m < arr.length + 1
                r = m;
                // Inv && r'-l' < r-l (converges)
            } else {
                // Inv && arr[m] >= arr[0] && -2 < m < r
                l = m;
                // Inv && r'-l' < r-l (converges)
            }
        }
        // A && (l == -1 || arr[l] < arr[0]) && (r == arr.length || arr[r] >= arr[0]) && l > -2 && r < arr.length + 1 && r - l == 1
        // => similar to B defined in BinarySearch, we get that:
        //  | arr[r] > arr[0] && !\exists r' < r : arr[r'] > arr[0] => \forall j < r : arr[0] > arr[j] => arr[:r] is sorted &&  arr[r - 1] < arr[r] => r is shift
        //  | r == arr.length => \forall 0 <= i < r : arr[0] > arr[i] => arr is sorted, answer is 0
        return (r == arr.length) ? 0 : r;
    }
    // post: A && printed i

    // pre: A && (l == -1 || arr[l] < arr[0]) && (r == arr.length || arr[r] >= arr[0]) && -1 <= l < r < arr.length + 1
    private static int recursive(int l, int r, int[] arr, int x) {
        if (l == r - 1) {
            // A && (l == -1 || arr[l] < arr[0]) && (r == arr.length || arr[r] >= arr[0]) && l > -2 && r < arr.length + 1 && r - l == 1
            // => similar to B defined in BinarySearch, we get that:
            //  | arr[r] > arr[0] && !\exists r' < r : arr[r'] > arr[0] => \forall j < r : arr[0] > arr[j] => arr[:r] is sorted &&  arr[r - 1] < arr[r] => r is shift
            //  | r == arr.length => \forall 0 <= i < r : arr[0] > arr[i] => arr is sorted, answer is 0
            return (r == arr.length) ? 0 : r;
        }

        // pre && l < r - 1  =>  r - l > 1
        int m = l + (r - l) / 2;
        //pre && r - l > 1 && m = l + (r - l) / 2 => l < m < r
        if (arr[m] < x) {
            // arr[m] < arr[0] && l < m < arr.length + 1
            // l' = l && r' = m => r'-l' < r - l (converges) && pre(l', r', arr, x)
            return recursive(l, m, arr, x);
        } else {
            // arr[m] >= arr[0] && -2 < m < r
            // l' = m && r' = r => r'-l' < r - l (converges) && pre(l', r', arr, x)
            return recursive(m, r, arr, x);
        }
    }
    // post: arr' = arr && printed i
}
