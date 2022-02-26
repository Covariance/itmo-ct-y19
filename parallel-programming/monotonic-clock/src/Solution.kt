/**
 @author Martynov Pavel
 */

class Solution : MonotonicClock {
    private var c1 by RegularInt(0)
    private var c2 by RegularInt(0)
    private var c3 by RegularInt(0)

    private var l1 by RegularInt(0)
    private var l2 by RegularInt(0)

    override fun write(time: Time) {
        c1 = time.d1
        c2 = time.d2
        c3 = time.d3

        l2 = time.d2
        l1 = time.d1
    }

    override fun read(): Time {
        val l1V = l1
        val l2V = l2

        val c3V = c3
        val c2V = c2
        val c1V = c1

        if (c1V == l1V && c2V == l2V) {
            return Time(c1V, c2V, c3V)
        }

        if (c1V == l1V) {
            return Time(c1V, c2V, 0)
        }

        return Time(c1V, 0, 0)
    }
}