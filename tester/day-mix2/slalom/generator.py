#!/usr/bin/python3
import math, operator, random, sys

def get_lower_hull(concave_function, X):
    Y = list(map(int, map(concave_function, X)))
    min_value = min(Y)
    return list(map(lambda x: x - min_value, Y))


def get_lower_hull_2(concave_function_1, concave_function_2, X, q):
    cusp = min(len(X) - 1, int(q * len(X)))
    Y1 = get_lower_hull(concave_function_1, X[:cusp+1])
    Y2 = get_lower_hull(concave_function_2, X[cusp:])
    return join_hulls(Y1, Y2)


def convert_to_upper_hull(lower_Y, t):
    return list(map(lambda y: t - y, lower_Y))


def join_hulls(increasing, decreasing):
    max_value = max(increasing[-1], decreasing[0])
    diff_increasing = max_value - increasing[-1]
    diff_decreasing = max_value - decreasing[0]
    return list(map(lambda x: x + diff_increasing, increasing)) + list(map(lambda x: x + diff_decreasing, decreasing[1:]))


def get_distance(lower_X, lower_Y, upper_X, upper_Y):
    def neg(A):
        return list(map(operator.neg, A))

    def aux(points, hull_X, hull_Y):
        res = float('inf')
        j = 0
        for x, y in points:
            while hull_X[j] < x:
                j += 1
            if hull_X[j] == x:
                res = min(res, hull_Y[j] - y)
            else:
                q = (x - hull_X[j - 1]) / (hull_X[j] - hull_X[j - 1])
                yu = q * hull_Y[j] + (1 - q) * hull_Y[j - 1]
                res = min(res, yu - y)
        return res

    assert lower_X[0] == upper_X[0] and lower_X[-1] == upper_X[-1]
    return min(aux(zip(lower_X, lower_Y), upper_X, upper_Y),
               aux(zip(upper_X, neg(upper_Y)), lower_X, neg(lower_Y)))


def add_dummy_points(X, hull_X, hull_Y):
    assert X[0] == hull_X[0] and X[-1] == hull_X[-1]
    j = 0
    Y = []
    for x in X:
        while hull_X[j] < x:
            j += 1
            ax, ay = 2 * hull_X[j - 1] - hull_X[j], 2 * hull_Y[j - 1] - hull_Y[j]
            bx, by = hull_X[j - 1], hull_Y[j - 1]
        if hull_X[j] == x:
            Y.append(hull_Y[j])
        else:
            q = (x - ax) / (bx - ax)
            y = max(0, int(q * by + (1 - q) * ay) - random.randint(1, 5))
            Y.append(y)
            ax, ay = bx, by
            bx, by = x, y
    return Y


def get_sample(X, q):
    return [X[0]] + sorted(random.sample(X[1:-1], min(len(X) - 2, int(q * len(X))))) + [X[-1]]


def bring_closer(lower_Y, upper_Y, d):
    assert len(lower_Y) == len(upper_Y)
    lower_d = d // 2
    upper_d = (d + 1) // 2
    for i in range(len(lower_Y)):
        lower_Y[i] += lower_d
        upper_Y[i] -= upper_d


def generate(n, t, lower_coeff, upper_coeff, lower_f1, lower_f2, lower_cusp, upper_f1, upper_f2, upper_cusp, strategy):
    X = sorted(random.sample(range(t), n))
    lower_X = get_sample(X, lower_coeff)
    upper_X = get_sample(X, upper_coeff)
    lower_Y = get_lower_hull_2(lower_f1, lower_f2, lower_X, lower_cusp)
    upper_Y = get_lower_hull_2(upper_f1, upper_f2, upper_X, upper_cusp)

    d = get_distance(lower_X, lower_Y, upper_X, convert_to_upper_hull(upper_Y, t))
    print(d, file=sys.stderr)
    assert d >= 0

    lower_Y = add_dummy_points(X, lower_X, lower_Y)
    upper_Y = convert_to_upper_hull(add_dummy_points(X, upper_X, upper_Y), t)
    bring_closer(lower_Y, upper_Y, strategy(d))

    return (X, lower_Y, upper_Y)


class Writer:
    def __init__(self):
        self.current_set = 0
        self.current_case = 0

    def next_case(self):
        self.current_case += 1

    def next_set(self):
        self.current_set += 1
        self.current_case = 0

    def write(self, X, lower_Y, upper_Y):
        assert len(X) == len(lower_Y) and len(X) == len(upper_Y)
        P = list(range(len(X)))
        random.shuffle(P)
        with open('{}.{}.in'.format(self.current_set, chr(self.current_case + ord('a'))), 'w') as f:
            print(len(X), file=f)
            for i in P:
                assert lower_Y[i] <= upper_Y[i]
                print(X[i], lower_Y[i], upper_Y[i], file=f)
        self.next_case()


def get_raiser(k):
    return lambda x: pow(x, k)


def scale(function, a):
    return lambda x: a * function(x)


def slow_down(function, k):
    return lambda x: function(x) / pow(math.log(x + 2), k)


def reflect(function, t):
    return lambda x: function(t - x)


def impossible_strategy(x):
    return math.ceil(x)


def tight_strategy(x):
    return math.floor(x)


def get_coeff_strategy(coeff):
    return lambda x: int((1 - coeff) * x)


random.seed(0x25367c61)
W = Writer()

W.next_set()
t = 100
n = 10
f = scale(get_raiser(0.9), 1)
s = get_coeff_strategy(0.2)
W.write(*generate(n, t, 1, 1, f, reflect(f, t), 0.3, f, reflect(f, t), 0.6, s))
W.write(*generate(n, t, 1, 1, f, reflect(f, t), 1, f, reflect(f, t), 1, s))
W.write(*generate(n, t, 1, 1, f, reflect(f, t), 0, f, reflect(f, t), 1, s))
W.write(*generate(n, t, 1, 1, f, reflect(f, t), 1, f, reflect(f, t), 0, s))
W.write(*generate(n, t, 1, 1, f, reflect(f, t), 0, f, scale(reflect(f, t), 0.5), 0, s))
W.write([4], [20], [30])
t = 10**9
s = get_coeff_strategy(1 / 10**6)
W.write(*generate(n, t, 1, 1, f, reflect(f, t), 0.7, f, reflect(f, t), 0.6, s))
W.write(*generate(n, t, 1, 1, f, reflect(f, t), 0.1, f, reflect(f, t), 0.3, tight_strategy))
n = 10**3
W.write(*generate(n, t, 0.9, 0.9, f, reflect(f, t), 0.4, f, reflect(f, t), 0.6, s))
W.write(*generate(n, t, 0.2, 0.9, f, reflect(f, t), 0.1, f, reflect(f, t), 0.2, tight_strategy))
f = reflect(scale(get_raiser(1.05), -0.1), t)
W.write(*generate(n, t, 0.5, 0.5, f, reflect(f, t), 0.9, f, reflect(f, t), 1, s))
W.write(*generate(n, t, 0.5, 0.5, f, reflect(f, t), 0.9, f, reflect(f, t), 0.8, impossible_strategy))
W.write(*generate(n, t, 0.5, 0.2, f, reflect(f, t), 0.4, slow_down(f, 1), reflect(f, t), 0.5, tight_strategy))

W.next_set()
t = 10**9
n = 10**5
f = scale(get_raiser(0.9), 7)
s = get_coeff_strategy(1 / 10**6)
W.write(*generate(n, t, 1, 1, f, reflect(f, t), 0.5, f, reflect(f, t), 0.5, s))
W.write(*generate(n, t, 0.8, 0.8, f, reflect(f, t), 0.3, f, reflect(f, t), 0.8, tight_strategy))
W.write(*generate(n, t, 0.7, 0.7, f, reflect(f, t), 0.9, scale(f, 0.2), reflect(f, t), 0.8, impossible_strategy))
W.write(*generate(n, t, 0.4, 0.4, f, reflect(f, t), 0, f, reflect(f, t), 1, s))
W.write(*generate(n, t, 0.4, 0.4, f, slow_down(reflect(f, t), 0.5), 0, f, scale(reflect(f, t), 0.1), 0, s))
W.write(*generate(n, t, 0.1, 0.2, f, reflect(f, t), 0.3, f, slow_down(reflect(f, t), 1), 0.3, tight_strategy))

W.next_set()
t = 10**9
n = 10**5
f = reflect(scale(get_raiser(1.05), -0.3), t)
s = get_coeff_strategy(1 / 10**6)
W.write(*generate(n, t, 1, 1, f, reflect(f, t), 0.5, f, reflect(f, t), 0.5, s))
W.write(*generate(n, t, 0.8, 0.8, f, reflect(f, t), 0.3, f, reflect(f, t), 0.8, impossible_strategy))
W.write(*generate(n, t, 0.7, 0.7, f, reflect(f, t), 0.9, scale(f, 0.2), reflect(f, t), 0.8, tight_strategy))
f = scale(f, 0.4)
W.write(*generate(n, t, 0.4, 0.4, f, reflect(f, t), 0.2, f, reflect(f, t), 0.3, get_coeff_strategy(0.5)))
W.write(*generate(n, t, 0.4, 0.4, f, slow_down(reflect(f, t), 0.5), 0.8, f, scale(reflect(f, t), 0.1), 0.8, s))
W.write(*generate(n, t, 0.05, 0.05, f, reflect(f, t), 0.3, f, slow_down(reflect(f, t), 1), 0.3, tight_strategy))
