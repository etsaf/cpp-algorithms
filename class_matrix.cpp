#include <iostream>
#include <tuple>
#include <vector>

template <typename T>
class Matrix{
private:
    std::vector<std::vector<T>> matrix;

public:
    Matrix(const std::vector<std::vector<T>>& m)
            : matrix(m) {}

    std::pair<size_t, size_t> size() const {
        return {matrix.size(), matrix[0].size()};
    }

    Matrix<T>& operator+=(const Matrix<T>& rhs) {
        auto [rows, columns] = size();
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < columns; ++j) {
                matrix[i][j] += rhs.matrix[i][j];
            }
        }
        return *this;
    }

    Matrix<T> operator+(const Matrix<T>& rhs) const {
        Matrix<T> temp(*this);
        temp += rhs;
        return temp;
    }

    template<typename V>
    Matrix<T>& operator*=(const V& n) {
        auto [rows, columns] = size();
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < columns; ++j) {
                matrix[i][j] *= n;
            }
        }
        return *this;
    }

    template <typename W>
    Matrix<T> operator*(const W& n) const {
        Matrix<T> temp(*this);
        temp *= n;
        return temp;
    }

    Matrix<T>& transpose() {
        auto [rows, columns] = size();
        std::vector<std::vector<T>> v;
        v.resize(columns);
        for (size_t i = 0; i < columns; ++i) {
            for (size_t j = 0; j < rows; ++j) {
                v[i].push_back(matrix[j][i]);
            }
        }
        matrix = v;
        return *this;
    }

    Matrix<T> transposed() const {
        Matrix<T> temp(*this);
        return temp.transpose();
    }

    Matrix<T> operator*(const Matrix<T>& rhs) const {
        std::vector<std::vector<T>> v;
        auto [rows1, columns1] = size();
        auto [rows2, columns2] = rhs.size();
        assert(columns1 == rows2);
        v.resize(rows1, std::vector<T>(columns2));
        for (size_t i = 0; i < rows1; ++i) {
            for (size_t j = 0; j < columns2; ++j) {
                for (size_t k = 0; k < rows2; ++k) {
                    v[i][j] += matrix[i][k] * rhs.matrix[k][j];
                }
            }
        }
        return Matrix(v);
    }

    Matrix<T>& operator*=(const Matrix<T>& rhs) {
        auto [rows1, columns1] = size();
        auto [rows2, columns2] = rhs.size();
        assert(columns1 == rows2);
        *this = *this * rhs;
        return *this;
    }

    template <typename U>
    friend std::ostream& operator<<(std::ostream& out, const Matrix<U>& m);

    class Iterator {
    private:
        Matrix<T>* data;
        size_t row = 0;
        size_t column = 0;

    public:
        friend class Matrix<T>;

        Iterator(Matrix<T>* data_)
                : data(data_) {
        }

        T& operator*() {
            return data->matrix[row][column];
        }

        std::pair<size_t, size_t> GetSize() {
            return data->size();
        }

        Iterator& operator++() {
            auto [rows1, columns1] = GetSize();
            ++column;
            if (column == columns1) {
                column = 0;
                ++row;
            }
            return *this;
        }

        Iterator operator++(int) {
            Iterator temp(*this);
            ++(*this);
            return temp;
        }

        bool operator==(Iterator other) const {
            return row == other.row && column == other.column;
        }

        bool operator!=(Iterator other) const {
            return !(*this == other);
        }
    };

    Iterator begin() {
        return Iterator(this);
    }

    Iterator end() {
        auto [rows1, columns1] = size();
        auto it = Iterator(this);
        it.row = rows1;
        it.column = 0;
        return it;
    }

    class ConstIterator {
    private:
        Matrix<T>* data;
        size_t row = 0;
        size_t column = 0;

    public:
        friend class Matrix<T>;

        ConstIterator(const Matrix<T>* data_)
                : data((Matrix<T> *) data_) {
        }

        T& operator*() const {
            return data->matrix[row][column];
        }

        std::pair<size_t, size_t> GetSize() const {
            return data->size();
        }

        ConstIterator& operator++() {
            auto [rows1, columns1] = GetSize();
            ++column;
            if (column == columns1) {
                column = 0;
                ++row;
            }
            return *this;
        }

        ConstIterator operator++(int) {
            ConstIterator temp(*this);
            ++(*this);
            return temp;
        }

        bool operator==(ConstIterator other) const {
            return row == other.row && column == other.column;
        }

        bool operator!=(ConstIterator other) const {
            return !(*this == other);
        }
    };

    ConstIterator begin() const {
        return ConstIterator(this);
    }

    ConstIterator end() const {
        auto [rows1, columns1] = size();
        auto it = ConstIterator(this);
        it.row = rows1;
        it.column = 0;
        return it;
    }
};

template <typename T, typename U>
Matrix<T> operator*(const U& n, const Matrix<T>& m) {
    Matrix<T> temp(m);
    temp *= n;
    return temp;
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const Matrix<T>& m) {
    auto [rows, columns] = m.size();
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < columns; ++j) {
            if (j != 0) {
                out << '\t';
            }
            out << m.matrix[i][j];
        }
        if (i != (rows - 1)) {
            out << '\n';
        }
    }
    return out;
}