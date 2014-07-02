import random

random.seed(4189362)

MIN_COST, MAX_COST = 1, 10**6


def is_connected(N, edges):
    graph = [[] for i in xrange(N)]
    for a, b, c in edges:
        graph[a].append(b)
        graph[b].append(a)
    visited = [False] * N
    visited[0] = True
    queue = [0]
    while queue:
        node = queue.pop()
        for next in filter(lambda x: visited[x]==False, graph[node]):
            visited[next] = True
            queue.append(next)
    for node in xrange(N):
        if not visited[node]:
            return False
    return True


def relabel(N, M, B, E, H, edges):
    mapping = range(1,N+1)
    random.shuffle(mapping)
    edges = map(lambda (a, b, c): (mapping[a], mapping[b], c), edges)
    return (N, M, mapping[B], mapping[E], mapping[H], edges)


def gen_tree(vertices):
    random.shuffle(vertices)
    edges = []
    for i in xrange(1, len(vertices)):
        v1, v2 = vertices[i], vertices[random.randint(0, i-1)]
        edges.append((v1, v2, random.randint(MIN_COST, MAX_COST)))
    return edges


def gen_random(vertices, M):
    '''Generate random connected graph on the given vertices with at most M edges.
    '''
    edges = gen_tree(vertices)
    seen = set((min(a,b), max(a,b)) for (a,b,c) in edges)
    available = []
    for i in xrange(len(vertices)):
        for j in xrange(i):
            a, b = vertices[i], vertices[j]
            key = (min(a,b), max(a,b))
            if key not in seen:
                available.append((a, b, random.randint(MIN_COST, MAX_COST)))
    random.shuffle(available)
    return edges + available[:M-len(edges)]

def gen_connected(N, M):
    vertices = range(N)
    edges = gen_random(vertices, M)
    B, E, H = random.sample(vertices, 3)
    return relabel(N, len(edges), B, E, H, edges)


def gen_path(N, min_cost=MIN_COST, max_cost=MAX_COST):
    edges = []
    for i in xrange(N-1):
        edges.append((i, i+1, random.randint(min_cost, max_cost)))
    B, H = 0, N-1
    E = random.randint(B+1, H-1)
    return relabel(N, len(edges), B, E, H, edges)


def gen_unique_path(N):
    '''Articulation vertex in the middle of components.
    '''
    N1, N2, N3 = N//3, N//3, N//3+N%3
    vs1, vs2, vs3 = range(0, N1), range(N1, N1+N2), range(N1+N2, N)
    B, E, H = vs1[0], vs2[0], vs3[0]
    cross = vs1[1]
    edges = gen_random(vs1, 333) + gen_random(vs2+[cross], 333) + gen_random(vs3+[cross], 333)
    assert is_connected(N, edges)
    return relabel(N, len(edges), B, E, H, edges)


def gen_disconnected1(N):
    N1, N2, N3 = N//3, N//3, N//3+N%3
    vs1, vs2, vs3 = range(0, N1), range(N1, N1+N2), range(N1+N2, N)
    B, E, H = vs1[0], vs2[0], vs3[0]
    edges = gen_random(vs1, 333) + gen_random(vs2 + vs3, 667)
    return relabel(N, len(edges), B, E, H, edges)

def gen_disconnected2(N):
    N1, N2, N3 = N//3, N//3, N//3+N%3
    vs1, vs2, vs3 = range(0, N1), range(N1, N1+N2), range(N1+N2, N)
    B, E, H = vs1[0], vs2[0], vs3[0]
    edges = gen_random(vs1+vs2, 333) + gen_random(vs3, 667)
    return relabel(N, len(edges), B, E, H, edges)

def gen_disconnected3(N):
    N1, N2, N3 = N//3, N//3, N//3+N%3
    vs1, vs2, vs3 = range(0, N1), range(N1, N1+N2), range(N1+N2, N)
    B, E, H = vs1[0], vs2[0], vs3[0]
    edges = gen_random(vs1+vs3, 333) + gen_random(vs2, 667)
    return relabel(N, len(edges), B, E, H, edges)

def gen_disconnected4(N):
    N1, N2, N3 = N//3, N//3, N//3+N%3
    vs1, vs2, vs3 = range(0, N1), range(N1, N1+N2), range(N1+N2, N)
    B, E, H = vs1[0], vs2[0], vs3[0]
    edges = gen_random(vs1, 333) + gen_random(vs2, 333) + gen_random(vs3, 333)
    return relabel(N, len(edges), B, E, H, edges)


def gen_boobs(N):
    B, E, H = 0, 1, 2
    X, Y = (N-3)//2, (N-3+1)//2
    assert X+Y+3 == N
    vs1, vs2 = range(H+1, H+X+1), range(H+X+1, H+X+Y+1)
    edges = []
    for v in vs1:
        edges.append((B, v, random.randint(MIN_COST, MAX_COST)))
        edges.append((v, E, random.randint(MIN_COST, MAX_COST)))
    for v in vs2:
        edges.append((E, v, random.randint(MIN_COST, MAX_COST)))
        edges.append((v, H, random.randint(MIN_COST, MAX_COST)))
    return relabel(N, len(edges), B, E, H, edges)


def gen_greedy_die(N):
    '''Shortest path between B->E kills all the paths from E->H.
    '''
    B, H, E = 0, 1, N-1
    edges = [
        (0, 2, random.randint(1, 100)),
        (1, 2, random.randint(1, 100))]
    for i in xrange(2, E):
        edges.append((i, i+1, random.randint(1, 100)))
    vs1, vs2 = [], []
    for i in xrange(3, E-1):
        if not vs1:
            vs1.append(i)
        elif not vs2:
            vs2.append(i)
        else:
            if random.randint(1, 2) == 1 and vs1[-1]+1 != i:
                vs1.append(i)
            elif vs2[-1]+1 != i:
                vs2.append(i)

    edges.append((B, vs1[0], random.randint(MAX_COST*3//4, MAX_COST)))
    for i in xrange(1, len(vs1)):
        edges.append((vs1[i-1], vs1[i], random.randint(MAX_COST*3//4, MAX_COST)))
    edges.append((vs1[-1], E, random.randint(MAX_COST*3//4, MAX_COST)))
    edges.append((H, vs2[0], random.randint(MAX_COST*3//4, MAX_COST)))
    for i in xrange(1, len(vs2)):
        edges.append((vs2[i-1], vs2[i], random.randint(MAX_COST*3//4, MAX_COST)))
    edges.append((vs2[-1], E, random.randint(MAX_COST*3//4, MAX_COST)))
    return relabel(N, len(edges), B, E, H, edges)


def gen_greedy_worse(N):
    B, H, E = 0, 1, N-1
    edges = [
        (0, 2, random.randint(1, 10)),
        (1, 2, random.randint(1, 10))]
    for i in xrange(2, E):
        edges.append((i, i+1, random.randint(1, 10)))
    vs1, vs2 = [], []
    for i in xrange(3, E-1):
        if not vs1:
            vs1.append(i)
        elif not vs2:
            vs2.append(i)
        else:
            if random.randint(1, 2) == 1 and vs1[-1]+1 != i:
                vs1.append(i)
            elif vs2[-1]+1 != i:
                vs2.append(i)
            else:
                edges.append((i, E, MAX_COST))

    edges.append((B, vs1[0], random.randint(500, 2000)))
    for i in xrange(1, len(vs1)):
        edges.append((vs1[i-1], vs1[i], random.randint(500, 2000)))
    edges.append((vs1[-1], E, random.randint(500, 2000)))
    edges.append((H, vs2[0], random.randint(500, 2000)))
    for i in xrange(1, len(vs2)):
        edges.append((vs2[i-1], vs2[i], random.randint(500, 2000)))
    edges.append((vs2[-1], E, random.randint(500, 2000)))

    edges.append((B, E, MAX_COST))
    edges.append((H, E, MAX_COST))
    return relabel(N, len(edges), B, E, H, edges)
