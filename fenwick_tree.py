#!/usr/bin/env python3
# -*- coding: utf-8 -*-

class FenwickTree:
    def __init__(self, n):
        self.x = [0] * n

    def sum(self, i, j):
        if i == 0:
            S = 0
            while j >= 0:
                S += x[j]
                j = (j & (j + 1)) - 1
            return S
        else:
            return self.sum(0, j) - self.sum(0, i - 1)

    def add(k, a):
        while k < len(x):
            k |= k + 1
            x[k] += a

if __name__ == '__main__':
    import doctest
    doctest.testmod()
