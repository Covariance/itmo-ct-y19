package queue;

import org.junit.jupiter.api.AfterAll;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.ValueSource;

import java.lang.reflect.InvocationTargetException;
import java.util.Random;

/**
 * @author Pavel Martynov (git: CovarianceMomentum)
 */

public class AbstractQueueTest {
    private static Random rand;

    @BeforeEach
    void reRand() {
        rand = new Random(4765239);
    }

    Queue createQueue(Class<Queue> queue) {
        try {
            return queue.getConstructor().newInstance();
        } catch (NoSuchMethodException | IllegalAccessException | InvocationTargetException | InstantiationException e) {
            throw new AssertionError("Cannot create queue: " + queue);
        }
    }

    void announceTest(String testName, Class<Queue> q) {
        System.out.print("Testing " + testName + " for: " + q);
    }

    @ParameterizedTest
    @ValueSource(classes = {ArrayQueue.class, LinkedQueue.class})
    void testSize(Class<Queue> queue) {
        announceTest("size", queue);
        Queue q = createQueue(queue);
        Assertions.assertEquals(0, q.size());
        int bal = 0;
        for (int i = 0; i < 1_000_000; i++) {
            if (bal == 0 || rand.nextInt(3) != 0) {
                q.enqueue(i);
                bal++;
            } else {
                q.dequeue();
                bal--;
            }
            Assertions.assertEquals(bal, q.size());
        }
    }

    @ParameterizedTest
    @ValueSource(classes = {ArrayQueue.class, LinkedQueue.class})
    void testClear(Class<Queue> queue) {
        announceTest("clear", queue);
        Queue q = createQueue(queue);
        for (int i = 1; i < 1_000; i++) {
            for (int j = 0; j < i; j++) {
                q.enqueue(j);
            }
            q.clear();
            Assertions.assertEquals(0, q.size());
        }
    }

    @ParameterizedTest
    @ValueSource(classes = {ArrayQueue.class, LinkedQueue.class})
    void testEmpty(Class<Queue> queue) {
        announceTest("isEmpty", queue);
        Queue q = createQueue(queue);
        Assertions.assertTrue(q.isEmpty());
        q.enqueue("val");
        Assertions.assertFalse(q.isEmpty());
        q.dequeue();
        Assertions.assertTrue(q.isEmpty());
        for (int i = 0; i < 1_000; i++) {
            q.enqueue(i);
        }
        for (int i = 0; i < 1_000; i++) {
            q.dequeue();
        }
        Assertions.assertTrue(q.isEmpty());
        // random neq tests
        for (int i = 0; i < 1_000; i++) {
            q.clear();
            int inserted = rand.nextInt(1_000);
            for (int j = 0; j < inserted; j++) {
                q.enqueue(j);
            }
            int removed = rand.nextInt(inserted);
            for (int j = 0; j < removed; j++) {
                q.dequeue();
            }
            Assertions.assertFalse(q.isEmpty());
        }
    }

    @ParameterizedTest
    @ValueSource(classes = {ArrayQueue.class, LinkedQueue.class})
    void testRemovingFromEmptyError(Class<Queue> queue) {
        announceTest("dequeue from empty", queue);
        Assertions.assertThrows(AssertionError.class, () -> {
            Queue q = createQueue(queue);
            q.dequeue();
        });
        Assertions.assertThrows(AssertionError.class, () -> {
                    Queue q = createQueue(queue);
                    for (int i = 0; i < 1_000; i++) {
                        q.enqueue(i);
                    }
                    for (int i = 0; i < 1_001; i++) {
                        q.dequeue();
                    }
                }
        );
    }

    @ParameterizedTest
    @ValueSource(classes = {ArrayQueue.class, LinkedQueue.class})
    void testEnqueueNull(Class<Queue> queue) {
        announceTest("enqueue", queue);
        Assertions.assertThrows(AssertionError.class, () ->
        {
            Queue q = createQueue(queue);
            q.enqueue(null);
        });

        Assertions.assertThrows(AssertionError.class, () ->
        {
            Queue q = createQueue(queue);
            for (int i = 0; i < 1_000; i++) {
                q.enqueue(i);
            }
            int bound = rand.nextInt(1_000);
            for (int i = 0; i < bound; i++) {
                q.dequeue();
            }
            q.enqueue(null);
        });
    }

    @ParameterizedTest
    @ValueSource(classes = {ArrayQueue.class, LinkedQueue.class})
    void testValues(Class<Queue> queue) {
        announceTest("value", queue);
        Queue q = createQueue(queue);
        Object[] values = new Object[]{1, 2, true, "val", new Object()};
        for (Object obj : values) {
            q.enqueue(obj);
        }
        for (Object obj : values) {
            Assertions.assertEquals(obj, q.dequeue());
        }
        q.clear();
        // big test
        for (int i = 0; i < 1_000_000; i++) {
            q.enqueue(i);
        }
        for (int i = 0; i < 1_000_000; i++) {
            Assertions.assertEquals(i, q.dequeue());
        }
    }

    @ParameterizedTest
    @ValueSource(classes = {ArrayQueue.class, LinkedQueue.class})
    void testHeadOverlap(Class<Queue> queue) {
        announceTest("head overlap", queue);
        Queue q = createQueue(queue);
        for (int j = 0; j < 1_000; j++) {
            for (int i = 0; i < 7; i++) {
                q.enqueue(i);
            }
            for (int i = 0; i < 7; i++) {
                Assertions.assertEquals(i, q.dequeue());
            }
        }
    }

    @AfterAll
    static void report() {
        System.out.println("Tests successful");
    }

}
