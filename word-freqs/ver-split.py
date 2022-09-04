#!/usr/bin/env python

import sys

if __name__ == "__main__":
    for line in sys.stdin:
        for w in line.split():
            print(w)


