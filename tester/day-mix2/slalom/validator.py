#!/usr/bin/python3
import re, sys

line_no = 0

def next_line():
    global line_no
    line_no += 1
    return sys.stdin.readline()

def my_assert(condition, message):
    if not condition:
        print('line {}: {}'.format(line_no, message))
        sys.exit(1)

def assert_syntax(line, syntax):
    my_assert(re.match(syntax, line), 'incorrect syntax (expected "{}")'.format(syntax))

def assert_range(n, identifier, lower_bound, upper_bound):
    my_assert(lower_bound <= n <= upper_bound,
              '{} not in range [{}, {}]'.format(identifier, lower_bound, upper_bound))

number = r'(0|[1-9][0-9]*)'

line = next_line()
assert_syntax(line, '^{0}$'.format(number))
n = int(line)
assert_range(n, 'n', 1, 10**5)

X = set()
for i in range(n):
    line = next_line()
    assert_syntax(line, '^{0} {0} {0}$'.format(number))
    x, y1, y2 = map(int, line.split())
    assert_range(x, 'x', 0, 10**9)
    assert_range(y1, 'y1', 0, 10**9)
    assert_range(y2, 'y2', 0, 10**9)
    my_assert(x not in X, 'a repeated x-coordinate')
    X.add(x)
    my_assert(y1 <= y2, 'y1 > y2')

line = next_line()
my_assert(line == '', 'redundant characters at the end')
