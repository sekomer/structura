import unittest
from structura import LinkedList


class TestLinkedList(unittest.TestCase):
    def test_append(self):
        ll = LinkedList()
        ll.append(1)
        ll.append(2)
        ll.append(3)
        self.assertEqual(ll.head(), 1)
        self.assertEqual(ll.tail(), 3)
        self.assertEqual(ll.size, 3)

    def test_prepend(self):
        ll = LinkedList()
        ll.prepend(1)
        ll.prepend(2)
        ll.prepend(3)
        self.assertEqual(ll.head(), 3)
        self.assertEqual(ll.tail(), 1)
        self.assertEqual(ll.size, 3)

    def test_pop(self):
        ll = LinkedList()
        ll.append(1)
        ll.append(2)
        ll.append(3)
        self.assertEqual(ll.pop(), 3)
        self.assertEqual(ll.pop(), 2)
        self.assertEqual(ll.pop(), 1)
        self.assertEqual(ll.size, 0)
        self.assertRaises(IndexError, ll.pop)

    def test_popleft(self):
        ll = LinkedList()
        ll.append(1)
        ll.append(2)
        ll.append(3)
        self.assertEqual(ll.popleft(), 1)
        self.assertEqual(ll.popleft(), 2)
        self.assertEqual(ll.popleft(), 3)
        self.assertEqual(ll.size, 0)
        self.assertRaises(IndexError, ll.popleft)

    def test_popat(self):
        ll = LinkedList()
        ll.append(1)
        ll.append(2)
        ll.append(3)
        self.assertEqual(ll.popat(0), 1)
        self.assertEqual(ll.popat(0), 2)
        self.assertEqual(ll.popat(0), 3)
        self.assertEqual(ll.size, 0)
        self.assertRaises(IndexError, ll.popat, 0)

    def test_find(self):
        ll = LinkedList()
        ll.append(1)
        ll.append(2)
        ll.append(3)
        self.assertEqual(ll.find(1), 0)
        self.assertEqual(ll.find(2), 1)
        self.assertEqual(ll.find(3), 2)
        self.assertEqual(ll.find(4), -1)

    def test_size(self):
        ll = LinkedList()
        self.assertEqual(ll.size, 0)
        ll.append(1)
        self.assertEqual(ll.size, 1)
        ll.append(2)
        self.assertEqual(ll.size, 2)
        ll.append(3)
        self.assertEqual(ll.size, 3)
        ll.pop()
        self.assertEqual(ll.size, 2)
        ll.pop()
        self.assertEqual(ll.size, 1)
        ll.pop()
        self.assertEqual(ll.size, 0)

    def test_head(self):
        ll = LinkedList()
        self.assertRaises(IndexError, ll.head)
        ll.append(1)
        self.assertEqual(ll.head(), True)
        ll.append(2)
        self.assertEqual(ll.head(), True)
        ll.append(3)
        self.assertEqual(ll.head(), True)
        ll.pop()
        self.assertEqual(ll.head(), True)
        ll.pop()
        self.assertEqual(ll.head(), True)
        ll.pop()
        # self.assertEqual(ll.head(), None)

    def test_tail(self):
        ll = LinkedList()
        self.assertRaises(IndexError, ll.tail)
        ll.append(1)
        self.assertEqual(ll.tail(), 1)
        ll.append(2)
        self.assertEqual(ll.tail(), 2)
        ll.append(3)
        self.assertEqual(ll.tail(), 3)
        ll.pop()
        self.assertEqual(ll.tail(), 2)
        ll.pop()
        self.assertEqual(ll.tail(), 1)
        ll.pop()
        self.assertRaises(IndexError, ll.tail)

    def test_remove(self):
        ll = LinkedList()
        ll.append(100000)
        ll.append(20001231)
        ll.append(3123123123123)
        self.assertEqual(ll.remove(100000), 100000)
        self.assertEqual(ll.remove(20001231), 20001231)
        self.assertEqual(ll.remove(3123123123123), 3123123123123)
        self.assertEqual(ll.size, 0)
        self.assertRaises(IndexError, ll.remove, 31)


if __name__ == '__main__':
    unittest.main()
