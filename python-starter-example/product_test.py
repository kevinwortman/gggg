
import product
import unittest

class TestProduct(unittest.TestCase):
    def test_positive(self):
        self.assertEqual(product.product(2, 3), 6)
        self.assertEqual(product.product(1, 10), 10)

    def test_negative(self):
        self.assertEqual(product.product(-3, 4), -12)
        self.assertEqual(product.product(5, -6), -30)
        self.assertEqual(product.product(-7, -8), 56)

    def test_zero(self):
        self.assertEqual(product.product(5, 0), 0)
        self.assertEqual(product.product(0, 6), 0)
        self.assertEqual(product.product(-5, 0), 0)
        self.assertEqual(product.product(0, -6), 0)
        self.assertEqual(product.product(0, 0), 0)

    def test_identity(self):
        self.assertEqual(product.product(1, 11), 11)
        self.assertEqual(product.product(12, 1), 12)
        self.assertEqual(product.product(1, 1), 1)
        self.assertEqual(product.product(1, 0), 0)

if __name__ == '__main__':
    unittest.main()
