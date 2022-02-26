package queue;

import java.util.function.Consumer;
import java.util.function.Predicate;

/**
 * @author Pavel Martynov (git: CovarianceMomentum)
 */

public abstract class AbstractQueue implements Queue {
    protected int size = 0;

    @Override
    public boolean isEmpty() {
        return size == 0;
    }

    @Override
    public int size() {
        return size;
    }

    @Override
    public void enqueue(final Object val) {
        assert val != null;
        enqueueImpl(val);
        size++;
    }

    @Override
    public Object dequeue() {
        assert size > 0;
        size--;
        return dequeueImpl();
    }

    @Override
    public Object element() {
        assert size > 0;
        return elementImpl();
    }

    @Override
    public void clear() {
        clearImpl();
        size = 0;
    }

    @Override
    public void retainIf(final Predicate<Object> predicate) {
        assert predicate != null;

        for (int i = size; i > 0; i--) {
            final Object currentElement = dequeue();
            if (predicate.test(currentElement)) {
                enqueue(currentElement);
            }
        }
    }

    @Override
    public void removeIf(final Predicate<Object> predicate) {
        retainIf(predicate.negate());
    }

    private static void divide(final Predicate<Object> predicate, final AbstractQueue queue, final boolean takeFirst) {
        final AbstractQueue firstSegment = queue.getExemplar();
        while (queue.size > 0 && predicate.test(queue.element())) {
            firstSegment.enqueue(queue.dequeue());
        }
    }

    interface Action extends Consumer<AbstractQueue> {
    }

    private void segmentAction(final Predicate<Object> p, final Action head, final Action tail) {
        assert p != null;

        int i = size;
        while (i > 0 && p.test(element())) {
            head.accept(this);
            i--;
        }
        while (i > 0) {
            tail.accept(this);
            i--;
        }
    }

    @Override
    public void takeWhile(final Predicate<Object> predicate) {
        segmentAction(predicate, q -> q.enqueue(q.dequeue()), AbstractQueue::dequeue);
    }

    @Override
    public void dropWhile(final Predicate<Object> predicate) {
        segmentAction(predicate, AbstractQueue::dequeue, q -> {});
    }

    /*@Override
    public void takeWhile(Predicate<Object> predicate) { //TODO
        assert predicate != null;

        int i = size;
        while (i > 0 && predicate.test(element())) {
            enqueue(dequeue());
            i--;
        }
        while (i > 0) {
            dequeue();
            i--;
        }
    }

    @Override
    public void dropWhile(Predicate<Object> predicate) { //TODO
        assert predicate != null;

        while (!isEmpty() && predicate.test(element())) {
            dequeue();
        }
    }

     */

    protected abstract void enqueueImpl(Object val);

    protected abstract Object dequeueImpl();

    protected abstract Object elementImpl();

    protected abstract void clearImpl();

    protected abstract AbstractQueue getExemplar();
}
