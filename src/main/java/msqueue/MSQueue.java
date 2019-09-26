package msqueue;

public class MSQueue implements Queue {
    private Node head;
    private Node tail;

    public MSQueue() {
        Node dummy = new Node(0);
        this.head = dummy;
        this.tail = dummy;
    }

    @Override
    public void enqueue(int x) {
        Node newTail = new Node(x);
        tail.next = newTail;
        tail = newTail;
    }

    @Override
    public int dequeue() {
        Node curHead = head;
        Node next = head.next;
        if (curHead == tail)
            return Integer.MIN_VALUE;
        head = next;
        return next.x;
    }

    @Override
    public int peek() {
        Node curHead = head;
        Node next = head.next;
        if (curHead == tail)
            return Integer.MIN_VALUE;
        return next.x;
    }

    private class Node {
        final int x;
        Node next;

        Node(int x) {
            this.x = x;
        }
    }
}