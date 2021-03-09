
#include "tsp.hpp"

double get_forbidden_cost(){
    return NAN;
}




void matrix_of_cost::matrix_get_size() {
    matrix_size = cost_matrix[0].size();
}


std::vector<int> tsp(std::vector<std::vector<double>> matrix1) {
    matrix_of_cost matrix(matrix1);
    matrix.matrix_of_cost::matrix_get_size();
    for (int k = 0; k < matrix1.size(); ++k) {
        matrix.find_lowest_val_in_rows();
        matrix.subst_val_row();
        matrix.find_lowest_val_in_cols();
        matrix.subst_val_col();
        matrix.find_dots();
        matrix.create_map();
        matrix.add_to_path_and_remove_row_col();
        matrix.mins_in_rows.clear();
        matrix.mins_in_cols.clear();

    }
    matrix.sort_tuples_vector();
    matrix.move_to_path();
    return matrix.get_path();
}



void matrix_of_cost::find_lowest_val_in_rows() {
    double min;
    for(int i=0;i<matrix_size;i++){
        min = DBL_MAX;
        for(int j=0;j<matrix_size;j++){
            if((cost_matrix[i][j]!=NAN)&&(cost_matrix[i][j]<min)){
                min = cost_matrix[i][j];
            }
        }
        if((min == DBL_MAX)||(min == INF)){min = 0;}
        mins_in_rows.push_back(min);

    }


}
void matrix_of_cost::find_lowest_val_in_cols(){
    double min;

    for(int i=0;i<matrix_size;i++){
        min = DBL_MAX;
        for(int j=0;j<matrix_size;j++){
            if((cost_matrix[j][i]!=NAN)&&(cost_matrix[j][i]<min)){
                min = cost_matrix[j][i];
            }
        }
        if((min == DBL_MAX)||(min == INF)){min = 0;}
        mins_in_cols.push_back(min);

    }
//    matrix_minimums.insert(mins_in_cols.end(),mins_in_cols.begin(),mins_in_cols.end());

}

void matrix_of_cost::subst_val_row(){
    for (int i = 0; i < matrix_size; i++){
        for (int j = 0; j < matrix_size; j++){
            if((cost_matrix[i][j]) != NAN){
                cost_matrix[i][j] -= mins_in_rows[i];
            }
        }
    }
    mins_in_rows.clear();

}

void matrix_of_cost::subst_val_col(){
    for (int i = 0; i < matrix_size; i++){
        for (int j = 0; j < matrix_size; j++){
            if((cost_matrix[j][i]) != NAN){
                cost_matrix[j][i] -= mins_in_cols[i];
            }
        }
    }
    mins_in_cols.clear();
}


void matrix_of_cost::find_dots(){
    std::tuple<int,int> coordinate;

    for (int i = 0; i < matrix_size; i++) {
        for (int j = 0; j < matrix_size; j++) {
            if (cost_matrix[i][j] == 0) {
                if (std::find(zero_points_coordinates.begin(),zero_points_coordinates.end(), std::make_tuple(i, j)) == zero_points_coordinates.end()){
                    coordinate = std::make_tuple(i, j);
                    zero_points_coordinates.push_back(coordinate);

                }
            }
        }
    }
}


void matrix_of_cost::create_map() {
    int it = zero_points_coordinates.size();
    double min_x;
    double min_y;
    double cost_of_road;


    while(it!=0) {
        int x_coordinate = std::get<0>(zero_points_coordinates[it - 1]);
        int y_coordinate = std::get<1>(zero_points_coordinates[it - 1]);
        min_x = DBL_MAX;
        min_y = DBL_MAX;
        for(int i = 0; i < matrix_size; i++){
            if((cost_matrix[x_coordinate][i]!=NAN)&&(i!=y_coordinate)&&(cost_matrix[x_coordinate][i]<min_x)){
                min_x = cost_matrix[x_coordinate][i];
            }
        }
        for (int j = 0; j < matrix_size; j++) {
            if((cost_matrix[j][y_coordinate]!=NAN)&&(j!=x_coordinate)&&(cost_matrix[j][y_coordinate]<min_y)){
                min_y = cost_matrix[j][y_coordinate];
            }
        }
        cost_of_road = min_x + min_y;

        map_of_points[cost_of_road] = zero_points_coordinates[it - 1];

        it--;
    }
    zero_points_coordinates.clear();
}

void matrix_of_cost::add_to_path_and_remove_row_col() {
    int x_coordinate;
    int y_coordinate;
    //auto v = map_of_points.rbegin()->first;
    std::tuple<int,int> point = map_of_points.rbegin()-> second;
    best_answer.push_back(point);
    double v = map_of_points.rbegin()->first;

    std::tie(x_coordinate,y_coordinate) = point;
    for (int i = 0; i < matrix_size; ++i){
            cost_matrix[x_coordinate][i] = NAN;
    }
    for (int j = 0; j < matrix_size; ++j) {
            cost_matrix[j][y_coordinate] = NAN;
    }
    cost_matrix[x_coordinate][y_coordinate] = NAN;
    cost_matrix[y_coordinate][x_coordinate] = NAN;
    map_of_points.clear();
//    auto it_for_point = std::find(zero_points_coordinates.begin(),zero_points_coordinates.end(),std::make_tuple(x_coordinate,y_coordinate));
//    zero_points_coordinates.erase(it_for_point);
//    auto it_inverse = std::find(zero_points_coordinates.begin(),zero_points_coordinates.end(),std::make_tuple(y_coordinate,x_coordinate));
//    zero_points_coordinates.erase(it_inverse);
}

void matrix_of_cost::sort_tuples_vector() {
    std::vector<std::tuple<int,int>> best_answer_temp;
    best_answer_temp.push_back(best_answer[0]);
    for (int j = 0; j < best_answer.size() - 1; ++j) {
        for (auto & i : best_answer) {
                if (std::get<0>(i) == std::get<1>(best_answer_temp[j])) {
                    best_answer_temp.push_back(i);
                }
        }

    }
    best_answer = best_answer_temp;
}

void matrix_of_cost::move_to_path() {
        for (auto & i : best_answer) {
            best_path.push_back(std::get<0>(i));
        }
        best_path.push_back(std::get<0>(best_answer[0]));


}

std::vector<int> matrix_of_cost::get_path() {
    double it = 0;
    while(it != best_path.size()){
        best_path[it] += 1;
        it++;
    }
    return best_path;
}


