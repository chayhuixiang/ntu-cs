import math
import heapq
import random
import csv
import time

def dijkstra(graph, start):
  V = len(graph)
  d = [math.inf for i in range(V)]
  pi = [None for i in range(V)]
  visited = [False for i in range(V)]
  pq = []
  if V > 0:
    pq = [(0, start)]
    d[start] = 0

  while len(pq):
    (dist, curr) = heapq.heappop(pq)
    if visited[curr] == True:
      continue
    visited[curr] = True
    adjList = graph[curr]
    for (v, weight) in adjList:
      dist_from_start = weight + d[curr]
      if dist_from_start < d[v]:
        d[v] = dist_from_start
        pi[v] = curr
        heapq.heappush(pq, (dist_from_start, v))

  return d, pi

def randomiseGraph(graph, V, E):
  while E > 0:
    row = random.randint(0, V-1)
    col = random.randint(0, V-1)
    weight = random.randint(1, 10)
    if row == col:
      continue
    if graph[row][col] == 0:
      graph[row][col] = weight
      E -= 1

def randomiseConnectedGraph(graph, V):
  for row in range(V):
    for col in range(V):
      weight = random.randint(1, 10)
      if row == col:
        continue
      graph[row][col] = weight

def convertList(graph, V):
  result = {}
  for i in range(V):
    result[i] = []
  for row in range(V):
    for col in range(V):
      weight = graph[row][col]
      if weight > 0:
        result[row].append((col, weight))

  return result


if __name__ == "__main__":

  # # -----
  # # adjacency list is in the format (vertice, weight)
  # # eg. 
  # graph = {
  #   0: [(1, 10), (3, 5)],
  #   1: [(3, 2), (2, 1)],
  #   2: [(4, 4)],
  #   3: [(1, 3), (2, 9), (4, 2)],
  #   4: [(0, 7), (2, 6)]
  # }
  # # -----
  
  header = ["V", "E", "time"]
  f = open("data_b3.csv", "w")
  writer = csv.writer(f)
  writer.writerow(header)

  V = 0
  while V <= 1000:
    E = 0
    while E < (V - 1) * (V - 1) and E < 10000000: # Maximum number of edges
      V = int(input("Enter number of vertices (V): "))
      E = int(input("Enter number of edges (E): "))
      graph = [[0 for i in range(V)] for i in range(V)]
      randomiseGraph(graph, V)
      graph = convertList(graph, V)

      # print("Graph: ")
      # print(graph)
      # print()

      start = time.time()
      [d, pi] = dijkstra(graph, 0)
      end = time.time()
      # print(f"d array: {d}")
      # print(f"pi array: {pi}")
      print(f"Time taken in seconds for V = {V} and E = {E}: {end - start}")
      writer.writerow([V, E, end-start])
      E += 2000

    # if str(E)[0] == "5":
    #   E *= 2
    # else:
    #   E *= 5
    # if str(V)[0] == "5":
    #   V *= 2
    # else:
    #   V *= 5
    V += 50

  f.close()

