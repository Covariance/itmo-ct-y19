# LRU Cache

This is a simple implementation of a Least Recently Used Cache
that satisfies the following interface:

```golang
type LRUCache[K comparable, V any] interface {
 Get(key K) *V
 Put(key K, value V)
}
```

## Implementation

Implementation is done using double-linked list and a hashmap.

## Testing

Test coverage is 100%, and the special wrapper type is introduced to check
how the invariants of the type hold after each operation,
as Golang does not have assertions that are no-op in runtime.
