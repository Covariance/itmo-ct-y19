import kotlinx.atomicfu.atomic
import kotlinx.atomicfu.atomicArrayOfNulls
import java.util.PriorityQueue
import java.util.concurrent.ThreadLocalRandom

private const val FC_SIZE = 16

class FCPriorityQueue<E : Comparable<E>> {
    private class Completed(val result: Any?)

    private val q = PriorityQueue<E>()
    private val lock = atomic(false)
    private val actions = atomicArrayOfNulls<Any?>(FC_SIZE)

    private fun tryLock(): Boolean {
        return lock.compareAndSet(expect = false, update = true)
    }

    private fun unlock() {
        lock.compareAndSet(expect = true, update = false)
    }

    private fun combine() {
        for (ind in 0 until FC_SIZE) {
            val status = actions[ind].value

            if (status !is Completed && status != null) { // It's an actual operation there!
                @Suppress("UNCHECKED_CAST")
                actions[ind].compareAndSet(status, (status as () -> Completed)())
            }
        }
    }

    private fun <T> act(action: () -> T?): T? {
        // First we try to execute our action
        if (tryLock()) {
            // If we got the lock, then we become the combiner
            val result = action()
            combine()
            return result.also { unlock() }
        }

        // Otherwise, we publish our action to random cell
        var ind = ThreadLocalRandom.current().nextInt(FC_SIZE)

        val wrappedAction: () -> Completed = { Completed(action()) }

        while (!actions[ind].compareAndSet(null, wrappedAction)) {
            // If cell is taken, move to the next one
            ind = (ind + 1) % FC_SIZE
        }

        // And wait for result
        while (true) {
            val status = actions[ind].value

            // Our task is completed by combiner, we can just take it
            if (status is Completed) {
                val result = status.result
                actions[ind].compareAndSet(status, null)
                @Suppress("UNCHECKED_CAST")
                return result as T?
            }

            // Also try to become combiner
            // Do not worry about result, we would take it on next iteration
            if (tryLock()) {
                combine().also { unlock() }
            }
        }
    }

    /**
     * Retrieves the element with the highest priority
     * and returns it as the result of this function;
     * returns `null` if the queue is empty.
     */
    fun poll(): E? {
        return act { q.poll() }
    }

    /**
     * Returns the element with the highest priority
     * or `null` if the queue is empty.
     */
    fun peek(): E? {
        return act { q.peek() }
    }

    /**
     * Adds the specified element to the queue.
     */
    fun add(element: E) {
        act { q.add(element) }
    }
}