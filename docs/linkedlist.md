# **Linked List**

## **What is a Linked List?**

A Linked List is a data structure that stores items in a linear order. Each item in the list contains a reference to the next item in the list. The first item in the list is called the head, and the last item is called the tail.

## **What is a Doubly Linked List?**

A Doubly Linked List is a data structure that stores items in a linear order. Each item in the list contains a reference to the next item in the list, as well as the previous item in the list. The first item in the list is called the head, and the last item is called the tail.

> **Note:** `structura` use a Doubly Linked List for its implementation of a Linked List.

## **Why use a Linked List?**

A Linked List can be used to implement a Stack or Queue. It can also be used as a building block for other data structures, such as a Graph or Binary Tree. They can also be used instead of Arrays when you need constant time insertions/deletions, when the size of the list is uncertain.

## **Time Complexity**

| Operation       | Time Complexity |
| --------------- | --------------- |
| `append()`      | O(1)            |
| `prepend()`     | O(1)            |
| `insert()`      | O(n)            |
| `bulk_append()` | O(n)            |
| `pop()`         | O(1)            |
| `popat()`       | O(n)            |
| `popleft()`     | O(1)            |
| `remove()`      | O(n)            |
| `get()`         | O(n)            |
| `set()`         | O(n)            |
| `find()`        | O(n)            |
| `head()`        | O(1)            |
| `tail()`        | O(1)            |
| `is_empty()`    | O(1)            |
| `clear()`       | O(n)            |
| `size`          | O(1)            |

## **Space Complexity**

The space complexity of a Linked List is O(n), where n is the number of items in the list.

## **Creating a Linked List**

To create a Linked List, you must specify the type of items it will hold.

```Python
from structura import LinkedList

ll = LinkedList() # []
```

## **Appending an item**

`append()` will add an item to the end of the list.

```python
ll.append(1) # [1]
ll.append(2) # [1, 2]
ll.append(3) # [1, 2, 3]
```

## **Prepending an item**

`prepend()` will add an item to the beginning of the list.

```python
ll.prepend(0) # [0, 1, 2, 3]
ll.prepend(-1) # [-1, 0, 1, 2, 3]
```

## **Inserting an item**

`insert()` will add an item at a specified index.

```python
ll.insert(2, 1.5) # [-1, 0, 1, 1.5, 2, 3]
```

## **Bulk appending items**

`bulk_append()` will add multiple items to the end of the list. Its only faster than appending items one by one if you are appending too many items.

```python
ll.bulk_append([4, 5, 6]) # [-1, 0, 1, 1.5, 2, 3, 4, 5, 6]
```

## **Popping an item**

`pop()` will remove the last item in the list and return it.

```python
ll.pop() # [-1, 0, 1, 1.5, 2, 3, 4, 5]
```

## **Popat an item**

`popat()` will remove an item at a specified index and return it.

```python
ll.popat(0) # [0, 1, 1.5, 2, 3, 4, 5]
```

## **Popleft an item**

`popleft()` will remove the first item in the list and return it.

```python
ll.popleft() # [1, 1.5, 2, 3, 4, 5]
```

## **Removing an item**

`remove()` will remove the first occurrence of an item in the list.

```python
ll.remove(1) # [1.5, 2, 3, 4, 5]
```

## **Getting an item**

`get()` will return the item at a specified index.

```python
ll.get(0) # 1.5
ll.get(1) # 2
```

## **Setting an item**

`set()` will set the item at a specified index.

```python
ll.set(0, 1) # [1, 2, 3, 4, 5]
ll.set(1, 2) # [1, 2, 3, 4, 5]
```

## **Finding an item**

`find()` will return the index of the first occurrence of an item in the list.

```python
ll.find(1) # 0
ll.find(2) # 1
```

## **Getting the size**

`size` attribute will return the number of items in the list.

```python
ll.size # 5
```

## **Getting the head**

`head()` will return the first item in the list.

```python
ll.head() # 1
```

## **Getting the tail**

`tail()` will return the last item in the list.

```python
ll.tail() # 5
```

## **Is the list empty?**

`is_empty()` will return `True` if the list is empty, and `False` otherwise.

```python
ll.is_empty() # False
```

## **Clearing the list**

`clear()` will remove all items from the list.

```python
ll.clear() # []
```
