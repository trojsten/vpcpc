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
        for (N, M, B, E, H, edges) in set:
            W.open()
            W.write('%s %s %s %s %s' % (N, M, B, E, H))
            for edge in edges:
                W.write(' '.join(map(str, edge)))
            W.close()
            W.next_case()
        W.next_set()


data = [[]]

w(data)
