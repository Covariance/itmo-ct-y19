package dijkstra

import java.util.*
import java.util.concurrent.Phaser
import java.util.concurrent.ThreadLocalRandom
import java.util.concurrent.atomic.AtomicInteger
import java.util.concurrent.locks.ReentrantLock
import kotlin.concurrent.thread

private val NODE_DISTANCE_COMPARATOR = Comparator<Node> { o1, o2 -> o1!!.distance.compareTo(o2!!.distance) }

class MultiQueue<E>(qsc: Int, private val cmp: Comparator<E>) {
    private val qs: Array<PriorityQueue<E>> = Array(qsc) { PriorityQueue(cmp) }
    private val locks: Array<ReentrantLock> = Array(qsc) { ReentrantLock() }

    private fun lock(): Pair<Int, Int> {
        var a = ThreadLocalRandom.current().nextInt(0, qs.size)
        var b = ThreadLocalRandom.current().nextInt(0, qs.size)

        while (b == a) {
            b = ThreadLocalRandom.current().nextInt(0, qs.size)
        }

        if (a > b) {
            a = b.also { b = a }
        }

        locks[a].lock()
        locks[b].lock()

        return Pair(a, b)
    }

    private fun unlock(which: Pair<Int, Int>) {
        locks[which.second].unlock()
        locks[which.first].unlock()
    }

    fun add(el: E) {
        val (a, b) = lock()

        if (qs[a].size < qs[b].size) {
            qs[a].add(el)
        } else {
            qs[b].add(el)
        }

        unlock(Pair(a, b))
    }

    fun poll(): E? {
        val (a, b) = lock()

        val topA = qs[a].peek()
        val topB = qs[b].peek()
        if (topA == null && topB == null) {
            unlock(Pair(a, b))
            return null
        }
        if (topA == null) {
            qs[b].poll()
            unlock(Pair(a, b))
            return topB
        }
        if (topB == null) {
            qs[a].poll()
            unlock(Pair(a, b))
            return topA
        }

        val result = (if (cmp.compare(topA, topB) < 0) qs[a] else qs[b]).poll()

        unlock(Pair(a, b))

        return result
    }
}

// Returns `Integer.MAX_VALUE` if a path has not been found.
fun shortestPathParallel(start: Node) {
    val workers = Runtime.getRuntime().availableProcessors()
    // The distance to the start node is `0`
    start.distance = 0
    // Create a priority (by distance) queue and add the start node into it
    val q = MultiQueue(4, NODE_DISTANCE_COMPARATOR)
    q.add(start)
    // Run worker threads and wait until the total work is done
    val onFinish = Phaser(workers + 1) // `arrive()` should be invoked at the end by each worker
    val activeNodes = AtomicInteger(1)
    repeat(workers) {
        thread {
            while (activeNodes.get() > 0) {
                val cur = q.poll() ?: continue
                for (e in cur.outgoingEdges) {
                    // println("edge from " + cur.toString() + " to " + e.to.toString() + " with weight " + e.weight.toString())
                    while (true) {
                        val dst = e.to.distance
                        if (dst > cur.distance + e.weight) {
                            if (e.to.casDistance(dst, cur.distance + e.weight)) {
                                q.add(e.to)
                                activeNodes.incrementAndGet()
                                break
                            }
                        } else {
                            break
                        }
                    }
                }
                activeNodes.decrementAndGet()
            }
            onFinish.arrive()
        }
    }
    onFinish.arriveAndAwaitAdvance()
}