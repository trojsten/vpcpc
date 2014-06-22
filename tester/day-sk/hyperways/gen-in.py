import random

random.seed(22062014)

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
        for (n,l) in set:
            W.open()
            W.write("%d %d" % (n,len(l)))
            for e in l:
                W.write("%d %d" % e)
            W.close()
            W.next_case()
        W.next_set()
    
def grid_generator(r, s):
    l = []
    for i in range(r):
        for j in range(s):
            l.append((i+j*r+1,(i+j*r+1) % (r*s) + 1))
            l.append((i+j*r+1,(i+j*r+r) % (r*s) + 1))
    random.shuffle(l)
    l = l[0:(r*s)]
    return (r*s,l)

def full_rand_generator(r, s):
    l = []
    n = r*s
    for i in range(2*n):
        a = random.randint(1,n)
        b = random.randint(1,n)
        l.append((a, b))
    return (n,l)  

def complete_generator(r, s):
    l = []
    for i in range(r):
        for j in range(r):
            l.append((i+1,j+1))
    random.shuffle(l)
    return (r*r,l)

def row_generator(r, s):
    l = []
    n = (r*s) // 4
    for i in range(n):
        l.append((4*i+1,4*i+2))
        l.append((4*i+2,4*i+3))
        l.append((4*i+3,4*i+4))
        l.append((4*i+2,4*i+3))
        l.append((4*i+2,4*i+4))
        l.append((4*i+1,4*i+3))
    for i in range(n-1):
        l.append((4*i+random.randint(1,4),4*i+random.randint(5,8)))
    for i in range(n-1):
        l.append((4*i+random.randint(1,4),4*i+random.randint(5,8)))
    return (4*n,l)

def mixed_row_generator(r, s):
    l = []
    n = (r*s) // 4
    for i in range(n):
        l.append((4*i+1,4*i+2))
        l.append((4*i+2,4*i+3))
        l.append((4*i+3,4*i+4))
        l.append((4*i+2,4*i+3))
        l.append((4*i+2,4*i+4))
        l.append((4*i+1,4*i+3))
    for i in range(n-1):
        l.append((4*i+random.randint(1,4),4*i+random.randint(5,8)))
    random.shuffle(l)
    for i in range(n-1):
        l.append((4*i+random.randint(1,4),4*i+random.randint(5,8)))
    return (4*n,l)



data = [[
    (5,[(1,2),(3,3),(4,5),(2,3),(4,5),(3,4),(4,1),(5,2)])
]]


for (r,s) in [(10,10),(30,33),(100,100),(300,330),(1000,1000)]:
    pom = [];
    
    pom.append(grid_generator(r,s))
    pom.append(grid_generator(r,s))
    pom.append(full_rand_generator(r,s))
    pom.append(full_rand_generator(r,s))
    pom.append(complete_generator(r,s))
    pom.append(row_generator(r,s))
    pom.append(mixed_row_generator(r,s))
    
    data.append(pom)

w(data)    