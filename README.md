# SmartCity-Planner
1. Electricity Network Planner (MST)
  Models buildings as nodes and cables as weighted undirected edges.

  Uses Prim’s algorithm to compute the minimum total cable length needed to connect all buildings.

  Works on disconnected graphs too, ensuring maximum flexibility for large layouts.

  Outputs both the total length and which cables to lay between buildings.

2. Shortest Path Finder (Dijkstra’s Algorithm)
  Models cities/points as nodes and roads as weighted edges.

  Computes shortest path between any two user-selected cities.

  Outputs the distance and the path route step-by-step.

3. Topological Sort (Dependency Resolution)
  Uses DFS-based Topological Sorting.

  Helps in identifying task or city visit order in acyclic graphs (DAGs).

  Detects and reports if the graph has cycles, where topological order is not possible.
