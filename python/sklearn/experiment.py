import numpy as np

from sklearn.neighbors import KNeighborsClassifier as KNN
from sklearn.discriminant_analysis import LinearDiscriminantAnalysis as LDA
from sklearn.discriminant_analysis import QuadraticDiscriminantAnalysis as QDA


from sklearn.metrics import confusion_matrix
from sklearn.metrics import accuracy_score



class Experiment():
    def __init__(self, data, classifiers):
        self.data = data
        self.classifiers = classifiers
        self.predictions = []
        self.accuracys = []
        
        for c in self.classifiers:
            c.fit(self.data.X_train, self.data.y_train)
            y_pred = c.predict(self.data.X_test)
            self.predictions.append(y_pred)
            self.accuracys.append(accuracy_score(self.data.y_test, y_pred))
        
## import experiment, data
## x = xp.Experiment(data.Data(100, 3, 4), [xp.KNN(), xp.LDA(), xp.QDA()])
## x.accuracys
