#ifndef _GRAPH_H
#define _GRAPH_H

#include <vector>
#include <queue>
#include <algorithm>

#include <iostream>
#include <sstream>
#include <fstream>

#include <climits>

namespace Graph {
    typedef int vertex;
    struct distances_matrix {
        std::vector<std::vector<unsigned>> data;
        distances_matrix() {}
        distances_matrix(
            std::vector<std::vector<int>>& graph);
        void print();
    };

    class adjlist  {
    public:
        struct adjacent {
            vertex node;
            int weight;
        };
        

        adjlist(std::ifstream &file);
        void print();
        // minimum spanning tree weight
        int prim();

        // shortest paths
        std::vector<int> dijkstra(vertex source);
        std::vector<int> bellman_ford (vertex source);

    private:

        std::vector <std::vector <adjacent>> data;
        unsigned m;
        int satsum(unsigned x, unsigned y) {
            if (x > INT_MAX || y > INT_MAX)
                throw;
            unsigned s = x + y;
            return s < INT_MAX ? s : INT_MAX;

        }
    };

    class edgelist {
    public:
        struct edge {
            vertex orig;
            vertex dest;
            int weight;
        };
        edgelist(std::ifstream &file);
        void print();
        // minimum spanning tree weight
        int kruskal();

    private:
        std::vector<edge> data;
        unsigned n;
        bool sorted;
          
        struct UDS {
            std::vector<vertex> parent;
            std::vector<unsigned int> rank;

            UDS(unsigned n) {
                for (int i = 0; i < n; i++) {
                    parent.push_back(i);
                    rank.push_back(0);
                }
            }

            vertex find (vertex v) {
                if (v != parent[v])
                    parent[v] = find(parent[v]);
                return parent[v];
            }

            void merge (vertex x, vertex y) {
                x = find(x), y = find (y);
                if (rank[x] > rank[y])
                    parent[y] = x;
                else 
                    parent[x] = y;

                if (rank[x] == rank[y])
                    rank[y]++;
            }

        };
          
    };
     
    class adjmatrix {
    public:


        
        adjmatrix(std::ifstream &file);
        void print();
        static unsigned satsum(unsigned x, unsigned y) {
            unsigned s = x + y;
            return s < x || s < y ? UINT_MAX : s;
        }
        // shortest path matrix
        // distance_matrix floyd(GrafoMatriz& grafo);
        distances_matrix dantzig();
        distances_matrix floyd();
        
    private:
        std::vector<std::vector<int>> data;
        unsigned m;
        

    };
          
     
    inline bool operator>(const adjlist::adjacent& v,
                          const adjlist::adjacent& w) {
        return v.weight > w.weight;
    }

    adjlist::adjlist(std::ifstream &file) {
        int n, a, b, c;
        std::string line;

        getline(file, line);
        if (line.length() == 0) {
            std::cerr << "error: graph must not be null"
                      << std::endl;
            throw;
        }
          
        std::istringstream first_line(line);
        first_line >> n >> m;

        data.insert(data.end(), n, std::vector<adjacent>());
        for(int i = 0; i < m; i++) {
            getline (file, line);
            std::istringstream iss(line);
            iss >> a >> b >> c;
            data[a].push_back(adjacent{b, c});
            data[b].push_back(adjacent{a, c});
        }
    }


    int adjlist::prim() {
        unsigned n = data.size();
        std::priority_queue<adjacent, std::vector<adjacent>,
                            std::greater<adjacent>> pq;
        std::vector<int> distances(n, INT_MAX);
        std::vector<bool> visited(n, false);

        distances[0] = 0;
        visited[0] = true;
        pq.push(adjacent{0, 0});

        while (!pq.empty()) {
            adjacent w = pq.top(); pq.pop();
            visited[w.node] = true;
            for(adjacent& e : data[w.node]) {
                if(!visited[e.node]
                   && e.weight < distances[e.node]) {
                    distances[e.node] = e.weight;
                    pq.push(adjacent{ e.node, e.weight });
                }
            }
        }
        int sum = 0;
        for(int p : distances) { sum += p; }
        return sum;
    }

    std::vector<int> adjlist::dijkstra(vertex source) {
        unsigned n = data.size();
        std::priority_queue<adjacent, std::vector<adjacent>,
                            std::greater<adjacent>> pq;
        std::vector<int> distances(n, INT_MAX);
        std::vector<bool> visited(n, false);
        distances[0] = 0;
        pq.push(adjacent{0, 0});

        while (!pq.empty()) {
            adjacent w = pq.top(); pq.pop();
            if (!visited[w.node]) {
                visited[w.node] = true;
                for(adjacent& e : data[w.node]) {
                    int x = satsum(distances[w.node], e.weight);
                    if(!visited[e.node]
                       && x < distances[e.node]) {
                        distances[e.node] = x;
                        pq.push(adjacent{ e.node, x });
                    }
                }
            }
        }
        return distances;
    }

    std::vector<int> adjlist::bellman_ford (vertex source) {
        unsigned n = data.size();
        std::vector<int> distances(n, INT_MAX);
        distances[source] = 0;
        for (unsigned i = 1 ; i < n; i ++) {
            for (unsigned origin = 0; origin < n ; origin++) {
                for (unsigned k = 0;
                     k < data[origin].size();
                     k++) {
                    adjacent &e = data[origin][k];
                    unsigned sum
                        = satsum(distances[origin],
                                 e.weight);
                    if ( distances[e.node] > sum )
                        distances[e.node] = sum;
                }
            }
        }
        return distances;
    }
     
    edgelist::edgelist(std::ifstream &file) {
        int N, M, a, b, c;
        std::string line;
        getline(file, line);
        if (line.length() == 0) {
            std::cerr << "error: graph must not be null"
                      << std::endl;
            throw;
        }
        std::istringstream first_line(line);
        first_line >> N >> M;
        n = N;
        for(int i = 0; i < M; i++) {
            getline (file, line);
            std::istringstream iss(line);
            iss >> a >> b >> c;
            data.push_back(edge{a, b, c});
        }
        std::sort(data.begin(),
                  data.end(),
                  [](edge&  e, edge&  f) {
                      return e.weight < f.weight;
                  });
        sorted = true;
    }

    int edgelist::kruskal() {
        int sum = 0;
        UDS uds(n);
        if (!sorted) {
            std::cerr << "not sorted!" << std::endl;
            throw;
        }
          
        for (edge& e : data) {
            if (uds.find (e.orig) != uds.find (e.dest)) {
                sum += e.weight;
                uds.merge (e.orig, e.dest);
            }
        }
        return sum;
    }
    void edgelist::print() {
        std::vector<edge> sorted(data);
        for (std::vector<edge>::iterator it = sorted.begin();
             it != sorted.end(); it++) {
            if (it->orig > it->dest)
                std::swap(it->orig,it->dest);
        }
        sort(sorted.begin(), sorted.end(),
             [](edge x, edge y) {
                 return x.orig < y.orig || (x.orig == y.orig && x.dest < y.dest);
             });
        std::cout << n << data.size() << std::endl;
        for (std::vector<edge>::iterator it = sorted.begin();
             it != sorted.end(); it++) {
            std::cout << it->orig << " " << it->dest << " "
                      << it-> weight << std::endl;
        }
    }

    void adjlist::print() {
        for (int i = 0; i < data.size(); i++) {
            std::vector<adjacent> sorted(data[i]);
            std::sort(sorted.begin(), sorted.end(),
                      [](adjacent x, adjacent y) {
                          return x.node < y.node; 
                      });
            
            for (std::vector<adjacent>::iterator it = sorted.begin();
                 it != sorted.end(); it++) {
                if (it -> weight < INT_MAX)
                    std::cout << i << " " << it->node
                         << " " << it -> weight << std::endl;
            }
        }
    }
        adjmatrix::adjmatrix(std::ifstream &file) {
            int n, a, b, c;
            std::string line;

            std::getline(file, line);
            if (line.length() == 0) {
                std::cerr << "error: graph must not be null"
                          << std::endl;
                throw;
            }
         
            std::istringstream first_line(line);
            first_line >> n >> m;

            for (int i = 0; i < n; i++) {
                data.push_back(std::vector<int>(n, INT_MAX));
            }

            unsigned orig, dest; int weight;

            for (unsigned edge = 0; edge < m; edge++) {
                std::getline(file, line);
                std::istringstream iss(line);
                iss >> orig >> dest >> weight;
                data[orig][dest] = data[dest][orig] = weight;
            }
        }

    void adjmatrix::print() {
        int n = data.size();
        std::cout << n << " " << m << std::endl;
        for (int i = 0; i < n; i++)
            for(int j = i + 1; j < n; j++) {
                if (data[i][j] != INT_MAX)
                    std::cout << i << " " << j << " "
                              << data[i][j] << std::endl;
            }

          
    }

    distances_matrix::distances_matrix(
        std::vector<std::vector<int>>& graph) {
        unsigned n = graph.size();
        for (unsigned i = 0; i < n; i++) {
            data.push_back(std::vector<unsigned>());
            for (unsigned j = 0; j < n; j ++) {
                if (i == j)
                    data[i].push_back(0);
                else
                    data[i].push_back(graph[i][j]);
            }
        }

    }

    distances_matrix adjmatrix::dantzig() {
        unsigned n = data.size();
        distances_matrix dist_mat(data);

        for (unsigned k = 1; k < n; k ++) {
            for (unsigned i = 0; i < k; i ++) {
                unsigned row = UINT_MAX;
                unsigned col = UINT_MAX;
                for (unsigned j = 0; j < k; j ++) {
                    unsigned ij = dist_mat.data[i][j];
                    unsigned jk = dist_mat.data[j][k];
                    unsigned kj = dist_mat.data[j][k];
                    unsigned ji = dist_mat.data[j][i];
                    row = std::min(row, adjmatrix::satsum(ij,jk));
                    col =std::min(col, adjmatrix::satsum(kj, ji));
                }

                dist_mat.data[i][k] = row;
                dist_mat.data[k][i] = col;
            }

            for (unsigned i = 0; i < k; i ++) {
                for (unsigned j = 0; j < k; j ++) {
                    dist_mat.data[i][j]
                        = std::min(
                            dist_mat.data[i][j],
                            adjmatrix::satsum(
                                dist_mat.data[i][k],
                                dist_mat.data[k][j]));
			}
		}
	}

	return dist_mat;

    }

    distances_matrix adjmatrix::floyd() {
        unsigned n = data.size();
        distances_matrix dist_mat;
        for (unsigned i = 0; i < n; i ++) {
            dist_mat.data.push_back(std::vector<unsigned>());
            for (unsigned j = 0; j < n; j ++) {
                if(i == j) {
                    dist_mat.data[i].push_back(0);
                } else {
                    dist_mat.data[i].push_back(data[i][j]);
                }
            }
        }
        for (unsigned k = 0; k < n; k++) {
            for (unsigned i = 0 ; i < n ; i++) {
                for (unsigned j = 0; j < n; j++) {
                    dist_mat.data[i][j]
                        = std::min (dist_mat.data[i][j],
                                    satsum(dist_mat.data[i][k],
                                           dist_mat.data[k][j]));
                }
            }
    }
        return dist_mat;
    }


     void distances_matrix::print() {
         unsigned n = data.size();
         for (int col = 0; col < n; col++) {
             for (int row = 0; row < n; row++) {
                 std::cout << data[row][col] << " ";
             }
             std::cout << std::endl;
         }
     }
    
} /* Graph namespace */

#endif /* _GRAPH_H */
