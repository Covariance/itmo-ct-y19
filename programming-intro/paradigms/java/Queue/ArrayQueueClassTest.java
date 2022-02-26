package queue;

import org.junit.jupiter.api.AfterAll;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;

import java.util.Random;

/**
 * @author Pavel Martynov (git: CovarianceMomentum)
 */

public class ArrayQueueClassTest {
    private final static Random rand = new Random(4765239);

    @BeforeAll
    static void init() {
        System.out.println("Testing Class realization:");
    }

    @Test
    void testSize() {
        System.out.println("Testing \"size\"");
        ArrayQueue q = new ArrayQueue();
        Assertions.assertEquals(0, q.size());
        int bal = 0;
        for (int i = 0; i < 1_000_000; i++) {
            if (bal == 0) {
                q.enqueue(i);
                bal++;
            } else {
                if (rand.nextInt(3) == 0) {
                    q.dequeue();
                    bal--;
                } else {
                    q.enqueue(i);
                    bal++;
                }
            }
            Assertions.assertEquals(bal, q.size());
        }
    }

    @Test
    void testClear() {
        System.out.println("Testing \"clear\"");
        ArrayQueue q = new ArrayQueue();
        for (int i = 1; i < 1_000; i++) {
            for (int j = 0; j < i; j++) {
                q.enqueue(j);
            }
            q.clear();
            Assertions.assertEquals(0, q.size());
        }
    }

    @Test
    void testEmpty() {
        System.out.println("Testing \"isEmpty\"");
        ArrayQueue q = new ArrayQueue();
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

    @Test
    void testRemovingFromEmptyError() {
        System.out.println("Testing \"dequeue\" from empty");
        Assertions.assertThrows(AssertionError.class, () -> {
            ArrayQueue q = new ArrayQueue();
            q.dequeue();
        });
        Assertions.assertThrows(AssertionError.class, () -> {
                    ArrayQueue q = new ArrayQueue();
                    for (int i = 0; i < 1_000; i++) {
                        q.enqueue(i);
                    }
                    for (int i = 0; i < 1_001; i++) {
                        q.dequeue();
                    }
                }
        );
    }

    @Test
    void testEnqueueNull() {
        System.out.println("Testing \"enqueue\" with null");
        Assertions.assertThrows(AssertionError.class, () ->
        {
            ArrayQueue q = new ArrayQueue();
            q.enqueue(null);
        });

        Assertions.assertThrows(AssertionError.class, () ->
        {
            ArrayQueue q = new ArrayQueue();
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

    @Test
    void testValues() {
        System.out.println("Testing order in queue");
        ArrayQueue q = new ArrayQueue();
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

    @Test
    void testHeadOverlap() {
        System.out.println("Testing head overlap");
        ArrayQueue q = new ArrayQueue();
        for (int j = 0; j < 1_000; j++) {
            for (int i = 0; i < 7; i++) {
                q.enqueue(i);
            }
            for (int i = 0; i < 7; i++) {
                Assertions.assertEquals(i, q.dequeue());
            }
        }
    }

    @Test
    void testPushRemove() {
        System.out.println("Testing push-remove");
        ArrayQueue q = new ArrayQueue();
        q.push("100");
        Assertions.assertEquals("100", q.dequeue());
        q.enqueue("100");
        Assertions.assertEquals("100", q.remove());
        q.push("100");
        Assertions.assertEquals("100", q.remove());
    }

    @Test
    void testGetSet() {
        System.out.println("Testing get-set");
        ArrayQueue q = new ArrayQueue();
        q.push(1);
        q.push(2);
        q.push(3);
        Assertions.assertEquals(2, q.get(1));
        q.set(1, "100");
        Assertions.assertEquals("100", q.get(1));
    }

    @AfterAll
    static void report() {
        System.out.println("Tests successful");
    }

}
