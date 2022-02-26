package queue;

import java.util.Iterator;
import java.util.function.Predicate;

public class ArrayQueue extends AbstractQueue {
    protected Object[] data = new Object[2];
    protected int head;


    //region Iterable
    @Override
    public Iterator<Object> iterator() {
        return new ArrayQueueIterator();
    }

    private class ArrayQueueIterator implements Iterator<Object> {
        private int current = 0;

        @Override
        public boolean hasNext() {
            return current < size;
        }

        @Override
        public Object next() {
            return data[(head + current++) % data.length];
        }
    }
    //endregion

    private void expand() {
        if (size != data.length) {
            return;
        }
        Object[] newData = new Object[2 * data.length];
        System.arraycopy(data, head, newData, 0, data.length - head);
        System.arraycopy(data, 0, newData, data.length - head, head);
        head = 0;
        data = newData;
    }

    protected Object dequeueImpl() {
        Object result = elementImpl();
        data[head] = null;
        head = (head + 1) % data.length;
        return result;
    }

    protected void enqueueImpl(Object val) {
        expand();
        data[(head + size) % data.length] = val;
    }

    protected Object elementImpl() {
        return data[head];
    }

    protected void clearImpl() {
        data = new Object[2];
        head = 0;
    }

    @Override
    protected AbstractQueue getExemplar() {
        return new ArrayQueue();
    }

    @Deprecated
    public void takeWhileImpl(Predicate<Object> predicate) {
        int count = 0;
        for (Object obj : this) {
            if (!predicate.test(obj)) {
                break;
            }
            count++;
        }
        for (int i = count; i < size; i++) {
            data[(head + i) % data.length] = null;
        }
        size = count;
    }
}
