
from gggg import *

a = Assignment(15, 8)
s = State(a)

horizontal_rule()

s.reject_if_missing_contributors()
s.reject_if_starter_contributors()

s.reject_unless_files_exist(['product.py',
                             'product_test.py'])

s.reject_if_file_unchanged('product.py',
                           '63779f91c7a3ed2fbc2c4115b2cb73ac69ab5d752e838cb0f50c1326110b2fe8')

s.reject_if_file_changed('product_test.py',
                         '6fb16922a78ea57baa69ad6aa441d57e25b57e07049ce93032bee5e3d8a75d8c')

s.reject_unless_python_loads('product.py')

s.string_removed_test('TODO comments removed', 3, 'TODO', ['product.py'])

s.unittest_test('product_test.TestProduct.test_positive', 3)
s.unittest_test('product_test.TestProduct.test_negative', 3)
s.unittest_test('product_test.TestProduct.test_zero', 3)
s.unittest_test('product_test.TestProduct.test_identity', 3)

s.summarize()
