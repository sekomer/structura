import unittest
from structura import Queue


class TestQueue(unittest.TestCase):
    def test_queue_enqueue(self):
        q = Queue(1000)
        for i in range(1000):
            q.enqueue(f'qwerqwer[{i}]]')
        self.assertEqual(q.size, 1000)

    def test_queue_peek(self):
        q = Queue(32)
        for i in range(32):
            q.enqueue(f'qwerqwer[{i}]]')
        self.assertEqual(q.peek(), 'qwerqwer[0]]')

    def test_queue_dequeue(self):
        q = Queue(32)
        for i in range(32):
            q.enqueue(f'qwerqwer[{i}]]')
        self.assertEqual(q.dequeue(), 'qwerqwer[0]]')
        self.assertEqual(q.size, 31)

    def test_queue_is_empty(self):
        q = Queue(32)
        self.assertTrue(q.is_empty())
        q.enqueue('qwerqwer')
        self.assertFalse(q.is_empty())
        q.dequeue()
        self.assertTrue(q.is_empty())

    def test_queue_is_full(self):
        q = Queue(32)
        self.assertFalse(q.is_full())
        for i in range(32):
            q.enqueue(f'qwerqwer[{i}]]')
        self.assertTrue(q.is_full())
        q.dequeue()
        self.assertFalse(q.is_full())

    def test_queue_size(self):
        q = Queue(32)
        self.assertEqual(q.size, 0)
        for i in range(32):
            q.enqueue(f'qwerqwer[{i}]]')
        self.assertEqual(q.size, 32)
        q.dequeue()
        self.assertEqual(q.size, 31)

    def test_queue_dequeue_when_empty(self):
        q = Queue(32)
        self.assertRaises(IndexError, q.dequeue)

    def test_queue_peek_when_empty(self):
        q = Queue(32)
        self.assertRaises(IndexError, q.peek)

    def test_queue_enqueue_when_full(self):
        q = Queue(32)
        for i in range(32):
            q.enqueue(f'qwerqwer[{i}]]')
        self.assertRaises(IndexError, q.enqueue, 'qwerqwer')


if __name__ == '__main__':
    unittest.main()
