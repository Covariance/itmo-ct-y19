package queue;

import org.junit.jupiter.api.*;
import org.junit.jupiter.api.Test;

import java.util.Random;

import static queue.ArrayQueueADT.*;

/**
 * @author Pavel Martynov (git: CovarianceMomentum)
 */

public class ArrayQueueModuleTest {
    private final static Random rand = new Random(4765239);

    @BeforeAll
    static void init() {
        System.out.println("Testing Module realization:");
    }

    @AfterEach
    void clear() {
        ArrayQueueModule.clear();
    }

    @Test
    void testSize() {
        System.out.println("Testing \"size\"");
        Assertions.assertEquals(0, ArrayQueueModule.size());
        int bal = 0;
        for (int i = 0; i < 1_000_000; i++) {
            if (bal == 0) {
                ArrayQueueModule.enqueue(i);
                bal++;
            } else {
                if (rand.nextInt(3) == 0) {
                    ArrayQueueModule.dequeue();
                    bal--;
                } else {
                    ArrayQueueModule.enqueue(i);
                    bal++;
                }
            }
            Assertions.assertEquals(bal, ArrayQueueModule.size());
        }
    }

    @Test
    void testClear() {
        System.out.println("Testing \"clear\"");
        for (int i = 1; i < 1_000; i++) {
            for (int j = 0; j < i; j++) {
                ArrayQueueModule.enqueue(j);
            }
            ArrayQueueModule.clear();
            Assertions.assertEquals(0, ArrayQueueModule.size());
        }
    }

    @Test
    void testEmpty() {
        System.out.println("Testing \"isEmpty\"");
        Assertions.assertTrue(ArrayQueueModule.isEmpty());
        ArrayQueueModule.enqueue("val");
        Assertions.assertFalse(ArrayQueueModule.isEmpty());
        ArrayQueueModule.dequeue();
        Assertions.assertTrue(ArrayQueueModule.isEmpty());
        for (int i = 0; i < 1_000; i++) {
            ArrayQueueModule.enqueue(i);
        }
        for (int i = 0; i < 1_000; i++) {
            ArrayQueueModule.dequeue();
        }
        Assertions.assertTrue(ArrayQueueModule.isEmpty());
        // random neq tests
        for (int i = 0; i < 1_000; i++) {
            ArrayQueueModule.clear();
            int inserted = rand.nextInt(1_000);
            for (int j = 0; j < inserted; j++) {
                ArrayQueueModule.enqueue(j);
            }
            int removed = rand.nextInt(inserted);
            for (int j = 0; j < removed; j++) {
                ArrayQueueModule.dequeue();
            }
            Assertions.assertFalse(ArrayQueueModule.isEmpty());
        }
    }

    @Test
    void testRemovingFromEmptyError() {
        System.out.println("Testing \"dequeue\" from empty");
        Assertions.assertThrows(AssertionError.class, ArrayQueueModule::dequeue);
        Assertions.assertThrows(AssertionError.class, () -> {
                    for (int i = 0; i < 1_000; i++) {
                        ArrayQueueModule.enqueue(i);
                    }
                    for (int i = 0; i < 1_001; i++) {
                        ArrayQueueModule.dequeue();
                    }
                }
        );
    }

    @Test
    void testEnqueueNull() {
        System.out.println("Testing \"enqueue\" with null");
        Assertions.assertThrows(AssertionError.class, () ->
        {
            ArrayQueueModule.enqueue(null);
        });

        Assertions.assertThrows(AssertionError.class, () ->
        {
            for (int i = 0; i < 1_000; i++) {
                ArrayQueueModule.enqueue(i);
            }
            int bound = rand.nextInt(1_000);
            for (int i = 0; i < bound; i++) {
                ArrayQueueModule.dequeue();
            }
            ArrayQueueModule.enqueue(null);
        });
    }

    @Test
    void testValues() {
        System.out.println("Testing order in queue");
        Object[] values = new Object[]{1, 2, true, "val", new Object()};
        for (Object obj : values) {
            ArrayQueueModule.enqueue(obj);
        }
        for (Object obj : values) {
            Assertions.assertEquals(obj, ArrayQueueModule.dequeue());
        }

        // big test
        for (int i = 0; i < 1_000_000; i++) {
            ArrayQueueModule.enqueue(i);
        }
        for (int i = 0; i < 1_000_000; i++) {
            Assertions.assertEquals(i, ArrayQueueModule.dequeue());
        }
    }

    @Test
    void testHeadOverlap() {
        System.out.println("Testing head overlap");
        for (int j = 0; j < 1_000; j++) {
            for (int i = 0; i < 7; i++) {
                ArrayQueueModule.enqueue(i);
            }
            for (int i = 0; i < 7; i++) {
                Assertions.assertEquals(i, ArrayQueueModule.dequeue());
            }
        }
    }

    @Test
    void testPushRemove() {
        System.out.println("Testing push-remove");
        ArrayQueueModule.push("100");
        Assertions.assertEquals("100", ArrayQueueModule.dequeue());
        ArrayQueueModule.enqueue("100");
        Assertions.assertEquals("100", ArrayQueueModule.remove());
        ArrayQueueModule.push("100");
        Assertions.assertEquals("100", ArrayQueueModule.remove());
    }

    @Test
    void testGetSet() {
        System.out.println("Testing get-set");
        ArrayQueueModule.push(1);
        ArrayQueueModule.push(2);
        ArrayQueueModule.push(3);
        Assertions.assertEquals(2, ArrayQueueModule.get(1));
        ArrayQueueModule.set(1, "100");
        Assertions.assertEquals("100", ArrayQueueModule.get(1));
    }
    
    @AfterAll
    static void report() {
        System.out.println("Tests successful");
    }

}

