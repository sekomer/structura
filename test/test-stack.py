import unittest
from structura import Stack


class TestStack(unittest.TestCase):
    def test_stack_push(self):
        s = Stack(1000)
        for i in range(1000):
            s.push(f'qwerqwer[{i}]]')
        self.assertEqual(s.size, 1000)

    def test_stack_peek(self):
        s = Stack(32)
        for i in range(32):
            s.push(f'qwerqwer[{i}]]')
        self.assertEqual(s.peek(), 'qwerqwer[31]]')

    def test_stack_pop(self):
        s = Stack(32)
        for i in range(32):
            s.push(f'qwerqwer[{i}]]')
        self.assertEqual(s.pop(), 'qwerqwer[31]]')
        self.assertEqual(s.size, 31)

    def test_stack_is_empty(self):
        s = Stack(32)
        self.assertTrue(s.is_empty())
        s.push('qwerqwer')
        self.assertFalse(s.is_empty())
        s.pop()
        self.assertTrue(s.is_empty())

    def test_stack_is_full(self):
        s = Stack(32)
        self.assertFalse(s.is_full())
        for i in range(32):
            s.push(f'qwerqwer[{i}]]')
        self.assertTrue(s.is_full())
        s.pop()
        self.assertFalse(s.is_full())

    def test_stack_size(self):
        s = Stack(32)
        self.assertEqual(s.size, 0)
        for i in range(32):
            s.push(f'qwerqwer[{i}]]')
        self.assertEqual(s.size, 32)
        s.pop()
        self.assertEqual(s.size, 31)

    def test_stack_pop_when_empty(self):
        s = Stack(32)
        self.assertRaises(IndexError, s.pop)

    def test_stack_peek_when_empty(self):
        s = Stack(32)
        self.assertRaises(IndexError, s.peek)

    def test_stack_push_when_full(self):
        s = Stack(32)
        for i in range(32):
            s.push(f'qwerqwer[{i}]]')
        self.assertRaises(IndexError, s.push, 'qwerqwer')


if __name__ == '__main__':
    unittest.main()
