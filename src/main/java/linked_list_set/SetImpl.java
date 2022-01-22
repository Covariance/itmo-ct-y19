package linked_list_set;

import kotlinx.atomicfu.AtomicRef;

public class SetImpl implements Set {
    private interface Node {
        ActualNode node();
    }

    private static class ActualNode implements Node {
        final AtomicRef<Node> next;
        final int x;

        ActualNode(int x, ActualNode next) {
            this.next = new AtomicRef<Node>(next);
            this.x = x;
        }

        public ActualNode node() {
            return this;
        }
    }

    private static class RemovedNode implements Node {
        final ActualNode next;

        RemovedNode(ActualNode next) {
            this.next = next;
        }

        public ActualNode node() {
            return next;
        }
    }

    private static class Window {
        ActualNode left, right;

        public Window(ActualNode left, ActualNode right) {
            this.left = left;
            this.right = right;
        }
    }

    private final ActualNode head = new ActualNode(Integer.MIN_VALUE, new ActualNode(Integer.MAX_VALUE, null));

    /**
     * Returns the {@link Window}, where cur.x < x <= next.x
     */
    private Window findWindow(int x) {
        while (true) {
            boolean valid = true;
            ActualNode left = head;
            ActualNode right = left.next.getValue().node();
            while (right.x < x) {
                Node nextL = left.next.getValue();
                Node nextR = right.next.getValue();
                if (nextL instanceof RemovedNode || nextL.node() != right) {
                    valid = false;
                    break;
                }
                if (nextR instanceof RemovedNode) {
                    if (!left.next.compareAndSet(nextL, nextR.node())) {
                        valid = false;
                        break;
                    }
                    right = nextR.node().node();
                } else {
                    left = right;
                    right = left.next.getValue().node();
                }
            }
            if (valid) {
                Node nextL = left.next.getValue();
                if (nextL.node() != right || nextL instanceof RemovedNode) {
                    continue;
                }

                Node nextR = right.next.getValue();
                if (nextR instanceof RemovedNode) {
                    left.next.compareAndSet(nextL, nextR.node());
                    continue;
                }
                return new Window(left, right);
            }
        }
    }


    @Override
    public boolean add(int x) {
        while (true) {
            Window w = findWindow(x);
            if (w.right.x == x) {
                return false;
            } else {
                Node left = w.left.next.getValue();
                if (left.node() != w.right || left instanceof RemovedNode) {
                    continue;
                }
                if (w.left.next.compareAndSet(left, new ActualNode(x, w.right))) {
                    return true;
                }
            }
        }
    }

    @Override
    public boolean remove(int x) {
        while (true) {
            Window w = findWindow(x);
            if (w.right.x != x) {
                return false;
            } else {
                Node right = w.right.next.getValue();
                if (right instanceof ActualNode && w.right.next.compareAndSet(right, new RemovedNode(right.node()))) {
                    return true;
                }
            }
        }
    }

    @Override
    public boolean contains(int x) {
        return findWindow(x).right.x == x;
    }
}