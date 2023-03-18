# **Queue**

## **What is a Queue?**

A Queue is a data structure that stores items in a linear order. Items can be added to the end of the queue, and removed from the front of the queue. The first item in the queue is called the head, and the last item is called the tail.

## **Why use a Queue?**

A Queue can be used to implement a Breadth First Search. It can also be used as a building block for other data structures, such as a Graph or Binary Tree. They can also be used instead of Arrays when you need constant time insertions/deletions, when the size of the list is uncertain.

## **Time Complexity**

| Operation    | Time Complexity |
| ------------ | --------------- |
| `enqueue()`  | O(1)            |
| `dequeue()`  | O(1)            |
| `peek()`     | O(1)            |
| `is_empty()` | O(1)            |
| `is_full()`  | O(1)            |
| `clear()`    | O(n)            |
| `capacity`   | O(1)            |
| `size`       | O(1)            |

## **Space Complexity**

The space complexity of a Queue is O(n), where n is the number of items in the queue.

## **Creating a Queue**

To create a Queue, you can use the `Queue()` constructor.

```Python
from structura import Queue

q = Queue(capacity=10) # []
```

## **Enqueueing an item**

`enqueue()` will add an item to the end of the queue.

```python
q.enqueue(1) # [1]
q.enqueue(2) # [1, 2]
q.enqueue(3) # [1, 2, 3]
```

## **Dequeueing an item**

`dequeue()` will remove an item from the front of the queue.

```python
q.dequeue() # [2, 3]
q.dequeue() # [3]
q.dequeue() # []
```

## **Peeking at the front of the queue**

`peek()` will return the item at the front of the queue.

```python
q.enqueue(1) # [1]
q.enqueue(2) # [1, 2]

q.peek() # 1
```

## **Clearing the queue**

`clear()` will remove all items from the queue.

```python
q.enqueue(1) # [1]
q.enqueue(2) # [1, 2]

q.clear() # []
```

## **Checking if the queue is empty**

`is_empty()` will return `True` if the queue is empty, and `False` otherwise.

```python
q.enqueue(1) # [1]
q.enqueue(2) # [1, 2]

q.is_empty() # False
```

## **Checking if the queue is full**

`is_full()` will return `True` if the queue is full, and `False` otherwise.

```python
q.enqueue(1) # [1]
q.enqueue(2) # [1, 2]

q.is_full() # False
```

## **Getting the size of the queue**

`size` will return the number of items in the queue.

```python
q.enqueue(1) # [1]
q.enqueue(2) # [1, 2]

q.size # 2
```

## **Getting the capacity of the queue**

`capacity` will return the maximum number of items the queue can hold.

```python
q.capacity # 10
```
