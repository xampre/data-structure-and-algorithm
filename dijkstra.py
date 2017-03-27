#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from heapq import heappush, heappop

class PQueue:
    def __init__(self, list_=[]):
        self.list = list_
    def pop(self): return heappop(self.list)
    def push(self, v): heappush(self.list, v)
    def empty(self): return not bool(self.list)

class Edge:
    def __init__(self, to, cost):
        self.to = to
        self.cost = cost

def dijkstra(G):
    l = len(G)
    dist = [float('inf')]*l
    prev = [None]*l
    done = [False]*l
    dist[0] = 0
    pq = PQueue()
    pq.push((0, 0))
    while not pq.empty():
        c, v = pq.pop()
        done[v] = True
        for e in G[v]:
            cost = dist[v] + e.cost
            if cost < dist[e.to] and (not done[e.to]):
                dist[e.to] = cost
                prev[e.to] = v
                pq.push((cost, e.to))
    return dist, prev

if __name__ == '__main__':
    G = [[Edge(1, 7), Edge(2, 9), Edge(3, 14)],
        [Edge(0, 7), Edge(5, 15), Edge(2, 10)],
        [Edge(0, 9), Edge(1, 10), Edge(3, 2), Edge(5, 11)],
        [Edge(0, 14), Edge(2, 2), Edge(4, 9)],
        [Edge(3, 9), Edge(5, 6)],
        [Edge(1, 15), Edge(2, 11), Edge(4, 6)]]
    print(dijkstra(G)[0][5] == 20)
