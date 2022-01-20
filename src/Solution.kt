/**
 * @author Martynov Pavel
 */

class Solution : AtomicCounter {
    private val current : ThreadLocal<Node> = ThreadLocal.withInitial { root }
    private val root = Node(0)

    private class Node(val value: Int) {
        val next : Consensus<Node> = Consensus()
    }

    override fun getAndAdd(x: Int): Int {
        var old : Int = current.get().value
        val node = Node(old + x)

        current.set(current.get().next.decide(node))

        while (node.value != current.get().value) {
            old = current.get().value
            current.set(current.get().next.decide(Node(old + x)))
        }

        return old
    }
}
