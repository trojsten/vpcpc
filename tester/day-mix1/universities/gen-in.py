import glob
from os import path
import random

from generators import *


class NameGenerator(object):
    def __init__(self):
        self.set = 0
        self.case = 0

    def next_case(self):
        self.case = self.case+1

    def next_set(self):
        self.set = self.set+1
        self.case = 0

    def name(self):
        if self.set == 0:
            return path.join('test', '00.sample.%s' % (chr(ord('a')+self.case)))
        return path.join('test', '%02d.%s' % (self.set, chr(ord('a')+self.case)))

class Writer(object):
    def __init__(self):
        self.G = NameGenerator();

    def next_case(self):
        self.G.next_case()

    def next_set(self):
        self.G.next_set()

    def open(self):
        print('Generujem: %s' % (self.G.name()))
        self.file = open(self.G.name()+'.in','w')

    def close(self):
        self.file.close()

    def write(self, line):
        self.file.write(line)
        self.file.write('\n')

def w(data):
    W = Writer()
    for set in data:
        for (N, colors, happy, vs) in set:
            W.open()
            W.write('%s' % N)
            W.write(colors)
            W.write(' '.join(map(str, happy)))
            W.write(' '.join(map(str, vs)))
            W.close()
            W.next_case()
        W.next_set()


data = [[]]

# data with increasing N
for MIN_N, MAX_N in [(8000, 10000), (40000, 50000), (100000, 100000)]:
    tc = []

    if MIN_N == 8000:
        tc.extend([
            (2, 'BW', [5, -10], [1]),
            (3, 'WBB', [-10, -20, 100], [1, 2]),
            (5, 'BWWWW', [0, 1, 2, 3, 4], [1, 2, 3, 4]),
            (5, 'BWWWW', [0, 1, 2, 3, 4], [1, 1, 1, 1])])
    elif MIN_N == 100000:
        N = 100000
        tc.extend([
            (N, gen_equal_random_colors_shuffle(N), gen_max_happy(N), gen_path_strict(N))])

    for structure in gen_structure:
        for colors in gen_colors:
            N = random.randint(MIN_N, MAX_N)
            tc.append((N, colors(N), gen_random_happy(N), structure(N)))
    for structure in gen_structure:
        N = random.randint(MIN_N, MAX_N)
        tc.append((N, gen_random_colors(N), gen_random_happy(N, min_h=0, max_h=10**5), structure(N)))
    data.append(tc)

w(data)
