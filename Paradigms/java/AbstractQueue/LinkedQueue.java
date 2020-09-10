package queue;

import java.util.Iterator;
import java.util.function.Predicate;

/**
 * @author Pavel Martynov (git: CovarianceMomentum)
 */

public class LinkedQueue extends AbstractQueue {

    //region Iterable
    @Override
    public Iterator<Object> iterator() {
        return new LinkedQueueIterator();
    }

    private class LinkedQueueIterator implements Iterator<Object> {

        Element current = head;

        @Override
        public boolean hasNext() {
            return current != null;
        }

        @Override
        public Object next() {
            Object res = current.val;
            current = current.next;
            return res;
        }

    }
    //endregion

    protected static class Element {
        private Object val;
        private Element next;

        private Element(Object val, Element next) {
            this.val = val;
            this.next = next;
        }
    }

    protected Element head;
    protected Element tail;

    @Override
    protected void enqueueImpl(Object val) {
        if (size == 0) {
            head = tail = new Element(val, null);
        } else {
            tail.next = new Element(val, null);
            tail = tail.next;
        }
    }

    @Override
    protected Object dequeueImpl() {
        Object result = head.val;
        head = head.next;
        return result;
    }

    @Override
    protected Object elementImpl() {
        return head.val;
    }

    @Override
    protected void clearImpl() {
        head = null;
        tail = null;
    }

    @Override
    protected AbstractQueue getExemplar() {
        return new LinkedQueue();
    }

    @Deprecated
    public void takeWhileImpl(Predicate<Object> predicate) {
        Element prev = null;
        Element current = head;
        int count = 0;
        while (current != null && predicate.test(current.val)) {
            prev = current;
            current = current.next;
            count++;
        }
        tail = prev;
        if (tail != null) {
            tail.next = null;
        }
        size = count;
    }
}
