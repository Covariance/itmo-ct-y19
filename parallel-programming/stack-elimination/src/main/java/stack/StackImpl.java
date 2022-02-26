package stack;

import kotlinx.atomicfu.AtomicRef;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Objects;
import java.util.concurrent.ThreadLocalRandom;

public class StackImpl implements Stack {
    private final static int ELIMINATOR_SIZE = 10;
    private final static int PUSH_POS_RETRIES = 5;
    private final static int PUSH_RETRIES = 5;
    private final static int POP_RETRIES = 5;

    private static class Node {
        final AtomicRef<Node> next;
        final int x;

        Node(int x, Node next) {
            this.next = new AtomicRef<>(next);
            this.x = x;
        }
    }

    private final AtomicRef<Node> head = new AtomicRef<>(null);

    private final static class IntAtomicEliminationWrapper {

        private enum GuardStatus {
            EMPTY, FILLED, TAKEN
        }

        private final static class IntEliminationWrapper {
            private final int val;
            private final GuardStatus status;

            public IntEliminationWrapper(int val, GuardStatus status) {
                this.val = val;
                this.status = status;
            }

            public IntEliminationWrapper(GuardStatus status) {
                this(0, status);
            }

            public IntEliminationWrapper() {
                this(0, GuardStatus.EMPTY);
            }

            public int getVal() {
                return val;
            }

            @Override
            public boolean equals(Object o) {
                if (this == o) return true;
                if (o == null || getClass() != o.getClass()) return false;
                IntEliminationWrapper that = (IntEliminationWrapper) o;
                return this.status == that.status;
            }

            @Override
            public int hashCode() {
                return Objects.hash(status);
            }
        }

        private final static IntEliminationWrapper EMPTY = new IntEliminationWrapper(GuardStatus.EMPTY);
        private final static IntEliminationWrapper FILLED = new IntEliminationWrapper(GuardStatus.FILLED);
        private final static IntEliminationWrapper TAKEN = new IntEliminationWrapper(GuardStatus.TAKEN);

        private final AtomicRef<IntEliminationWrapper> ref;

        private IntAtomicEliminationWrapper() {
            this.ref = new AtomicRef<>(new IntEliminationWrapper());
        }

        public static IntEliminationWrapper getFilled(int x) {
            return new IntEliminationWrapper(x, GuardStatus.FILLED);
        }

        public boolean fillIfEmpty(IntEliminationWrapper x) {
            return ref.compareAndSet(EMPTY, x);
        }

        public Integer takeIfFilled() {
            IntEliminationWrapper val;
            while ((val = ref.getValue()).equals(FILLED)) {
                if (ref.compareAndSet(FILLED, TAKEN)) {
                    return val.getVal();
                }
            }
            return null;
        }

        public boolean cleanIfTaken() {
            return ref.compareAndSet(TAKEN, EMPTY);
        }
    }

    private final List<IntAtomicEliminationWrapper> eliminator
            = new ArrayList<>(Collections.nCopies(ELIMINATOR_SIZE, new IntAtomicEliminationWrapper()));

    private boolean eliminatorPush(int x) {
        int pos = ThreadLocalRandom.current().nextInt(ELIMINATOR_SIZE);
        int retries = 0;
        IntAtomicEliminationWrapper.IntEliminationWrapper wrapper = IntAtomicEliminationWrapper.getFilled(x);
        while (retries != PUSH_POS_RETRIES && !eliminator.get(pos).fillIfEmpty(wrapper)) {
            pos = (1 + pos) % ELIMINATOR_SIZE;
            ++retries;
        }

        if (retries == PUSH_POS_RETRIES) {
            return false;
        }

        for (retries = 0; retries != PUSH_RETRIES; ++retries){
            if (eliminator.get(pos).cleanIfTaken()) {
                return true;
            }
        }

        return eliminator.get(pos).cleanIfTaken();
    }

    private void simplePush(int x) {
        while (true) {
            Node curHead = head.getValue();
            Node newHead = new Node(x, curHead);
            if (head.compareAndSet(curHead, newHead)) {
                return;
            }
        }
    }

    @Override
    public void push(int x) {
        if (!eliminatorPush(x)) {
            simplePush(x);
        }
    }

    private int simplePop() {
        while (true) {
            Node curHead = head.getValue();
            if (curHead == null) return Integer.MIN_VALUE;
            if (head.compareAndSet(curHead, curHead.next.getValue())) {
                return curHead.x;
            }
        }
    }

    private Integer eliminatorPop() {
        int pos = ThreadLocalRandom.current().nextInt(ELIMINATOR_SIZE);
        Integer res;
        for (int retries = 0; retries != POP_RETRIES; ++retries) {
            if ((res = eliminator.get(pos).takeIfFilled()) != null) {
                return res;
            }
            pos = (1 + pos) % ELIMINATOR_SIZE;
        }
        return null;
    }

    @Override
    public int pop() {
        Integer eliminatorResult = eliminatorPop();
        if (eliminatorResult != null) {
            return eliminatorResult;
        }
        return simplePop();
    }
}
