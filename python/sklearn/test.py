import experiment as xp
import data
import classif
x = xp.Experiment(
    data.Data(100, 3, 4),
    [xp.KNN(), xp.LDA(), xp.QDA(), classif.Cuadratico()]
)

print('[xp.KNN(), xp.LDA(), xp.QDA(), classif.Cuadratico()]')
print(x.accuracys)
