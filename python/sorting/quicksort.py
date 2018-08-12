import random       

def quicksort(a):
    quicksort_aux(a,0,len(a)-1)

def quicksort_aux(a, p, r):
    if p < r:
        q = partition (a, p, r)
        quicksort_aux (a, p, q - 1)
        quicksort_aux (a, q + 1, r)
    

def partition (a, p, r):

    i = random.randint(p, r)
    a[r], a[i] = a[i], a[r]
    x = a[r]
    i = p - 1
    for j in range (p, r):
        if a[j] <= x:
            i += 1
            a[i], a[j] = a[j], a[i]

    a[i + 1], a[r] = a[r], a[i + 1]
    return 1 + i
