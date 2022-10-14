package lrucache

type LRUCache[K comparable, V any] interface {
	Get(key K) *V
	Put(key K, value V)
}

type LRUCacheImpl[K comparable, V any] struct {
	capacity   int
	head, tail *node[K, V]
	values     map[K]*node[K, V]
}

type node[K, V any] struct {
	prev, next *node[K, V]
	key        K
	value      V
}

func Construct[K comparable, V any](capacity int) *LRUCacheImpl[K, V] {
	if capacity < 1 {
		panic("Cannot construct LRU cache with non-positive capavity")
	}

	return &LRUCacheImpl[K, V]{
		capacity: capacity,
		head:     nil,
		tail:     nil,
		values:   map[K]*node[K, V]{},
	}
}

func (r *LRUCacheImpl[K, V]) append(key K, value V) {
	node := &node[K, V]{
		key:   key,
		value: value,
	}
	if r.tail == nil {
		r.tail = node
		r.head = node
	} else {
		r.tail.next = node
		node.prev = r.tail
		r.tail = node
	}
	r.values[key] = node
}

func (r *LRUCacheImpl[K, V]) use(node *node[K, V]) {
	if node == r.tail {
		return
	}
	if node == r.head {
		r.head = r.head.next
		r.head.prev = nil
	} else {
		node.prev.next = node.next
		node.next.prev = node.prev
	}
	r.tail.next = node
	node.prev = r.tail
	r.tail = r.tail.next
	r.tail.next = nil
}

func (r *LRUCacheImpl[K, V]) Get(key K) *V {
	node, ok := r.values[key]
	if !ok {
		return nil
	}
	r.use(node)
	return &node.value
}

func (r *LRUCacheImpl[K, V]) Put(key K, value V) {
	if _, ok := r.values[key]; ok {
		r.values[key].value = value
		r.use(r.values[key])
		return
	}
	if len(r.values) < r.capacity {
		r.append(key, value)
		return
	}
	node := r.head
	r.use(node)
	delete(r.values, node.key)

	r.values[key] = node
	node.key = key
	node.value = value
}
