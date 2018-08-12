def mergesort(lista):
    if len(lista) > 1:
        izquierda = mergesort(lista[:len(lista)//2])
        derecha = mergesort(lista[len(lista)//2:])
        return merge(izquierda, derecha)
    else:
        return lista

def merge(a, b):
    res = []
    j = 0
    for i in range(0, len(a)):
        while j < len(b) and a[i] > b[j]:
            res.append(b[j])
            j += 1
        res.append(a[i])
    res += b[j:]
    return res


