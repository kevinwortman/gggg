
from gggg import *

a = Assignment(12, 6)
s = State(a)

horizontal_rule()

s.reject_if_missing_contributors()
s.reject_if_starter_contributors()

s.reject_unless_files_exist(['product.hpp',
                             'product_test.cpp'])

s.reject_if_file_unchanged('product.hpp',
                           '953ed73434f4cae54b9161b48da2f25a2622522198a655c00de571bb596b16df')

s.reject_if_file_changed('product_test.cpp',
                         '0139691ee712697636a51e979b866b4a939f7840032fc81208f22c8931f90a5d')

s.reject_unless_command_succeeds(['make', 'clean', 'product_test'])

s.string_removed_test('TODO comments removed', 3, 'TODO', ['product.hpp'])

s.gtest_run('product_test')
s.gtest_suite_test('ProductPositive', 3)
s.gtest_suite_test('ProductZero', 3)
s.gtest_suite_test('ProductNegative', 3)

s.summarize()
