import kotlinx.atomicfu.AtomicRef
import kotlinx.atomicfu.atomic
import kotlin.coroutines.Continuation
import kotlin.coroutines.resume
import kotlin.coroutines.suspendCoroutine

class SynchronousQueueMS<E> : SynchronousQueue<E> {
    private val head: AtomicRef<Node<E>>
    private val tail: AtomicRef<Node<E>>

    init {
        val dummy = Sender<E>(null)
        head = atomic(dummy)
        tail = atomic(dummy)
    }

    private open class Node<E>(v: E?) {
        val value = atomic(v)
        val next: AtomicRef<Node<E>?> = atomic(null)
        var continuation: Continuation<Boolean>? = null
    }

    private class Sender<E>(v: E?) : Node<E>(v)
    private class Receiver<E>(v: E?) : Node<E>(v)

    // Small disclaimer -- I really don't know how to extract that insane amount of copy-paste from send and receive
    // I tried so hard and got so far but in the end it isn't even smaller (by line count)
    override suspend fun send(element: E) {
        val node = Sender(element)

        while (true) {
            val curHead = head.value
            val curTail = tail.value

            if ((curTail is Sender<*> || curHead == curTail) && check(curTail, node)) {
                return
            }

            val next = curHead.next.value
            if (next == null || curTail != tail.value || curHead != head.value) {
                continue
            }

            if (next is Receiver<*> && next.continuation != null && head.compareAndSet(curHead, next)) {
                next.value.value = element
                next.continuation!!.resume(true)
                return
            }
        }
    }

    override suspend fun receive(): E {
        val node: Node<E> = Receiver(null)

        while (true) {
            val curHead = head.value
            val curTail = tail.value

            if ((curTail is Receiver<*> || curHead == curTail) && check(curTail, node)) {
                return node.value.value!!
            }

            val next = curHead.next.value
            if (next == null || curHead == tail.value || curTail != tail.value || curHead != head.value) {
                continue
            }

            val element = next.value.value ?: continue
            if (next is Sender<*> && next.continuation != null && head.compareAndSet(curHead, next)) {
                next.value.value = null
                next.continuation!!.resume(true)
                return element
            }
        }
    }

    private suspend fun check(curTail: Node<E>, node: Node<E>): Boolean {
        return suspendCoroutine sc@{ cont ->
            node.continuation = cont
            if (!curTail.next.compareAndSet(null, node)) {
                cont.resume(false)
                return@sc
            }

            tail.compareAndSet(curTail, node)
        }
    }
}
