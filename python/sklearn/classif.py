import numpy as np

class Cuadratico():

    
    def int_to_cannonical_vector(self, n, length):
        res = np.zeros(length)
        res[n] = 1
        return res


    def array_to_cannonical_vectors(self, x):
        cs = np.unique(x)
        nums = np.arange(len(cs))
        d = dict(zip(cs,nums))
        return np.concatenate([
            self.int_to_cannonical_vector(d[k], len(cs))
            for k in x
        ]).reshape(-1, len(cs))
    
    
    def fit(self, X, T):
        Y = self.array_to_cannonical_vectors(T)
        B = X.T @ Y
        A = X.T @ X
        self.W = np.linalg.solve(A,B)


    def predict(self, X):
        y = self.W.T @ X.T
        return np.argmax(y, axis=0)
