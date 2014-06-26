import random

random.seed(4189362)

def gen_random(N):
    return [random.randint(1, i) for i in xrange(1, N)]

def gen_path(N):
    return [random.randint(max(1, i-2), i) for i in xrange(1, N)]

def gen_path_strict(N):
    return [i for i in xrange(1, N)]

def gen_star(N):
    return [random.randint(0, i-1)//100+1 for i in xrange(1, N)]

def gen_bt(N):
    return [i//2+1 for i in xrange(1, N)]

gen_structure = [gen_random, gen_path, gen_star, gen_bt]


def gen_random_colors(N):
    while True:
        colors = ''.join(random.choice('WBB') for i in xrange(N))
        if 'W' in colors and 'B' in colors:
            return colors

def gen_equal_random_colors(N):
    return 'B' * (N//2) + 'W' * ((N+1)//2)

def gen_equal_random_colors_shuffle(N):
    colors = list('B' * (N//2) + 'W' * ((N+1)//2))
    random.shuffle(colors)
    return ''.join(colors)

gen_colors = [gen_random_colors, gen_equal_random_colors, gen_equal_random_colors_shuffle]


MAX_H = 10**5
def gen_max_happy(N):
    return [MAX_H] * N

def gen_random_happy(N, max_h=MAX_H, min_h=None):
    if min_h is None:
        min_h = -random.choice([max_h, max_h//10])
    return [random.randint(min_h, max_h) for i in xrange(N)]

gen_happy = [gen_max_happy, gen_random_happy]


def gen_testcase(N):
    colors = gen_random_colors(N)
    happy = gen_random_happy(N)
    vs = gen_path_strict(N)
    return (N, colors, happy, vs)
    # colors = random.choice(gen_colors)(N)
    # happy = random.choice(gen_happy)(N)
    # vs = random.choice(gen_structure)(N)
    # return (N, colors, happy, vs)
