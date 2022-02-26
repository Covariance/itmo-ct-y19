import java.util.concurrent.atomic.AtomicReference

class AtomicArray<E>(size: Int, initialValue: E?) {
    // Atomicfu may be optimized and everything, but it's very, VERY inconvenient
    private val a = Array(size) { AtomicReference<Any?>(initialValue) }


    // Repeatedly helps with completing the descriptor or returns value
    private fun getOrHelp(obj: AtomicReference<Any?>): Any? {
        while (true) {
            val current = obj.get()

            if (current is Descriptor) {
                current()
                continue
            }

            return current
        }
    }

    operator fun get(index: Int): E? {
        val current = getOrHelp(a[index])

        @Suppress("UNCHECKED_CAST")
        return current as E?
    }

    operator fun set(index: Int, value: E) {
        while (true) {
            val current = getOrHelp(a[index])

            if (a[index].compareAndSet(current, value)) {
                return
            }
        }
    }

    fun cas(index: Int, expected: E, update: E) = helpingCas(a[index], expected, update)

    private fun helpingCas(obj: AtomicReference<Any?>, expected: Any?, update: Any?, caller: Any? = null): Boolean {
        while (true) {
            val value = obj.get()

            if (value is Descriptor && value !== expected && value !== caller) {
                value()
                continue
            }

            if (value != expected) {
                return false
            }

            if (obj.compareAndSet(expected, update)) {
                return true
            }
        }
    }

    fun cas2(index1: Int, expected1: E, update1: E, index2: Int, expected2: E, update2: E): Boolean {
        if (index1 <= index2) {
            return orderedCas2(a[index1], expected1, update1, a[index2], expected2, update2)
        }

        return orderedCas2(a[index2], expected2, update2, a[index1], expected1, update1)
    }

    // Just a simple marking functional interface
    fun interface Descriptor {
        operator fun invoke()
    }

    // region CAS2
    private fun orderedCas2(
        obj1: AtomicReference<Any?>, expected1: Any?, update1: Any?,
        obj2: AtomicReference<Any?>, expected2: Any?, update2: Any?
    ): Boolean {
        if (obj1 === obj2) {
            if (expected1 == expected2) {
                return helpingCas(obj2, expected2, update2)
            }
            return false
        }

        val descriptor = Cas2Descriptor(obj1, expected1, update1, obj2, expected2, update2)
        if (!helpingCas(obj1, expected1, descriptor)) {
            return false
        }

        descriptor()

        return descriptor.outcome.get() == Cas2Status.SUCCESS
    }

    private inner class Cas2Descriptor(
        val obj1: AtomicReference<Any?>, val expected1: Any?, val update1: Any?,
        val obj2: AtomicReference<Any?>, val expected2: Any?, val update2: Any?
    ) : Descriptor {
        val outcome = AtomicReference<Any?>(Cas2Status.UNDECIDED)

        override operator fun invoke() {
            rdcss(obj2, expected2, this, outcome, Cas2Status.UNDECIDED, this)

            val status = if (obj2.get() === this) Cas2Status.SUCCESS else Cas2Status.FAIL

            outcome.compareAndSet(Cas2Status.UNDECIDED, status)

            if (outcome.get() == Cas2Status.SUCCESS) {
                obj2.compareAndSet(this, update2)
                obj1.compareAndSet(this, update1)
            } else {
                obj2.compareAndSet(this, expected2)
                obj1.compareAndSet(this, expected1)
            }
        }
    }

    private enum class Cas2Status { UNDECIDED, SUCCESS, FAIL }
    // endregion

    // region RDCSS
    // This function is here only for intermediate testing purposes
    fun rdcss(index1: Int, expected1: Any?, update1: Any?, index2: Int, expected2: Any?): Boolean {
        if (index2 > index1) {
            return false
        }

        return rdcss(a[index1], expected1, update1, a[index2], expected2)
    }

    private fun rdcss(
        obj1: AtomicReference<Any?>,
        expected1: Any?,
        update1: Any?,
        obj2: AtomicReference<Any?>,
        expected2: Any?,
        caller: Any? = null
    ): Boolean {
        if (obj1 === obj2) {
            if (expected1 == expected2) {
                return helpingCas(obj1, expected1, update1, caller = caller)
            }
            return false
        }

        val descriptor = RdcssDescriptor(obj1, expected1, update1, obj2, expected2)
        if (!helpingCas(obj1, expected1, descriptor, caller = caller)) {
            return false
        }

        descriptor()

        return descriptor.outcome.get() == RdcssStatus.SUCCESS
    }

    private inner class RdcssDescriptor(
        val obj1: AtomicReference<Any?>,
        val expected1: Any?,
        val update1: Any?,
        val obj2: AtomicReference<Any?>,
        val expected2: Any?
    ) : Descriptor {

        val outcome = AtomicReference(RdcssStatus.UNDECIDED)

        override operator fun invoke() {
            val status = if (obj2.get() === expected2) RdcssStatus.SUCCESS else RdcssStatus.FAIL

            this.outcome.compareAndSet(RdcssStatus.UNDECIDED, status)

            val update = if (this.outcome.get() == RdcssStatus.SUCCESS) update1 else expected1

            obj1.compareAndSet(this, update)
        }
    }

    private enum class RdcssStatus { UNDECIDED, SUCCESS, FAIL }
    // endregion
}
