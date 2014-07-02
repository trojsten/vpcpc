import random

random.seed(4189362)

MIN_COST, MAX_COST = 1, 10**6

def gen_random(N, prob=1.0):
    edges = []
    for i in xrange(N):
        for j in xrange(i):
            if random.random() <= prob:
                edges.append((i+1, j+1, random.randint(MIN_COST, MAX_COST)))
    B, E, H = random.sample(range(1,N+1),3)
    return (N, len(edges), B, E, H, edges)
