#pragma once

#include <unordered_map>

#include "weighted-graph.hpp"
#include "graph-types.h"

template <typename T>
void computeIndegrees(const WeightedGraph<T>& graph, std::unordered_map<value_type<T>, int>& indegrees) {
    //graph is made up of key value pairs that have <key(index), adjacency_list(aka list of key-value pairs)
    for(auto vertex : graph){ //setting all elements in indegrees to 0
        indegrees[vertex.first] = 0;
    }
    for(auto adj_list : graph){ //iterates through the entire graph
        for(auto vertex : adj_list.second){ //for each vertex in the adjacency list from the current node we are on
            indegrees[vertex.first] = indegrees[vertex.first] + 1; //use the key to increment the number of indegrees at that key position
        }
    }
}
