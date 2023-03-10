# **RingBuffer**

## **What is a RingBuffer?**

A RingBuffer is a data structure that is similar to a queue, but with a fixed size. When the buffer is full, adding a new item will overwrite the oldest item in the buffer.

## **Why use a RingBuffer?**

A RingBuffer is useful when you want to keep a fixed number of items, but you don't want to have to worry about removing old items. For example, if you want to keep a log of the last 100 messages sent to a chat server, you could use a RingBuffer to store the messages.

## **Time Complexity**

| Operation    | Time Complexity |
| ------------ | --------------- |
| `enqueue()`  | O(1)            |
| `dequeue()`  | O(1)            |
| `peek()`     | O(1)            |
| `is_empty()` | O(1)            |
| `is_full()`  | O(1)            |
| `size()`     | O(1)            |
| `capacity()` | O(1)            |
| `clear()`    | O(1)            |

## **Space Complexity**

The space complexity of a RingBuffer is O(n), where n is the capacity of the buffer.

## **Creating a RingBuffer**

To create a RingBuffer, you must specify the maximum number of items it can hold.

**Note**: Since the buffer is circular, it will overwrite the oldest item when it is full.

```Python
from structura import RingBuffer

buffer = RingBuffer(3) # capacity of 3
```

## **Getting the capacity**

The capacity of the buffer is the maximum number of items it can hold.

```python
buffer.capacity() # 3
```

## **Getting the size**

The size of the buffer is the number of items it currently holds.

```python
buffer.size() # 0
```

## **Checking if the buffer is empty**

`is_empty()` will return `True` if the buffer is empty, and `False` otherwise.

```python
buffer.is_empty() # True
```

## **Checking if the buffer is full**

`is_full()` will return `True` if the buffer is full, and `False` otherwise.

```python
buffer.is_full() # False
```

## **Adding an item**

Enqueueing an item will add it to the buffer. If the buffer is full, the oldest item will be overwritten.

```python
buffer.enqueue(42)      # [42]
buffer.enqueue([1,2,3]) # [42, [1,2,3]]
buffer.enqueue('foo')   # [42, [1,2,3], 'foo']

# /!\ overwrites the tail
buffer.enqueue({'c': 99}) # [[1,2,3], 'foo', {'c': 99}]
```

## **Removing an item**

Dequeueing an item will remove it from the buffer. If the buffer is empty, an exception will be raised.

```python
buffer.dequeue() # [1,2,3]
buffer.dequeue() # 'foo'
buffer.dequeue() # {'c': 99}

buffer.dequeue() # raises an exception
```

## **Peeking at the next item**

Peeking at the next item will return the next item in the buffer without removing it. If the buffer is empty, an exception will be raised.

```python
buffer.enqueue(42)      # [42]
buffer.enqueue([1,2,3]) # [42, [1,2,3]]
buffer.enqueue('foo')   # [42, [1,2,3], 'foo']

buffer.peek() # 42
buffer.peek() # 42
```

## **Clearing the buffer**

Clearing the buffer will remove all items from the buffer.

```python
buffer.enqueue(42)      # [42]
buffer.enqueue([1,2,3]) # [42, [1,2,3]]
buffer.enqueue('foo')   # [42, [1,2,3], 'foo']

buffer.clear() # []
```
