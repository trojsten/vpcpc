import random

random.seed(24062014)

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

cubes = [
"""AAA
AAA
AAA
BBBCCCDDDEEE
BBBCCCDDDEEE
BBBCCCDDDEEE
FFF
FFF
FFF""",
"""BBB
FAD
ACD
DBCFFFCEEFBC
BBACCEADDAEA
BCFDDACDDAEA
EFE
FFE
ECB""",
"""FBB
FAF
BAC
FDBFCAEEEDDE
DBAECCADABEC
DBEDEBAFDFBA
CCA
FFD
CEC""",
"""CBD
AAD
BED
CFACAFEFFDEF
CBDECACDDCEB
ACBFBACEDAFE
BFE
DFA
EBB"""
]


def w(data):
    W = writer()
    for set in data:
        for (l,k) in set:
            W.open()
            W.write(random.choice(cubes))
            W.write("%d %d" % (len(l),len(k)))
            for e in l:
                W.write("%s %d" % e)
            for e in k:
                W.write("%d %s %d" % e)
            W.close()
            W.next_case()
        W.next_set()
    

data = [[]]


for (n,m) in [(10,10),(1000,1000),(5000,10000),(65000,65000)]:
    pom = []
    
    for i in range(5):
        l = []
        k = []
        for j in range(n):
            l.append((random.choice("ABCDEF"),random.choice([-1,1])))
        for j in range(m):
            k.append((
                random.randint(1,n),
                random.choice("ABCDEF"),
                random.choice([-1,1])
            ))
        pom.append((l,k))
    data.append(pom)

w(data)    
