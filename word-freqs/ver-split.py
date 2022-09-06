#!/usr/bin/env python
import operator

import sys

if __name__ == "__main__":
    table = dict()
    for line in sys.stdin:
        for w in line.split():
            table[w] = table.get(w, 0) + 1


    #for k,v in sorted(table.items(), key=operator.itemgetter(1)):
    #    print("{}: {}".format(k,v))
    for k,v in table.items():
        print("{}: {}".format(k,v))

