package queue;

/**
 * Inv: a[0], a[1], ..., a[n - 1]
 * n >= 0
 * \forall i: 0 <= i < n : a[i] != null
 */
public class ArrayQueueADT {
    private Object[] data = new Object[2];
    private int head;
    private int size;

    /**
     * Pre: q != null
     * Post: q.a' = q.a && q.n' = q.n
     * @param q {ArrayQueueADT} Queue to expand
     */
    private static void expand(ArrayQueueADT q) {
        if (q.size != q.data.length) {
            return;
        }
        Object[] newData = new Object[2 * q.data.length];
        System.arraycopy(q.data, q.head, newData, 0, q.data.length - q.head);
        System.arraycopy(q.data, 0, newData, q.data.length - q.head, q.head);
        q.head = 0;
        q.data = newData;
    }

    /**
     * Removes first element from given queue and returns its value
     * Pre: n > 0 && q != null
     * Post: n' = n - 1 && a' = [a[1], ... a[n - 1]]
     * @param q {ArrayQueueADT} Queue to remove element from
     * @return {Object} a[0]
     */
    public static Object dequeue(ArrayQueueADT q) {
        assert q != null && q.size > 0;

        Object result = element(q);
        q.data[q.head] = null;
        q.head = (q.head + 1) % q.data.length;
        q.size--;
        return result;
    }

    /**
     * Pushes new element in given queue
     * Pre: q != null && val != null
     * Post: n' = n + 1 && a' = [a[0]..a[n - 1], val]
     * @param q {ArrayQueueADT} queue to push element in
     * @param val {Object} value to push into queue
     */
    public static void enqueue(ArrayQueueADT q, Object val) {
        assert q != null && val != null;

        if (q.size == q.data.length) {
            expand(q);
        }
        q.data[(q.head + q.size) % q.data.length] = val;
        q.size++;
    }

    /**
     * Adds given element to the beginning of the given queue
     * Pre: q != null && val != null
     * Post: n' = n + 1 && a' = [val, a[0], ..., a[n - 1]]
     * @param q {ArrayQueueADT} Queue to add element in
     * @param val {Object} Value to add into queue
     */
    public static void push(ArrayQueueADT q, Object val) {
        assert q != null && val != null;

        expand(q);
        q.data[(q.head + q.data.length - 1) % q.data.length] = val;
        q.head = (q.head + q.data.length - 1) % q.data.length;
        q.size++;
    }

    /**
     * Returns last element of the given queue
     * Pre: q != null && n > 0
     * Post: Immutable
     * @param q {ArrayQueueADT} Queue to return element from
     * @return {Object} a[n-1]
     */
    public static Object peek(ArrayQueueADT q) {
        assert q != null && q.size > 0;

        return q.data[(q.head + q.size - 1) % q.data.length];
    }

    /**
     * Removes last element of the given queue and returns its value
     * Pre: q != null && n > 0
     * Post: n' = n - 1 && a' = [a[0], ..., a[n - 2]]
     * @param q {ArrayQueueADT} Queue to remove element from
     * @return {Object} a[n-1]
     */
    public static Object remove(ArrayQueueADT q) {
        assert q != null && q.size > 0;

        Object result = peek(q);
        q.data[(q.head + q.size - 1) % q.data.length] = null;
        q.size--;
        return result;
    }

    /**
     * Returns element of the given queue by index
     * Pre: q != null && 0 <= index < n
     * Post: immutable
     * @param q {ArrayQueueADT} Queue to get element from
     * @param index {Integer} Index of element to get
     * @return {Object} a[index]
     */
    public static Object get(ArrayQueueADT q, int index) {
        assert q != null && 0 <= index && index < q.size;

        return q.data[(q.head + index) % q.data.length];
    }

    /**
     * Sets element of the given queue to value y index
     * Pre: q != null && 0 <= index < n && val != null
     * Post: n' = n && a' = [a[0], ..., a[index - 1], val, a[index + 1], ... a[n - 1]]
     * @param q {ArrayQueueADT} Queue to set element in
     * @param index {Integer} Index of element to set
     * @param val {Object} Object to set element to
     */
    public static void set(ArrayQueueADT q, int index, Object val) {
        assert q != null && 0 <= index && index < q.size && val != null;

        q.data[(q.head + index) % q.data.length] = val;
    }

    /**
     * Returns value of first element in given queue
     * Pre: q != null && n > 0
     * Post: immutable
     * @param q {ArrayQueueADT} Queue to return element from
     * @return {Object} a[0]
     */
    public static Object element(ArrayQueueADT q) {
        assert q != null && q.size > 0;

        return q.data[q.head];
    }

    /**
     * Returns size of queue
     * Pre: q != null
     * Post: immutable
     * @param q {ArrayQueueADT} given queue
     * @return n
     */
    public static int size(ArrayQueueADT q) {
        assert q != null;

        return q.size;
    }

    /**
     * Returns true if given queue is empty
     * Pre: q != null
     * Post: immutable
     * @param q {ArrayQueueADT} Queue to check
     * @return n == 0
     */
    public static boolean isEmpty(ArrayQueueADT q) {
        assert q != null;

        return q.size == 0;
    }

    /**
     * Clears the queue
     * Pre: q != null
     * Post: n = 0 && a' = []
     * @param q {ArrayQueueADT} Queue to clear
     */
    public static void clear(ArrayQueueADT q) {
        assert q != null;

        q.data = new Object[2];
        q.head = q.size = 0;
    }
}