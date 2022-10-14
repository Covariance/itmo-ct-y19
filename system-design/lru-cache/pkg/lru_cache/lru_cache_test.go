package lrucache

import (
	"fmt"
	"math/rand"
	"strconv"
	"testing"

	"github.com/stretchr/testify/assert"
	"github.com/stretchr/testify/require"
)

func CheckLRUCacheInvariant[K comparable, V any](t *testing.T, lru *LRUCacheImpl[K, V]) {
	t.Helper()

	// Checking length and correctness of double-linked list:
	length := 0
	for node := lru.head; node != lru.tail; node = node.next {
		length++

		require.NotNil(t, node.next, "Linked list is broken")
	}
	assert.LessOrEqual(t, length, lru.capacity, "Linked list length is out of bounds")

	// Checking correctness of list elements
	for node := lru.head; node != lru.tail; node = node.next {
		nodeInMap, ok := lru.values[node.key]
		assert.True(t, ok, "Node in linked list is not in value map")
		assert.Equal(t, node, nodeInMap, "Value points to incorrect node")
	}
}

type LRUCacheForTesting[K comparable, V any] struct {
	lru *LRUCacheImpl[K, V]
	t   *testing.T
}

func (r *LRUCacheForTesting[K, V]) Get(key K) *V {
	result := r.lru.Get(key)
	CheckLRUCacheInvariant(r.t, r.lru)
	return result
}

func (r *LRUCacheForTesting[K, V]) Put(key K, value V) {
	r.lru.Put(key, value)
	CheckLRUCacheInvariant(r.t, r.lru)
}

func ConstructForTesting[K comparable, V any](t *testing.T, capacity int) *LRUCacheForTesting[K, V] {
	result := &LRUCacheForTesting[K, V]{
		lru: Construct[K, V](capacity),
		t:   t,
	}
	CheckLRUCacheInvariant(result.t, result.lru)
	return result
}

func TestOneCapacity(t *testing.T) {
	lru := ConstructForTesting[int, string](t, 1)

	lru.Put(1, "1")

	value := lru.Get(1)

	assert.Equal(t, *value, "1", "Value in cache is incorrect")

	lru.Put(2, "2")

	value = lru.Get(1)

	assert.Nil(t, value, "Displacement has not happened")
}

func TestDisplacementCorrectness(t *testing.T) {
	lru := ConstructForTesting[int, string](t, 2)

	lru.Put(1, "1")
	lru.Put(2, "2")
	lru.Get(1) // Making 1 last recently used
	lru.Put(3, "3")

	value_1 := lru.Get(1)
	value_2 := lru.Get(2)
	value_3 := lru.Get(3)

	assert.Equal(t, "1", *value_1)
	assert.Nil(t, value_2)
	assert.Equal(t, "3", *value_3)
}

func TestOverwriteCorrectness(t *testing.T) {
	lru := ConstructForTesting[int, string](t, 2)

	lru.Put(1, "1")
	lru.Put(2, "2")
	lru.Put(1, "0x1")

	value_1 := lru.Get(1)
	value_2 := lru.Get(2)

	assert.Equal(t, "0x1", *value_1)
	assert.Equal(t, "2", *value_2)
}

func TestNoDisplacements(t *testing.T) {
	lru := ConstructForTesting[int, string](t, 100)

	for i := 0; i != 100; i++ {
		lru.Put(i, strconv.Itoa(i))
	}

	for i := 0; i != 10_000; i++ {
		key := rand.Intn(100)

		value := lru.Get(key)

		assert.Equal(t, strconv.Itoa(key), *value)
	}
}

func TestInabilityToCreateIncorrectCapacity(t *testing.T) {
	incorrectCapacities := []int{0, -1, -100}

	for _, capacity := range incorrectCapacities {
		t.Run(fmt.Sprintf("capacity %d", capacity), func(t *testing.T) {
			defer func() {
				if r := recover(); r == nil {
					require.Fail(t, "This should panic")
				}
			}()

			Construct[int, int](capacity)
		})
	}
}
