# **Stack**

## **What is a Stack?**

A Stack is a data structure that stores items in a Last-In-First-Out (LIFO) order. The most recently added item is the first to be removed.

## **Why use a Stack?**

A Stack can be used for evaluating expressions consisting of operands and operators. Stacks can be used for Backtracking, i.e., to check parenthesis matching in an expression. It can also be used to convert one form of expression to another form. It can be used for systematic Memory Management.

## **Time Complexity**

| Operation    | Time Complexity |
| ------------ | --------------- |
| `push()`     | O(1)            |
| `pop()`      | O(1)            |
| `peek()`     | O(1)            |
| `is_empty()` | O(1)            |
| `clear()`    | O(n)            |
| `size`       | O(1)            |
| `capacity`   | O(1)            |

## **Space Complexity**

The space complexity of a Stack is O(n), where n is the capacity of the stack.

## **Creating a Stack**

To create a Stack, you must specify the maximum number of items it can hold.

```Python
from structura import Stack

stack = Stack(3) # capacity of 3
```

## **Getting the capacity**

The capacity of the stack is the maximum number of items it can hold.

```python
stack.capacity # 3
```

## **Getting the size**

The size of the stack is the number of items it currently holds.

```python
stack.size # 0
```

## **Checking if the stack is empty**

`is_empty()` will return `True` if the stack is empty, and `False` otherwise.

```python
stack.is_empty() # True
```

## **Checking if the stack is full**

`is_full()` will return `True` if the stack is full, and `False` otherwise.

```python

stack.is_full() # False
```

## **Adding an item**

`push()` will add an item to the top of the stack.

```python
stack.push(1) # [1]
stack.push(2) # [1, 2]
stack.push(3) # [1, 2, 3]
```

## **Listing all items**

`items()` will return a list of all items in the stack.

```python
stack.items() # [1, 2, 3]
```

## **Removing an item**

`pop()` will remove and return the item at the top of the stack.

```python
stack.pop() # 3
stack.pop() # 2
stack.pop() # 1

stack.pop() # raises an exception
```

## **Peeking at the top item**

`peek()` will return the item at the top of the stack without removing it.

```python
stack.push(1) # [1]
stack.push(2) # [1, 2]
stack.push(3) # [1, 2, 3]

stack.peek() # 3
stack.peek() # 3
```

## **Clearing the stack**

`clear()` will remove all items from the stack.

```python
stack.push(1) # [1]
stack.push(2) # [1, 2]
stack.push(3) # [1, 2, 3]

stack.clear() # []
```
