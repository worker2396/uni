#include "tsp.hpp"


int main() {
    std::vector<std::vector<double>> cost_matrix{
            {INF,  3.0,  4.0,  2.0,  7.0},
            {3.0,  INF,  4.0,  6.0,  3.0},
            {4.0,  4.0,  INF,  5.0,  8.0},
            {2.0,  6.0,  5.0,  INF,  6.0},
            {7.0,  3.0,  8.0,  6.0,  INF},
    };
    std::vector<int> best_path = tsp(cost_matrix);
    for (auto it : best_path) {
        std::cout<<best_path[it]<<' ';
    }
    return 0;
}
