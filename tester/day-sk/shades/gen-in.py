import random
import math

random.seed(26062014)

class name_generator:
    def __init__(self):
        self.set = 0;
        self.case = 0;

    def next_case(self):
        self.case = self.case+1

    def next_set(self):
        self.set = self.set+1
        self.case = 0

    def name(self):
        if self.set == 0:
            return "test/00.sample.%s" % (chr(ord('a')+self.case))
        return "test/%02d.%s" % (self.set, chr(ord('a')+self.case))

class writer:
    def __init__(self):
        self.G = name_generator();

    def next_case(self):
        self.G.next_case()
    
    def next_set(self):
        self.G.next_set()

    def open(self):
        print("Generujem: %s" % (self.G.name()))
        self.file = open(self.G.name()+".in","w")

    def close(self):
        self.file.close()

    def write(self, line):
        print(line, file=self.file)


def w(data):
    W = writer()
    for set in data:
        for (l,k) in set:
            W.open()
            W.write("%d" % (len(k)))
            for e in k:
                f = list(e)
                W.write("%d %s" % (len(f)," ".join(map(str,f))))
            W.write("%d %s" % (len(l)," ".join(map(str,l))))
            W.close()
            W.next_case()
        W.next_set()

def singles_paterner(L):
    res = []
    for i in L:
        res.append([random.randint(7,99)])
    return res;

def n_paterner(L,n):
    res = []
    for i in range(len(L)//n):
        k = random.randint(0,len(L)-n)
        res.append(L[k:k+n])
    return res;

def tiny_paterner(L):
    return n_paterner(L,3)

def short_paterner(L):
    return n_paterner(L,6)

def sqrt_paterner(L):
    return n_paterner(L,math.floor(math.sqrt(len(L))))

def log_paterner(L):
    res = []
    rest = len(L)
    while rest > 0:
        r = random.randint(1,rest)
        rest -= r;
        i = random.randint(0,len(L)-r)
        res.append(L[i:i+r])
    return res;

def small_seq(l):
    res = []
    for i in range(l):
        res.append(random.randint(1,36))
    return res


def bin_seq(l):
    res = []
    for i in range(l):
        res.append(2**random.randint(0,7))
    return res;

def patern_bin_seq(l):
    res = []
    patern = []
    for i in range(7):
        patern.append(2**random.randint(0,6))
    for i in range(l // 7):
        r = random.randint(1,2)
        res+=map(lambda x : r*x, patern)
    return res;

def rand_mult(L):
    r = random.randint(47,78);
    return map(lambda x : r*x, L)


def generator(l, sequencer, paterner):
    L = sequencer(l);
    K = paterner(L);
    return (list(rand_mult(L)),list(map(rand_mult,K)))



data = [[
    ([3,6,3,6,12,6,3],[[47],[21,42],[34,17],[1,2,1]])
]]


for l in [15,1000,10000,100000,300000]:
    pom = [];
    
    pom.append(generator(l,small_seq,singles_paterner))
    for s in [small_seq, bin_seq, patern_bin_seq]:
        for p in [tiny_paterner, short_paterner, log_paterner, sqrt_paterner]:
            pom.append(generator(l,s,p))
    
    data.append(pom)

w(data)    