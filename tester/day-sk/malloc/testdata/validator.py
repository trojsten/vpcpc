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
assert_syntax(line, '^{0} {0}$'.format(number))
n, q = map(int, line.split())
assert_range(n, 'n', 1, 3 * 10**5)
assert_range(q, 'q', 1, 3 * 10**5)

for i in range(q):
    line = next_line()
    assert_syntax(line, '^(1 {0}|2 {0} {0})$'.format(number))
    Q = list(map(int, line.split()))
    if Q[0] == 1:
        assert_range(Q[1], 'c', 1, n)
    else:
        assert_range(Q[1], 'u', 0, n - 1)
        assert_range(Q[2], 'el', 1, n - Q[1])

line = next_line()
my_assert(line == '', 'redundant characters at the end')
