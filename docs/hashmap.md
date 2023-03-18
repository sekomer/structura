# **HashMap**

## **What is a HashMap?**

A HashMap is a data structure that stores items in a key-value pair. Each item in the HashMap is hashed to a specific index in the HashMap. The HashMap is implemented as an array of linked lists. When a new item is added to the HashMap, it is hashed to a specific index in the array. If the index is empty, a new linked list is created and the item is added to the list. If the index is not empty, the item is added to the linked list at that index.

## **Why use a HashMap?**

A HashMap can be used to implement a Set. It can also be used as a building block for other data structures, such as a Graph or Binary Tree. They can also be used instead of Arrays when you need constant time insertions/deletions, when the size of the list is uncertain.

## **Time Complexity**

| Operation     | Time Complexity |
| ------------- | --------------- |
| `put()`       | O(1)            |
| `get()`       | O(1)            |
| `remove()`    | O(1)            |
| `keys()`      | O(n)            |
| `size`        | O(1)            |
| `capacity`    | O(1)            |
| `load_factor` | O(1)            |

## **Space Complexity**

The space complexity of a HashMap is O(n), where n is the number of items in the HashMap.

## **Creating a HashMap**

To create a HashMap, you must specify the type of items it will hold.

```Python
from structura import HashMap

hm = HashMap(capacity=10) # {}
```

## **Adding an item**

`put()` will add an item to the HashMap.

```python
hm.put("key", "value") # {"key": "value"}
hm.put("key2", "value2") # {"key": "value", "key2": "value2"}
```

## **Getting an item**

`get()` will return the value of the item with the specified key.

```python
hm.get("key") # "value"
hm.get("key2") # "value2"
```

## **Removing an item**

`remove()` will remove the item with the specified key.

```python
hm.remove("key") # {"key2": "value2"}
hm.remove("key2") # {}
```

## **Getting the keys**

`keys()` will return a list of all the keys in the HashMap.

```python
hm.put("key", "value") # {"key": "value"}
hm.put("key2", "value2") # {"key": "value", "key2": "value2"}
hm.keys() # ["key", "key2"]
```

## **Getting the size**

`size` will return the number of items in the HashMap.

```python
hm.put("key", "value") # {"key": "value"}
hm.put("key2", "value2") # {"key": "value", "key2": "value2"}
hm.size # 2
```

## **Getting the capacity**

`capacity` will return the capacity of the HashMap.

```python
hm = HashMap(capacity=32) # {}
hm.capacity # 32
```

## **Getting the load factor**

`load_factor` will return the load factor of the HashMap.

```python
hm = HashMap(capacity=32, load_factor=0.9) # {}
hm.load_factor # 0.9
```
