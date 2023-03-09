import unittest
from structura import RingBuffer


class TestRingBuffer(unittest.TestCase):
    def test_ringbuffer_enqueue(self):
        rb = RingBuffer(100)
        for i in range(1000):
            rb.enqueue(f'qwerqwer[{i}]]')
        self.assertEqual(rb.size(), 100)

    def test_ringbuffer_peek(self):
        rb = RingBuffer(32)
        for i in range(32):
            rb.enqueue(f'qwerqwer[{i}]]')
        self.assertEqual(rb.peek(), 'qwerqwer[0]]')

    def test_ringbuffer_dequeue(self):
        rb = RingBuffer(32)
        for i in range(32):
            rb.enqueue(f'qwerqwer[{i}]]')
        self.assertEqual(rb.dequeue(), 'qwerqwer[0]]')
        self.assertEqual(rb.size(), 31)

    def test_ringbuffer_is_empty(self):
        rb = RingBuffer(32)
        self.assertTrue(rb.is_empty())
        rb.enqueue('qwerqwer')
        self.assertFalse(rb.is_empty())
        rb.dequeue()
        self.assertTrue(rb.is_empty())

    def test_ringbuffer_is_full(self):
        rb = RingBuffer(32)
        self.assertFalse(rb.is_full())
        for i in range(32):
            rb.enqueue(f'qwerqwer[{i}]]')
        self.assertTrue(rb.is_full())
        rb.dequeue()
        self.assertFalse(rb.is_full())

    def test_ringbuffer_size(self):
        rb = RingBuffer(32)
        self.assertEqual(rb.size(), 0)
        for i in range(32):
            rb.enqueue(f'qwerqwer[{i}]]')
        self.assertEqual(rb.size(), 32)
        rb.dequeue()
        self.assertEqual(rb.size(), 31)

    def test_ringbuffer_dequeue_when_empty(self):
        rb = RingBuffer(32)
        self.assertEqual(rb.dequeue(), None)

    def test_ringbuffer_peek_when_empty(self):
        rb = RingBuffer(32)
        self.assertEqual(rb.peek(), None)

    def test_chaos(self):
        rb = RingBuffer(32)
        for i in range(100):
            rb.enqueue(f'qwerqwer[{i}]]')
            rb.peek()
            rb.is_empty()
            rb.is_full()
            rb.size()

        for i in range(1000):
            rb.dequeue()
            rb.peek()
            rb.is_empty()
            rb.is_full()
            rb.size()


if __name__ == '__main__':
    unittest.main()
