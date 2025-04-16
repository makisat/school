#include <iostream>
#include <vector>

class Matrix {
private:
  int rows;
  int cols;
  std::vector<std::vector<int>> data;
public:
  Matrix(int rows, int cols) : rows(rows), cols(cols) {
    data.resize(rows);
    for (auto& row : data) {
      row.resize(cols, 0);
    }
  }

  void setData(const std::vector<std::vector<int>>& new_data) {
    data = new_data;
}

  void showData() {
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        std::cout << data[i][j] << " ";
      }
      std::cout << std::endl;
    }
  }
};

int main() {

  std::vector<std::vector<int>> data_A =
  { {6, 4},
    {8, 3} };

  std::vector<std::vector<int>> data_B =
  { {1, 2, 3},
    {4, 5, 6} };

  Matrix A = Matrix(2, 2);
  A.setData(data_A);
  Matrix B = Matrix(2, 3);
  B.setData(data_B);

  std::cout << "data A" << std::endl;
  A.showData();

  std::cout << "data B" << std::endl;
  B.showData();

  return 0;
}


