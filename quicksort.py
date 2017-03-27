#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# -*- py-python-command: "/usr/bin/python3"; -*-

def qsort(ls, pibot=lambda ls: ls[0]):
    """
    >>> import random
    >>> r = list(range(100))
    >>> l = list(r)
    >>> random.shuffle(l)
    >>> qsort(l) == r
    True
    """
    if ls == []: return []
    p = pibot(ls)
    return (qsort([x for x in ls if x < p])
            + [p]
            + qsort([x for x in ls if x > p]))

if __name__ == '__main__':
    import doctest
    doctest.testmod()
