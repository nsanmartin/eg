import numpy as np

from sklearn.model_selection import train_test_split

class NormalDist():
    def __init__(self, mu, l):
        self.mu = mu
        self.l = l

        
def generate_normal_variable(class_size, dists):
    return np.array([
        np.random.normal(d.mu, d.l, class_size)
        for d in dists
    ])


def random_normal_distribution():
    return NormalDist(np.random.rand(), np.random.rand())


def generate_data(class_size, class_count, variable_count):
    return (
        np.concatenate([
            generate_normal_variable(
                class_size,
                [random_normal_distribution() for _ in range(class_count)]
            )
            for _ in range(variable_count)
        ]).reshape(variable_count, class_size * class_count).T,
        np.concatenate([[c] * class_size for c in range(class_count)])
    )


class Data():
    def __init__(self, class_size, class_count, variable_count):
        self.X, self.y = generate_data(
            class_size = 100,
            class_count = class_count,
            variable_count = variable_count
        )
        self.X_train, self.X_test, self.y_train, self.y_test = train_test_split(
            self.X, self.y, test_size=0.2, random_state=0
        )
