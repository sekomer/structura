# **PriorityQueue**

## **What is a PriorityQueue?**

A PriorityQueue is a data structure that stores items based on their priority. Items with a higher priority are dequeued before items with a lower priority. If two items have the same priority, they are dequeued in the order they were enqueued. The lower the priority number, the higher the priority.

## **Why use a PriorityQueue?**

A PriorityQueue is useful when you need to store items in order, but you also need to be able to quickly remove the item with the highest priority.

## **Time Complexity**

| Operation  | Time Complexity |
| ---------- | --------------- |
| `push()`   | `O(n)`          |
| `pop()`    | `O(1)`          |
| `peek()`   | `O(1)`          |
| `clear()`  | `O(n)`          |
| `is_empty` | `O(1)`          |
| `size`     | `O(1)`          |

## **Creating a PriorityQueue**

To create a PriorityQueue, you can use the `PriorityQueue()` constructor.

```python
from structura import PriorityQueue

pq = PriorityQueue() # []
```

## **Pushing an item**

`push()` will add an item to the PriorityQueue. The first argument is the data, and the second argument is the priority.

```python
pq.push(1, 1) # [(1, 1)]
pq.push(2, 2) # [(1, 1), (2, 2)]
pq.push(3, 3) # [(1, 1), (2, 2), (3, 3)]
```

## **Popping an item**

`pop()` will remove the item with the highest priority. It will return the data and the priority.

```python
pq.pop() # (1, 1), [(2, 2), (3, 3)]
pq.pop() # (2, 2), [(3, 3)]
pq.pop() # (3, 3), []
```

## **Peeking at the front of the PriorityQueue**

`peek()` will return the item at the front of the PriorityQueue. It will return the data and the priority.

```python
pq.peek() # (1, 1), [(1, 1), (2, 2), (3, 3)]
```

## **Clearing the PriorityQueue**

`clear()` will remove all items from the PriorityQueue.

```python
pq.clear() # []
```

## **Checking if the PriorityQueue is empty**

`is_empty` will return True if the PriorityQueue is empty, and False if it is not.

```python
pq = PriorityQueue()
pq.is_empty # True
pq.push(1, 1)
pq.is_empty # False
```

## **Getting the size of the PriorityQueue**

`size` will return the number of items in the PriorityQueue.

```python
pq.size # 3
```
