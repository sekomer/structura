import unittest
from structura import HashMap


class TestHashMap(unittest.TestCase):
    def test_hashmap_put(self):
        hm = HashMap(1000)
        for i in range(1000):
            hm.put(f'qwerqwer[{i}]]', i)
        self.assertEqual(hm.size, 1000)

    def test_load_factor(self):
        hm = HashMap(1000, 0.4)
        for i in range(400):
            hm.put(f'qwerqwer[{i}]]', i)
        self.assertEqual(hm.size, 400)

    def test_hashmap_get(self):
        hm = HashMap()
        for i in range(32):
            hm.put(f'brrrr[{i}]]', i)
        self.assertEqual(hm.get('brrrr[0]]'), 0)

    def test_hashmap_remove(self):
        hm = HashMap()
        for i in range(32):
            hm.put(f'yesyesyes[{i}]]', i)
        self.assertEqual(hm.remove('yesyesyes[0]]'), None)
        self.assertEqual(hm.size, 31)

    def test_hashmap_size(self):
        hm = HashMap()
        self.assertEqual(hm.size, 0)
        for i in range(32):
            hm.put(f'qwerqwer[{i}]]', i)
        self.assertEqual(hm.size, 32)
        hm.remove('qwerqwer[0]]')
        self.assertEqual(hm.size, 31)

    def test_hashmap_remove_when_empty(self):
        hm = HashMap()
        self.assertRaises(KeyError, hm.remove, 'qwerqwer')

    def test_hashmap_get_when_empty(self):
        hm = HashMap()
        self.assertRaises(KeyError, hm.get, 'qwerqwer')

    def test_remove_unhashable(self):
        hm = HashMap()
        self.assertRaises(TypeError, hm.remove, [1, 2, 3])


if __name__ == '__main__':
    unittest.main()
