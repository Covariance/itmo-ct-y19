package queue;

import java.util.function.Predicate;

/**
 * Inv: a[0], a[1], ..., a[n - 1]
 * n >= 0
 * \forall i: 0 <= i < n : a[i] != null
 */
public interface Queue extends Iterable<Object> {

    /**
     * Adds element to the end of queue
     * Pre: val != null
     * Post: n' = n + 1 && a' = [a[0], a[1], ..., a[n - 1], val]
     * @param val {Object} element to enqueue
     */
    void enqueue(Object val);

    /**
     * Removes element from the beginning of the queue and returns its value
     * Pre: n > 0
     * Post: n' = n - 1 && a' = [a[1], a[2], ..., a[n - 1]]
     * @return {Object} a[n - 1]
     */
    Object dequeue();

    /**
     * Returns element from the beginning of the queue
     * Pre: n > 0
     * Post: n' = n && a' = a
     * @return {Object} a[n - 1]
     */
    Object element();

    /**
     * Return true if and only if queue is empty
     * Pre:
     * Post: n' = n && a' = a
     * @return {boolean} (n == 0)
     */
    boolean isEmpty();

    /**
     * Returns size of the queue
     * Pre:
     * Post: n' = n && a' = a
     * @return {int} n
     */
    int size();

    /**
     * Clears the queue
     * Pre:
     * Post: n' = 0 && a' = []
     */
    void clear();

    /**
     * Removes from the queue all elements that match given predicate
     * Pre: predicate != null
     * Post: n' = k && a' = [a[i_1], a[i_2], ... a[i_k]],
     * 0 <= i_1 < i_2 < ... < i_k < n && \forall i_j predicate.test(a[i_j]) == false && \forall t: \forall j: i_j != t: predicate.test(a[t]) == true
     * @param predicate {Predicate<Object>} predicate to test
     */
    void removeIf(Predicate<Object> predicate);

    /**
     * Removes from the queue all elements that don't match given predicate
     * Pre: predicate != null
     * Post: n' = k && a' = [a[i_1], a[i_2], ... a[i_k]],
     * 0 <= i_1 < i_2 < ... < i_k < n && \forall i_j predicate.test(a[i_j]) == true && \forall t: \forall j: i_j != t: predicate.test(a[t]) == false
     * @param predicate {Predicate<Object>} predicate to test
     */
    void retainIf(Predicate<Object> predicate);

    /**
     * Deletes elements from beginning of the queue that match given predicate
     * Pre: predicate != null
     * Post: | n' = n - i && a' = [a[i], a[i + 1], ..., a[n - 1]], !\exists 0 <= j < i : predicate.test(a[j]) == false && (i == n || predicate.test(a[i]) == false)
//     *       | n' = n && a' = a, (n == 0 || predicate.test(a[0]) == false)
     * @param predicate {Predicate<Object>} predicate to test
     */
    void dropWhile(Predicate<Object> predicate);

    /**
     * Retains in queue elements from beginning of the queue that match given predicate
     * Pre: predicate != null
     * Post: | n' = i && a' = [a[0], a[1], ..., a[i - 1]], !\exists 0 <= j < i : predicate.test(a[j]) == false && (i == n || predicate.test(a[i]) == false)
     *       | n' = 0 && a' = [], (n == 0 || predicate.test(a[0]) == false)
     * @param predicate {Predicate<Object>} predicate to test
     */
    void takeWhile(Predicate<Object> predicate);
}
