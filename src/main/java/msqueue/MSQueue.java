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

    private final AtomicRef<Node> head;
    private final AtomicRef<Node> tail;

    public MSQueue() {
        this.head = this.tail = new AtomicRef<>(new Node(0));
    }

    @Override
    public void enqueue(int x) {
        Node newNode = new Node(x);
        while (true) {
            Node tail = this.tail.getValue();
            Node afterTail = tail.next.getValue();
            if (tail == this.tail.getValue()) {
                if (afterTail == null) {
                    if (tail.next.compareAndSet(null, newNode)) {
                        return;
                    }
                } else {
                    this.tail.compareAndSet(tail, afterTail);
                }
            }
        }
    }

    @Override
    public int dequeue() {
        while (true) {
            Node head = this.head.getValue();
            Node tail = this.tail.getValue();
            Node afterHead = head.next.getValue();
            if (head == this.head.getValue()) {
                if (head == tail) {
                    if (afterHead == null) {
                        return Integer.MIN_VALUE;
                    }
                    this.tail.compareAndSet(tail, afterHead);
                } else {
                    int val = afterHead.x;
                    if (this.head.compareAndSet(head, afterHead)) {
                        return val;
                    }
                }
            }
        }
    }

    @Override
    public int peek() {
        Node curHead = head.getValue();
        Node next = curHead.next.getValue();
        if (curHead == tail.getValue())
            return Integer.MIN_VALUE;
        return next.x;
    }
}