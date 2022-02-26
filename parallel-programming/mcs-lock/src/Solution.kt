import java.util.concurrent.atomic.AtomicReference

class Solution(private val env: Environment) : Lock<Solution.Node> {
    private val tail = AtomicReference<Node?>(null)

    override fun lock(): Node {
        val node = Node() // сделали узел

        val prev = tail.getAndSet(node)
        if (prev != null) {
            prev.next.set(node)
            while (node.locked.get()) {
                env.park()
            }
        }

        return node // вернули узел
    }

    override fun unlock(node: Node) {
        if (node.next.get() == null) {
            if (tail.compareAndSet(node, null)) {
                return
            } else {
                while (node.next.get() == null) {
                    // активное ожидание
                }
            }
        }
        node.next.get()!!.locked.set(false)
        env.unpark(node.next.get()!!.thread)
    }

    class Node {
        val thread: Thread = Thread.currentThread() // запоминаем поток, которые создал узел
        val next = AtomicReference<Node?>(null)
        val locked = AtomicReference(true)
    }
}