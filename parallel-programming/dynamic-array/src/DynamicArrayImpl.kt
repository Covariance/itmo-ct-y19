import kotlinx.atomicfu.*

class DynamicArrayImpl<E> : DynamicArray<E> {
    private val core = atomic(Core(INITIAL_CAPACITY))

    // This is a whole lock for recreating the array because we are not actually helping with copy
    private val copyLock: AtomicBoolean = atomic(false)

    override fun get(index: Int): E {
        val currentCore = core.value
        if (index >= currentCore.size.value) {
            throw IllegalArgumentException("Index out of range: $index")
        }

        val value = currentCore.array[index].value ?: throw IllegalArgumentException("Index out of range: $index")
        if (value is Frozen) {
            @Suppress("UNCHECKED_CAST")
            return value.frozen as E
        }
        @Suppress("UNCHECKED_CAST")
        return value as E
    }

    override fun put(index: Int, element: E) {
        while (true) {
            val currentCore = core.value
            if (index >= currentCore.size.value) {
                throw IllegalArgumentException("Index out of range: $index")
            }

            val value = currentCore.array[index].value ?: throw IllegalArgumentException("Index out of range: $index")
            if (value is Frozen) {
                // In real-life implementation here we would help with transition, but no hands - no candies
                continue
            }
            if (core.value.array[index].compareAndSet(value, element)) {
                return
            }
        }
    }

    private fun resize(currentCore: Core) {
        if (!copyLock.compareAndSet(expect = false, update = true)) {
            return
        }

        val newCore = Core(currentCore.capacity * 2)
        for (i in 0 until currentCore.capacity) {
            while (true) {
                // We '!!' here because if there's a 'null' in the Core then our algorithm failed somewhere
                val value = currentCore.array[i].value!!
                if (currentCore.array[i].compareAndSet(expect = value, update = Frozen(value))) {
                    newCore.array[i].value = value
                    break
                }
            }
        }
        newCore.size.value = currentCore.capacity
        core.compareAndSet(currentCore, newCore)

        copyLock.compareAndSet(expect = true, update = false)
    }

    override fun pushBack(element: E) {
        while (true) {
            val currentCore = core.value
            val currentSize = currentCore.size.value
            if (currentSize == currentCore.capacity) {
                resize(currentCore)
            } else if (currentCore.array[currentSize].compareAndSet(expect = null, update = element)) {
                currentCore.size.incrementAndGet()
                return
            }
        }
    }

    override val size: Int get() = core.value.size.value

}

class Core(val capacity: Int) {
    val size = atomic(0)
    val array = atomicArrayOfNulls<Any?>(capacity)
}

private class Frozen(val frozen: Any)

private const val INITIAL_CAPACITY = 1 // DO NOT CHANGE ME
