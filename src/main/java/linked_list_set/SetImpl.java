package linked_list_set;

import kotlin.Pair;
import kotlinx.atomicfu.AtomicRef;

public class SetImpl implements Set {
    private final Node tail = new Node(Integer.MAX_VALUE, null);
    private final Node head = new Node(Integer.MIN_VALUE, tail);

    private static class Node {
        public int x;
        public AtomicRef<WrappedNode> next;

        public Node(int x, Node next) {
            this.x = x;
            this.next = new AtomicRef<>(new WrappedNode(next));
        }
    }

    private static class WrappedNode {
        private final Node node;
        private final boolean removed;

        public WrappedNode(Node node, boolean removed) {
            this.node = node;
            this.removed = removed;
        }

        public WrappedNode(Node next) {
            this(next, false);
        }

        public WrappedNode(int x, Node next) {
            this(new Node(x, next));
        }

        public Node getNode() {
            return node;
        }

        public boolean getRemoved() {
            return removed;
        }
    }

    private Pair<Node, Node> findWindow(int x) {
        while (true) {
            boolean valid = true;
            Node left = head;
            Node right = left.next.getValue().getNode();
            while (right.x < x) {
                WrappedNode nextL = left.next.getValue();
                WrappedNode nextR = right.next.getValue();
                if (nextL.getRemoved() || nextL.getNode() != right) {
                    valid = false;
                    break;
                }
                if (nextR.getRemoved()) {
                    WrappedNode newNextL = new WrappedNode(nextR.getNode());
                    if (!left.next.compareAndSet(nextL, newNextL)) {
                        valid = false;
                        break;
                    }
                    right = newNextL.getNode();
                } else {
                    left = right;
                    right = left.next.getValue().getNode();
                }
            }
            if (valid) {
                WrappedNode nextL = left.next.getValue();
                if (nextL.node != right || nextL.getRemoved()) {
                    continue;
                }

                WrappedNode nextR = right.next.getValue();
                if (nextR.getRemoved()) {
                    left.next.compareAndSet(nextL, new WrappedNode(nextR.getNode()));
                    continue;
                }
                return new Pair<>(left, right);
            }
        }
    }

    @Override
    public boolean add(int x) {
        while (true) {
            Pair<Node, Node> w = findWindow(x);
            if (w.getSecond().x == x) {
                return false;
            } else {
                WrappedNode left = w.getFirst().next.getValue();
                if (left.getNode() != w.getSecond() || left.getRemoved()) {
                    continue;
                }
                if (w.getFirst().next.compareAndSet(left, new WrappedNode(x, w.getSecond()))) {
                    return true;
                }
            }
        }
    }

    @Override
    public boolean remove(int x) {
        while (true) {
            Pair<Node, Node> w = findWindow(x);
            if (w.getSecond().x != x) {
                return false;
            } else {
                WrappedNode right = w.getSecond().next.getValue();
                if (!right.getRemoved() && w.getSecond().next.compareAndSet(right, new WrappedNode(right.node, true))) {
                    return true;
                }
            }
        }
    }

    @Override
    public boolean contains(int x) {
        return findWindow(x).getSecond().x == x;
    }
}