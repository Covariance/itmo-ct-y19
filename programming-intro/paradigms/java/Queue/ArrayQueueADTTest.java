package queue;

import org.junit.jupiter.api.AfterAll;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;

import java.util.Random;

import static queue.ArrayQueueADT.*;

/**
 * @author Pavel Martynov (git: CovarianceMomentum)
 */

public class ArrayQueueADTTest {
    private final static Random rand = new Random(4765239);

    @BeforeAll
    static void init() {
        System.out.println("Testing ADT realization:");
    }

    @Test
    void testSize() {
        System.out.println("Testing \"size\"");
        ArrayQueueADT q = new ArrayQueueADT();
        Assertions.assertEquals(0, size(q));
        int bal = 0;
        for (int i = 0; i < 1_000_000; i++) {
            if (bal == 0) {
                enqueue(q, i);
                bal++;
            } else {
                if (rand.nextInt(3) == 0) {
                    dequeue(q);
                    bal--;
                } else {
                    enqueue(q, i);
                    bal++;
                }
            }
            Assertions.assertEquals(bal, size(q));
        }
    }

    @Test
    void testClear() {
        System.out.println("Testing \"clear\"");
        ArrayQueueADT q = new ArrayQueueADT();
        for (int i = 1; i < 1_000; i++) {
            for (int j = 0; j < i; j++) {
                enqueue(q, j);
            }
            clear(q);
            Assertions.assertEquals(0, size(q));
        }
    }

    @Test
    void testEmpty() {
        System.out.println("Testing \"isEmpty\"");
        ArrayQueueADT q = new ArrayQueueADT();
        Assertions.assertTrue(isEmpty(q));
        enqueue(q, "val");
        Assertions.assertFalse(isEmpty(q));
        dequeue(q);
        Assertions.assertTrue(isEmpty(q));
        for (int i = 0; i < 1_000; i++) {
            enqueue(q, i);
        }
        for (int i = 0; i < 1_000; i++) {
            dequeue(q);
        }
        Assertions.assertTrue(isEmpty(q));
        // random neq tests
        for (int i = 0; i < 1_000; i++) {
            clear(q);
            int inserted = rand.nextInt(1_000);
            for (int j = 0; j < inserted; j++) {
                enqueue(q, j);
            }
            int removed = rand.nextInt(inserted);
            for (int j = 0; j < removed; j++) {
                dequeue(q);
            }
            Assertions.assertFalse(isEmpty(q));
        }
    }

    @Test
    void testRemovingFromEmptyError() {
        System.out.println("Testing \"dequeue\" from empty");
        Assertions.assertThrows(AssertionError.class, () -> {
            ArrayQueueADT q = new ArrayQueueADT();
            dequeue(q);
        });
        Assertions.assertThrows(AssertionError.class, () -> {
                    ArrayQueueADT q = new ArrayQueueADT();
                    for (int i = 0; i < 1_000; i++) {
                        enqueue(q, i);
                    }
                    for (int i = 0; i < 1_001; i++) {
                        dequeue(q);
                    }
                }
        );
    }

    @Test
    void testEnqueueNull() {
        System.out.println("Testing \"enqueue\" with null");
        Assertions.assertThrows(AssertionError.class, () ->
        {
            ArrayQueueADT q = new ArrayQueueADT();
            enqueue(q,null);
        });

        Assertions.assertThrows(AssertionError.class, () ->
        {
            ArrayQueueADT q = new ArrayQueueADT();
            for (int i = 0; i < 1_000; i++) {
                enqueue(q, i);
            }
            int bound = rand.nextInt(1_000);
            for (int i = 0; i < bound; i++) {
                dequeue(q);
            }
            enqueue(q,null);
        });
    }

    @Test
    void testValues() {
        System.out.println("Testing order in queue");
        ArrayQueueADT q = new ArrayQueueADT();
        Object[] values = new Object[]{1, 2, true, "val", new Object()};
        for (Object obj : values) {
            enqueue(q, obj);
        }
        for (Object obj : values) {
            Assertions.assertEquals(obj, dequeue(q));
        }
        clear(q);
        // big test
        for (int i = 0; i < 1_000_000; i++) {
            enqueue(q, i);
        }
        for (int i = 0; i < 1_000_000; i++) {
            Assertions.assertEquals(i, dequeue(q));
        }
    }

    @Test
    void testHeadOverlap() {
        System.out.println("Testing head overlap");
        ArrayQueueADT q = new ArrayQueueADT();
        for (int j = 0; j < 1_000; j++) {
            for (int i = 0; i < 7; i++) {
                enqueue(q, i);
            }
            for (int i = 0; i < 7; i++) {
                Assertions.assertEquals(i, dequeue(q));
            }
        }
    }

    @Test
    void testPushRemove() {
        System.out.println("Testing push-remove");
        ArrayQueueADT q = new ArrayQueueADT();
        push(q, "100");
        Assertions.assertEquals("100", dequeue(q));
        enqueue(q,"100");
        Assertions.assertEquals("100", remove(q));
        push(q, "100");
        Assertions.assertEquals("100", remove(q));
    }

    @Test
    void testGetSet() {
        System.out.println("Testing get-set");
        ArrayQueueADT q = new ArrayQueueADT();
        push(q,1);
        push(q,2);
        push(q,3);
        Assertions.assertEquals(2, get(q,1));
        set(q,1, "100");
        Assertions.assertEquals("100", get(q,1));
    }

    @AfterAll
    static void report() {
        System.out.println("Tests successful");
    }

}
