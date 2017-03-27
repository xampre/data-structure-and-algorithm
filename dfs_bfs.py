#!/usr/bin/env python3
# -*- coding: utf-8 -*-

def dfs(target, dlist, _index=[0]):
    if [] == dlist:
        return False
    elif target == dlist[0]:
        return tuple(_index)
    elif type(dlist[0]) == list:
        return (dfs(target, dlist[0], _index + [0])
                    or dfs(target, dlist[1:], _index[:-1] + [_index[-1] + 1]))
    else:
        return dfs(target, dlist[1:], _index[:-1] + [_index[-1] + 1])

def dfs_loop(target, dlist):
    s = list()
    for i, v in reversed(list(enumerate(dlist))):
        s.append(([i], v))

    while s:
        i, v = s.pop()
        if v == target:
            return tuple(i)
        elif type(v) == list:
            for _i, _v in reversed(list(enumerate(v))):
                s.append((i + [_i], _v))
    return False

def bfs(target, dlist):
    from collections import deque
    q = deque()
    for i, v in enumerate(dlist): q.append(([i], v))
    while q:
        i, v = q.popleft()
        if v == target:
            return tuple(i)
        elif type(v) == list:
            for _i, _v in enumerate(v): q.append((i + [_i], _v))
    return False

if __name__ == '__main__':
    dlist = [[1, 2, [3, [5]]], [[3, 5], 4, 7], [3, 7, 9]]
    print(dfs(5, dlist) == (0, 2, 1, 0))
    print(dfs(8, dlist) == False)
    print(dfs_loop(5, dlist) == (0, 2, 1, 0))
    print(dfs_loop(8, dlist) == False)
    print(bfs(5, dlist) == (1, 0, 1))
    print(bfs(8, dlist) == False)
