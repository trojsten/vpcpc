#!/usr/bin/python3
import random, sys

class InputInstance:
    def __init__(self, n):
        self.n = n
        self.queries = []

    def allocate(self, el):
        self.queries.append((1, el))

    def free(self, x, el):
        self.queries.append((2, x, el))

    def __str__(self):
        S = []
        S.append('{} {}\n'.format(self.n, len(self.queries)))
        for q in self.queries:
            S.append(' '.join(map(str, q)) + '\n')
        return ''.join(S)

    def write(self, file_prefix):
        with open('{}.in'.format(file_prefix), 'w') as f:
            f.write(str(self))


def rand(mean, variance):
    return random.randint(mean - variance, mean + variance)


def shuffle_a_bit(A, coeff):
    for i in range(int(coeff * len(A))):
        a = random.randint(0, len(A) - 1)
        b = random.randint(0, len(A) - 1)
        A[a], A[b] = A[b], A[a]


def get_random(n, q, allocating_prob=0.5):
    I = InputInstance(n)
    for i in range(q):
        if random.random() < allocating_prob:
            I.allocate(random.randint(1, n))
        else:
            el = random.randint(1, n)
            x = random.randint(0, n - el)
            I.free(x, el)
    return I


def get_random_small(n, q, max_length, init_phase_coeff=1.0, allocating_prob=0.5):
    init_phase = int(init_phase_coeff * n / max_length)
    I = InputInstance(n)
    for i in range(q):
        if i == 0:
            I.allocate(n)
        elif i <= init_phase or random.random() < allocating_prob:
            el = random.randint(1, max_length)
            x = random.randint(0, n - el)
            I.free(x, el)
        else:
            I.allocate(random.randint(1, max_length))
    return I


def get_mostly_freeing(n, q, round_size, allocating_length_coeff=0.5, freeing_length_coeff=7.0, freeing_variance_coeff=0.5):
    allocating_length = int(allocating_length_coeff * n)
    freeing_length = int(freeing_length_coeff * n / round_size)
    freeing_variance = int(freeing_variance_coeff * freeing_length)
    I = InputInstance(n)
    for i in range(q):
        if i % round_size == 0:
            I.allocate(allocating_length)
        else:
            el = rand(freeing_length, freeing_variance)
            x = random.randint(0, n - el)
            I.free(x, el)
    return I


def get_mostly_allocating(n, q, cutoff_length=5, cutoff_prob=0.25, allocating_length_coeff=0.35, allocating_variance_coeff=0.15, freeing_length_coeff=0.75, freeing_variance_coeff=0.25):
    freeing_length = int(freeing_length_coeff * n)
    freeing_variance = int(freeing_variance_coeff * n)
    I = InputInstance(n)
    available = 0
    for i in range(q):
        if i == 0:
            I.allocate(n)
        elif available == 0:
            available = rand(freeing_length, freeing_variance)
            x = random.randint(0, n - available)
            I.free(x, available)
        else:
            if available < cutoff_length or random.random() < cutoff_prob:
                el = available
            else:
                el = rand(int(allocating_length_coeff * available), int(allocating_variance_coeff * available))
            I.allocate(el)
            available -= el
    return I


def get_simple_worstcase(n):
    I = InputInstance(n)
    for i in range(n):
        if i % 2 == 0:
            I.allocate(2)
        else:
            I.free(i - 1, 1)
    return I


def get_small_and_large(n, q, small_length=3, large_length=9, variance=2, small_prob=0.2, allocating_prob=0.5):
    def restart():
        nonlocal I, u, v
        I.free(0, n)
        u, v = 0, 0

    I = InputInstance(n)
    u, v = 0, 0
    for i in range(q):
        if u + small_length > v or random.random() < allocating_prob:
            if random.random() < small_prob:
                I.allocate(rand(small_length, variance))
            else:
                el = rand(large_length, variance)
                if v + el < n:
                    I.allocate(el)
                    v += el
                else:
                    restart()
        else:
            u += rand(small_length, variance)
            el = rand(small_length, variance)
            if u + el < n:
                I.free(u, el)
                u += el
            else:
                restart()
    return I


def get_increasing_decreasing(n, max_length, shuffle_coeff=0.05):
    A = []
    for i in range(max_length):
        A += [i + 1] * (n // (max_length * (i + 2)))
    B = A[:]
    B.reverse()
    shuffle_a_bit(A, shuffle_coeff)
    shuffle_a_bit(B, shuffle_coeff)
    I = InputInstance(n)
    I.allocate(n)
    x = 0
    for el in A:
        I.free(x, el)
        x += el + 1
    for el in B:
        I.allocate(el)
    return I


random.seed(0x1b8ceca8)

instances = [
('1.a', get_random(1000, 1000)),
('1.b', get_random_small(1000, 1000, 10)),
('1.c', get_small_and_large(1000, 1000)),
('1.d', get_increasing_decreasing(1000, 4)),

('2.a', get_random(10000, 10000)),
('2.b', get_random_small(10000, 10000, 10)),
('2.c', get_small_and_large(10000, 10000)),
('2.d', get_increasing_decreasing(10000, 6)),
('2.e', get_mostly_freeing(10000, 10000, 30)),
('2.f', get_mostly_allocating(10000, 10000)),

('3.a', get_random(100000, 100000)),
('3.b', get_random_small(100000, 100000, 10)),
('3.c', get_small_and_large(100000, 100000)),
('3.d', get_increasing_decreasing(100000, 10)),

('4.a', get_random(300000, 300000)),
('4.b', get_random_small(300000, 300000, 5)),
('4.c', get_small_and_large(300000, 300000, 7, 20, 5, 0.4, 0.5)),
('4.d', get_increasing_decreasing(300000, 4, 0.1)),
('4.e', get_mostly_freeing(300000, 300000, 15)),
('4.f', get_mostly_allocating(300000, 300000)),

('5.a', get_random(300000, 300000)),
('5.b', get_random_small(300000, 300000, 97)),
('5.c', get_small_and_large(300000, 300000)),
('5.d', get_increasing_decreasing(300000, 10)),
('5.e', get_small_and_large(300000, 300000, 10, 50, 9)),
('5.f', get_increasing_decreasing(300000, 25, 0.02)),
('5.g', get_simple_worstcase(300000)),
]

for x in instances:
    x[1].write(x[0])
