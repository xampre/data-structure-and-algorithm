#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# -*- py-python-command: "/usr/bin/python3"; -*-

def bs(sorted_, key):
    """
    >>> l = [0,1,2,3,4,5]
    >>> [bs(l, n) for n in range(0, len(l) + 1)] == range(0, len(l)) + [None]
    True
    """
    L = 0
    R = len(sorted_) - 1
    while L <= R:
        mid = (L + R) // 2
        item = sorted_[mid]
        if item < key:
            L = mid + 1
        elif item > key:
            R = mid - 1
        else:
            return mid
    return None

if __name__ == '__main__':
    import doctest
    doctest.testmod()
