def insertionsort__(lista):
    for i in range(0, len(lista)):
        current = lista[i]
        j = i - 1
        while j >= 0 and lista[j] > current:
            lista[j + 1] = lista[j]
            j -= 1
            lista[j + 1] = current
