import unittest
from structura import PriorityQueue


class TestPriorityQueue(unittest.TestCase):
    def test_push(self):
        q = PriorityQueue()
        q.push(1, 1)
        q.push(2, 2)
        q.push(3, 3)
        self.assertEqual(q.size, 3)

    def test_pop(self):
        q = PriorityQueue()
        q.push(1, 12341234)
        q.push(2, 2234234)
        q.push(3, 3434)
        self.assertEqual(q.pop(), (3, 3434))
        self.assertEqual(q.pop(), (2, 2234234))
        self.assertEqual(q.pop(), (1, 12341234))
        self.assertRaises(IndexError, q.pop)

    def test_peek(self):
        q = PriorityQueue()
        q.push(1, 1)
        q.push(2, 2)
        q.push(3, 3)
        self.assertEqual(q.peek(), (1, 1))
        q.pop()
        self.assertEqual(q.peek(), (2, 2))
        q.pop()
        self.assertEqual(q.peek(), (3, 3))
        q.pop()
        self.assertRaises(IndexError, q.peek)

    def test_size(self):
        q = PriorityQueue()
        self.assertEqual(q.size, 0)
        q.push(1, 1)
        self.assertEqual(q.size, 1)
        q.push(2, 2)
        self.assertEqual(q.size, 2)
        q.push(3, 3)
        self.assertEqual(q.size, 3)
        q.pop()
        self.assertEqual(q.size, 2)
        q.pop()
        self.assertEqual(q.size, 1)
        q.pop()
        self.assertEqual(q.size, 0)

    def test_empty(self):
        q = PriorityQueue()
        self.assertTrue(q.is_empty())
        q.push(1, 1)
        self.assertFalse(q.is_empty())
        q.pop()
        self.assertTrue(q.is_empty())

    def test_clear(self):
        q = PriorityQueue()
        q.push(1, 1)
        q.push(2, 2)
        q.push(3, 3)
        q.clear()
        self.assertTrue(q.is_empty())


if __name__ == '__main__':
    unittest.main()
