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
        var new = Node(old + x)

        current.set(current.get().next.decide(new))

        while (new != current.get()) {
            old = current.get().value
            new = Node(old + x)
            current.set(current.get().next.decide(new))
        }

        return old
    }
}
