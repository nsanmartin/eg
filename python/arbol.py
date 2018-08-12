import sys

class Arbol(object):
    def __init__(this):
        this.menor = None
        this.mayor = None
        this.dato = None

def hacerArbol(arb, lst):
    p = arb
    for x in lst:
        while p.dato is not None:
            if x > p.dato: p = p.mayor
            else: p = p.menor
        p.dato = x

def test(a):
    p = a
    print(p)
    print(p.menor)
    print(p.mayor)
    print(p.dato)
    if p.menor is None:
        print("p.dato es None")

    
        
def main(argv):
    print("lst = [1,6,3,5,8,9]")
    l = [1]
    a = Arbol()
    print(a.dato)
    hacerArbol(a, l)
    print(a.dato)

    
if __name__ == "__main__":
    main(sys.argv[1:])

