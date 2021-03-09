#ifndef FIRST_PR_TSP_HPP
#define FIRST_PR_TSP_HPP
#include <algorithm>
#include <iostream>
#include <tuple>
#include <list>
#include <map>
#include <cmath>
#include <cfloat>
#include <vector>
#include <string>


std::vector<int> tsp(std::vector<std::vector<double>> cost_matrix);
double get_forbidden_cost();
const double INF = get_forbidden_cost();

class matrix_of_cost {
public:

    matrix_of_cost(std::vector<std::vector<double>> matrix):cost_matrix{matrix}{}
    unsigned matrix_size{};
    std::vector<int> best_path{};
    std::map<double, std::tuple<int,int>> map_of_points{};
    std::vector<double> mins_in_rows{};
    std::vector<double> mins_in_cols{};

    std::vector<std::vector<double>> cost_matrix{};
    std::vector<std::tuple<int,int>> zero_points_coordinates{};
    std::vector<std::tuple<int,int>> best_answer;




    void matrix_get_size();


    void find_lowest_val_in_rows();
    void find_lowest_val_in_cols();

    void subst_val_row();
    void subst_val_col();

    void find_dots();

    void create_map();



    void add_to_path_and_remove_row_col();
    void sort_tuples_vector();
    void move_to_path();
    std::vector<int> get_path();

};

#endif //FIRST_PR_TSP_HPP
