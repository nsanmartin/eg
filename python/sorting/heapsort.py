def heapsort(a):
    build_max_heap (a)
    heap_size = len(a)
    for i in range( len(a)- 1, 0, -1):
        a[0], a[i] = a[i] , a[0]
        heap_size -= 1
        max_heapify(a, 0, heap_size)

def max_heapify(a,i, heap_size):
    l = 2*i+1 #left(i)
    r = 2*i+2 #right(i)
    if l < heap_size and a[l] > a[i]:
        largest = l
    else: largest = i
    if r < heap_size and a[r] > a[largest]:
        largest = r
    if largest is not i:
        a[i], a[largest] = a[largest], a[i]
        max_heapify (a, largest, heap_size)
    
def build_max_heap (a):
    heap_size = len(a)
    for i in range(len(a)//2, -1, -1):
        max_heapify(a, i, heap_size)


    

