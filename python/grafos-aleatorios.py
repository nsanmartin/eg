import numpy as np
import random


class grafo_conexo_aleatorio:
    def __init__(self, n, m = None):
        self.n = n
        self.llenar_arbol()
        if m is None:
            self.llenar_resto()
        else:
            assert (m >= n - 1)
            assert (m <= n * (n-1) // 2)
            self.llenar_hasta_m(m)

    def arista_a_numero(self,origen, destino):
        if origen > destino:
            origen, destino = destino, origen

        diff = destino - origen
        diff_n = self.n - diff

        if diff_n < diff:
            origen, destino = destino, origen

        return (min(diff, diff_n) - 1) * self.n + origen


    def numero_a_arista(self, i):
        origen = i % self.n
        distancia = i // self.n + 1
        destino = (origen + distancia) % self.n
        return (origen, destino)


    
    def llenar_arbol(self):
        n = self.n
        self.aristas = np.zeros(n * (n-1) // 2, dtype=np.int)
        a = np.arange(n)
        np.random.shuffle(a)
        span = [a[0]]

        for x in a[1:]:
            s = random.choice(span)
            self.aristas[self.arista_a_numero(s, x)] = 1
            span.append(x)


    def llenar_resto(self):
        m = self.n * (self.n-1) / 2
        nuevas_aristas = np.random.random_integers(
            low=0, high=m - 1, size=random.randint(0, m-1))
        for i in nuevas_aristas:
            self.aristas[i] = 1

    def llenar_hasta_m(self, m):
        """Esta funci'on recibe n, m, m <= n(n-1)/2 .
        
        """
        mk = self.n * (self.n-1) // 2
        nuevas_aristas = set()
        
        while (len(nuevas_aristas) < m - self.n + 1):
            r = np.random.randint (mk)
            while self.aristas[r] == 1:
                r = np.random.randint (mk)
                nuevas_aristas.add(r)
            
        for i in nuevas_aristas:
            self.aristas[i] = 1


    def print_aristas(self):
        """
        Muestra las aristas y les asigna un peso aleatorio.
        """
        pesos = np.random.random_integers(
            low=0, size=len(self.aristas), high=random.randint(1, 100))
        print ('{:^17} {:^17} {:^17}'.format("origen", "destino","peso"))
        for i, x in enumerate(self.aristas):
            if x == 1:
                v, w = self.numero_a_arista(i)
                print ('{:^17} {:^17} {:^17}'.format(v, w, pesos[i]))


            


