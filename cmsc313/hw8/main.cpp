#include <vector>
#include <iostream>

class Matrix {
private:
  int rows;
  int cols;
  std::vector<std::vector<int>> data;

public:
  Matrix(int r, int c) : rows(r), cols(c), data(r, std::vector<int>(c, 0)) {}

  Matrix(const std::vector<std::vector<int>>& init_data) {
    rows = init_data.size();
    cols = init_data[0].size();
    data = init_data;
  }

  int getRows() const { return rows; }
  int getCols() const { return cols; }

  void showData() const {
    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < cols; ++j) {
        std::cout << data[i][j] << " ";
      }
      std::cout << std::endl;
    }
  }

  Matrix transpose() const {
    Matrix result(cols, rows);
    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < cols; ++j) {
        result.data[j][i] = data[i][j];
      }
    }
    return result;
  }

  friend Matrix operator+(const Matrix& a, const Matrix& b) {
    Matrix result(a.rows, a.cols);
    for (int i = 0; i < a.rows; ++i) {
      for (int j = 0; j < a.cols; ++j) {
        result.data[i][j] = a.data[i][j] + b.data[i][j];
      }
    }
    return result;
  }

  friend Matrix operator*(int scalar, const Matrix& m) {
    Matrix result(m.rows, m.cols);
    for (int i = 0; i < m.rows; ++i) {
      for (int j = 0; j < m.cols; ++j) {
        result.data[i][j] = scalar * m.data[i][j];
      }
    }
    return result;
  }

  friend Matrix operator*(const Matrix& a, const Matrix& b) {
    Matrix result(a.rows, b.cols);
    for (int i = 0; i < a.rows; ++i) {
      for (int j = 0; j < b.cols; ++j) {
        int sum = 0;
        for (int k = 0; k < a.cols; ++k) {
          sum += a.data[i][k] * b.data[k][j];
        }
        result.data[i][j] = sum;
      }
    }
    return result;
  }
};

int main() {
  Matrix A({{6, 4}, {8, 3}});
  Matrix B({{1, 2, 3}, {4, 5, 6}});
  Matrix C({{2, 4, 6}, {1, 3, 5}});

  std::cout << "A:" << std::endl;
  A.showData();
  std::cout << "\nB:" << std::endl;
  B.showData();
  std::cout << "\nC:" << std::endl;
  C.showData();

  Matrix T1 = 3 * B;
  Matrix T2 = C.transpose();
  Matrix T3 = T1 * T2;
  Matrix D = A + T3;

  std::cout << "\nD = A + (3 * B) * C^T:" << std::endl;
  D.showData();

  return 0;
}
