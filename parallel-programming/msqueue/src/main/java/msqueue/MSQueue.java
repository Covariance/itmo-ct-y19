package msqueue;

import kotlinx.atomicfu.AtomicRef;

public class MSQueue implements Queue {
    private final static class Node {
        final int x;
        final AtomicRef<Node> next;

        Node(int x) {
            this.x = x;
            this.next = new AtomicRef<>(null);
        }
    }

    private final AtomicRef<Node> H;
    private final AtomicRef<Node> T;

    public MSQueue() {
        Node dummy = new Node(0);
        this.H = new AtomicRef<>(dummy);
        this.T = new AtomicRef<>(dummy);
    }

    @Override
    public void enqueue(int x) {
        // Allocate a new node from the free list
        Node node = new Node(x);
        // Keep trying until Enqueue is done
        while (true) {
            Node tail = T.getValue(); // Read Tail.ptr and Tail.count together
            Node next = tail.next.getValue(); // Read next ptr and count fields together
            if (tail == T.getValue()) { // Are tail and next consistent ?
                if (next == null) { // Was Tail pointing to the last node ?
                    if (tail.next.compareAndSet(null, node)) { // Try to link node at the end of the linked list
                        T.compareAndSet(tail, node);
                        return; // Enqueue is done.Exit loop
                    }
                } else { // Tail was not pointing to the last node
                    T.compareAndSet(tail, next); // Try to swing Tail to the next node
                }
            }
        }
    }

    @Override
    public int dequeue() {
        while (true) { // Keep trying until Dequeue is done
            Node head = H.getValue(); // Read Head
            Node tail = T.getValue(); // Read Tail
            Node next = head.next.getValue(); // Read Head.ptr–>next
            if (head == H.getValue() && tail == T.getValue()) { // Are head, tail, and next consistent?
                if (head == tail) { // Is queue empty or Tail falling behind?
                    if (next == null) { // Is queue empty ?
                        return Integer.MIN_VALUE; // Queue is empty, couldn’t dequeue
                    }
                    T.compareAndSet(tail, next); // Tail is falling behind.Try to advance it
                } else { // No need to deal with Tail
                    int value = next.x; // Read value before CAS, otherwise another dequeue might free the next node
                    if (H.compareAndSet(head, next)) { // Try to swing Head to the next node
                        return value;
                    }
                }
            }
        }
    }

    @Override
    public int peek() {
        Node head = this.H.getValue();
        Node tail = this.T.getValue();
        Node afterHead = head.next.getValue();
        if (head == tail) {
            return Integer.MIN_VALUE;
        }
        return afterHead.x;
    }
}