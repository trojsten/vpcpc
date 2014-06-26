import random

random.seed(4387937)

# This method generates a random tree with the given number of vertices.
# It makes sure that there is a path of lenght at least PATH_LEN and
# a vertex with degree at least DEGREE.
# Don't try to hack there constraints, the method expects such tree exists.
# It writes the resulting tree in the required format to the given file.
def gen_tree(N, PATH_LEN, DEGREE, filename):

  parent = []
  for i in range(PATH_LEN): parent.append(i)

  # Which vertex ensures a DEGREE constraint
  degree_vertex = random.randint(0, PATH_LEN)

  for i in range(DEGREE): parent.append(degree_vertex)

  while len(parent) < N - 1:
    p = random.randint(0, len(parent))
    parent.append(p)

  # Shuffle indexes of vertices randomly
  mapping = list(range(1, N + 1))
  random.shuffle(mapping)

  edges = [[mapping[i + 1], mapping[parent[i]]] for i in range(N - 1)]
  random.shuffle(edges)

  f = open(filename, "w")
  f.write("%d\n" % N)
  for edge in edges:
    random.shuffle(edge)
    f.write("%d %d\n" % tuple(edge))
  f.close()

# number of vertices, min path lenght, min degree
testcases = {
  1: (
    (1, 0, 0),
    (2, 0, 0),
    (3, 0, 0),
    (4, 0, 0),
    (4, 0, 3),
    (10, 0, 0),
  ),
  2: (
    (100, 0, 0),
    (100, 99, 0),
    (100, 0, 99),
    (90, 30, 30),
    (30, 10, 10),
  ),
  3: (
    (1000, 0, 0),
    (1000, 800, 0),
    (1000, 0, 800),
    (1000, 400, 400),
  ),
  4: (
    (666, 0, 0),
    (867, 300, 300),
    (999, 499, 499),
  ),
  5: (
    (1000, 998, 0),
    (1000, 0, 997),
    (1000, 134, 287),
  ),
  6: (
    (55325, 21350, 28745),
  ),
  7: (
    (123456, 53421, 67473),
  ),
  8: (
    (334252, 154321, 84964),
  ),
  9: (
    (847673, 324261, 341876),
  ),
  10: (
    (1000000, 435613, 411697),
    (1000000, 999987, 0),
    (1000000, 0, 999948),
  )
}

for test, args in testcases.items():
  for i in range(len(args)):
    if len(args) > 1:
      letter = chr(ord("a") + i)
      filename = "test/%02d.%s.in" % (test, letter)
    else: filename = "test/%02d.in" % test
    gen_tree(*args[i], filename=filename)
