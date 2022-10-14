package lrucache

import (
	"testing"

	"github.com/stretchr/testify/assert"
	"github.com/stretchr/testify/require"
)

func CheckLRUCacheInvariant[K comparable, V any](t *testing.T, lru *LRUCache[K, V]) {
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
