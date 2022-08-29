/*
Dijkstra's Algorithm | Shortest Path in a Weighted Graph
When to Use Dijkstra Algorithm?
Given a weighted graph, what is fastest way to compute the shortest path from a node to every other node? What we mean by weighted graph is that every edge is now assigned a weight that and our distance increases by the weight instead of 1. This problem means that our previous graph theory algorithms such as Vanilla Breadth First Search don't work anymore as they are designed for unweighted graphs. The previous algorithms assumed each edge was equal so only need to visit each node once. That no longer works as the first time we visit a node does not guarantee minimum distance and we may need to revisit the node if we find a shorter path. Is there a way to update them to account for weighted graphs?

The Shortest-Path Faster Algorithm (SPFA)
The Shortest-Path Faster Algorithm abbreviated to SPFA can be thought of as a BFS variant. Instead of checking whether or not the neighbour node has been visited we instead see if we can improve our distance by checking the neighbor nodes and if it possible to update to a smaller distance and push the node into our queue. If it is greater then we want to update the node's distance since we have found a shorter path and push the node into our queue. This algorithm runs in worst case O(n * m) where n is the number of nodes in our graph and m is thg number of edges. Here is an implementation for how the Shortest-Path Faster Algorithm would work.
*/

#include <queue> // queue
#include <algorithm> // copy
#include <iostream> // cin, cout, streamsize
#include <iterator> // back_inserter, istream_iterator
#include <limits> // numeric_limits
#include <queue> // queue
#include <sstream> // istringstream
#include <string> // getline, string
#include <unordered_set> // unordered_set
#include <vector> // vector

std::vector<std::pair<int, int>> get_neighbors(std::vector<std::vector<std::pair<int, int>>> &graph, int node) {
  return graph[node];
}

int bfs(std::vector<std::vector<std::pair<int, int>>> &graph, int root, int target) {
  std::queue<int> q;
  q.push(root);
  std::vector<int> distance(graph.size() + 1, std::numeric_limits<int>::max());
  distance[root] = 0;
  while (!q.empty()) {
    int node = q.front(); q.pop();
    for (std::pair<int, int> neighbor : get_neighbors(graph, node)) {
      int id = neighbor.first;
      int weight = neighbor.second;
      if (distance[id] <= distance[node] + weight) {
        continue;
      }
      q.push(id);
      distance[id] = distance[node] + weight;
    }
  }
  return distance[target] == std::numeric_limits<int>::max() ? -1 : distance[target];
}

int bfs_dijkstra(std::vector<std::vector<std::pair<int, int>>> &graph, int root, int target) {
  std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> pq;
  std::vector<int> distance(graph.size() + 1, std::numeric_limits<int>::max());
  distance[root] = 0;
  pq.push({0, root});
  while (!pq.empty()) {
    std::pair<int, int> cur = pq.top(); pq.pop();
    int node = cur.second;
    for (std::pair<int, int> neighbor : get_neighbors(graph, node)) {
      int id = neighbor.first;
      int weight = neighbor.second;
      int d = distance[node] + weight;
      if (distance[id] <= d) {
        continue;
      }
      pq.push({d, id});
      distance[id] = d;
    }
  }
  return distance[target] == std::numeric_limits<int>::max() ? -1 : distance[target];
}

int shortest_path(std::vector<std::vector<std::pair<int, int>>> &graph, int a, int b) {
  //return bfs(graph, a, b);
    return bfs_dijkstra(graph, a, b);
}

template<typename T>
std::vector<T> get_words() {
    std::string line;
    std::getline(std::cin, line);
    std::istringstream ss{line};
    std::vector<T> v;
    std::copy(std::istream_iterator<T>{ss}, std::istream_iterator<T>{}, std::back_inserter(v));
    return v;
}

void ignore_line() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    int graph_length;
    std::cin >> graph_length;
    ignore_line();
    std::vector<std::vector<std::pair<int, int>>> graph;
    for (int i = 0; i < graph_length; i++) {
      std::vector<int> line = get_words<int>();
      std::vector<std::pair<int, int>> lm;
      for (int j = 0; j < line.size(); j += 2) {
        lm.push_back({line[j], line[j + 1]});
      }
      graph.push_back(lm);
    }
    int a;
    std::cin >> a;
    ignore_line();
    int b;
    std::cin >> b;
    ignore_line();
    int res = shortest_path(graph, a, b);
    std::cout << res << '\n';
}
