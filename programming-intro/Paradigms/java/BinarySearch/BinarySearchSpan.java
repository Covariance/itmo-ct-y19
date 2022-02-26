package search;

/**
 * @author Pavel Martynov (git: CovarianceMomentum)
 */

public class BinarySearchSpan {
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
        spanBinarySearch(x, arr);
        //System.out.println(IterativeBinarySearch(x, arr));
    }

    static void spanBinarySearch(int x, int[] arr) {
        int insertionPoint = BinarySearch.iterativeBinarySearch(x, arr);
        System.out.print(insertionPoint + " ");
        int endingPoint;
        if (x == Integer.MIN_VALUE) {
            endingPoint = arr.length;
        } else {
            endingPoint = BinarySearch.iterativeBinarySearch(x - 1, arr);
        }
        System.out.println(endingPoint - insertionPoint);
    }



    /*
    need to add test for span:
    -2147483648 -2147483648 -2147483648 -2147483648
    expected 0 3
    actual 0 0
     */
}
