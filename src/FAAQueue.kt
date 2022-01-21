import kotlinx.atomicfu.AtomicRef
import kotlinx.atomicfu.atomic
import kotlinx.atomicfu.atomicArrayOfNulls

class FAAQueue<T> {
    private val head: AtomicRef<Segment> // Head pointer, similarly to the Michael-Scott queue (but the first node is _not_ sentinel)
    private val tail: AtomicRef<Segment> // Tail pointer, similarly to the Michael-Scott queue

    init {
        val firstNode = Segment()
        head = atomic(firstNode)
        tail = atomic(firstNode)
    }

    /**
     * Adds the specified element [x] to the queue.
     */
    fun enqueue(x: T) {
        var tail = this.tail.value
        var enqInd = tail.enqIdx.getAndIncrement()
        while (true) {
            if (enqInd >= SEGMENT_SIZE) { // We jump over segment border
                val isClear = tail.next.compareAndSet(null, Segment(x))
                this.tail.compareAndSet(tail, tail.next.value!!)
                if (isClear) {
                    return
                }
            } else if (tail.elements[enqInd].compareAndSet(null, x)) {
                // Expect not to be written to, otherwise try again
                return
            }

            // Enqueue in this step failed, trying again (this is a weird get)
            tail = this.tail.value
            enqInd = tail.enqIdx.getAndIncrement()
        }
    }

    /**
     * Retrieves the first element from the queue
     * and returns it; returns `null` if the queue
     * is empty.
     */
    fun dequeue(): T? {
        var head = this.head.value
        var deqInd = head.deqIdx.getAndIncrement()
        while (true) {
            if (deqInd >= SEGMENT_SIZE) {
                val nextHead = head.next.value ?: return null
                this.head.compareAndSet(head, nextHead)
            } else {
                // I really don't like how this marker is not, for example, from enum of states, and therefore
                // we have to use Segment with Any inside
                val res = head.elements[deqInd].getAndSet(DONE)
                if (res != null) {
                    @Suppress("UNCHECKED_CAST")
                    return res as T?
                }
            }

            head = this.head.value
            deqInd = head.deqIdx.getAndIncrement()
        }
    }

    /**
     * Returns `true` if this queue is empty;
     * `false` otherwise.
     */
    val isEmpty: Boolean get() {
        while (true) {
            if (head.value.isEmpty) {
                // Just a little tweak to adapt to reference
                // btw it probably does not work at all
                if (head.value.next.value == null) {
                    return true
                }
                head.value = head.value.next.value!!
                continue
            } else {
                return false
            }
        }
    }
}

// Again, I don't like that we cannot make it generic, like Segment<T>
//
// Small proposal: how about we make SEGMENT_SIZE just a default argument in a constructor getting size? Like this:
//
// constructor(size: Int = SEGMENT_SIZE) {
//     this.size = size
//     this.elements = atomicArrayOfNulls(size)
// }
//
// constructor(x: Any?, size: Int = SEGMENT_SIZE) : this(size = size) {
//     enqIdx.incrementAndGet()
//     elements[0].getAndSet(x)
// }
//
// That would make out class a bit more real-life usable.
private class Segment {
    val next: AtomicRef<Segment?> = atomic(null)
    val enqIdx = atomic(0) // index for the next enqueue operation
    val deqIdx = atomic(0) // index for the next dequeue operation
    val elements = atomicArrayOfNulls<Any>(SEGMENT_SIZE)

    constructor() {
    }

    constructor(x: Any?) {
        enqIdx.incrementAndGet()
        elements[0].getAndSet(x)
    }

    val isEmpty: Boolean get() = deqIdx.value >= enqIdx.value || deqIdx.value >= SEGMENT_SIZE
}

private val DONE = Any() // Marker for the "DONE" slot state; to avoid memory leaks
const val SEGMENT_SIZE = 2 // DO NOT CHANGE, IMPORTANT FOR TESTS

