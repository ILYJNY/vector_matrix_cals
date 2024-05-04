#include "vector"
#include "cmath"
#include "complex"
#define MATRIX_LF std::vector<std::vector<long double>>
#define VECTOR_LF std::vector<long double>
#define MATRIX_CLF std::vector<std::vector<std::complex<long double>>>

long double vector_size(VECTOR_LF vector) {
    long double for_result = 0;
    for (long double i : vector) {
        for_result += powl(i, 2);
    }
    return sqrtl(for_result);
}

MATRIX_LF floor_matrix(MATRIX_LF matrix) {
    MATRIX_LF result;
    for (unsigned long long int i=0;matrix.size();i++) {
        for (unsigned long long int j=0;matrix[0].size();j++) {
            result[i][j] = floorl(matrix[i][j]);
        }
    }
    return result;
}


MATRIX_LF round_matrix(MATRIX_LF matrix) {//반올림
    MATRIX_LF result;
    for (unsigned long long int i=0;matrix.size();i++) {
        for (unsigned long long int j=0;matrix[0].size();j++) {
            result[i][j] = floorl(matrix[i][j] + 1/2);
        }
    }
    return result;
}



MATRIX_LF matrix_scalar_multiply(MATRIX_LF matrix, long double scalar) {
//    MATRIX_LF result(a.size(), VECTOR_LF(b[0].size()));
//    for (unsigned long long int i = 0; i < a.size(); i++) {
//        for (unsigned long long int j = 0; j < b[0].size(); j++) {
//            for (unsigned long long int k = 0; k < a[0].size(); k++) {
//                result[i][j] += a[i][k] * b[k][j];
//            }
//        }
//    }
    MATRIX_LF result;
    for (unsigned long long int i=0;i<matrix.size();i++) {
        for (unsigned long long int j=0;j<matrix[0].size();j++) {
            result[i][j] = matrix[i][j] * scalar;
        }
    }
    return result;
}

VECTOR_LF vector_scalar_times(VECTOR_LF vector, long double scalar) {
    for (long double & i : vector) {
        i *= scalar;
    }
    return vector;
}

VECTOR_LF vector_cross_product(VECTOR_LF a, VECTOR_LF b) {
    if (a.size() != b.size()) {
        throw std::invalid_argument("Vectors must have the same size");
    }
    std::vector<long double> result;
    for (unsigned long long int i = 0;i<a.size();i++) {
        if (i+1 <= a.size() || i+2 <= a.size()) {
            unsigned long long int alpha;
            unsigned long long int beta;
            if (i+1 <= a.size()) {
                alpha = i + 1 - a.size();
                beta = i + 2 - a.size();
            }
            if (i+2 <= a.size()) {
                alpha = i + 1;
                beta = i + 2 - a.size();
            }
            result[i] = a[alpha]*b[beta] - a[beta]*b[alpha];
        }
        else {
            result[i] = a[i+1]*b[i+2] - a[i+2]*b[i+1];
        }
    }
}

long double vector_dot_product(std::vector<long double> a, std::vector<long double> b) {
    if (a.size() != b.size()) {
        throw std::invalid_argument("Vectors must have the same size");
    }
    long double result = 0;
    for (unsigned long long int i = 0;i<a.size();i++) {
        result += a[i] * b[i];
    }
    return result;
}


std::vector<std::vector<long double>> matrix_timesv(std::vector<std::vector<long double>> a, std::vector<std::vector<long double>> b) {
    std::vector<unsigned long long int> size_of_as(a.size());
    std::vector<unsigned long long int> size_of_bs(b.size());
    for (const auto & i : a) {
        size_of_as.push_back(i.size());
    }
    for (unsigned long long int j = 0;j<size_of_as.size();j++) {
        if (size_of_as[j] != size_of_as[0]) {
            throw std::invalid_argument("Invalid Matrix");
        }
    }
    for (const auto & i : b) {
        size_of_bs.push_back(i.size());
    }
    for (unsigned long long int k = 0;k<size_of_as.size();k++) {
        if (size_of_bs[k] != size_of_bs[0]) {
            throw std::invalid_argument("Invalid Matrix");
        }
    }

    if (a.size() != b[0].size()) {
        throw std::invalid_argument("Cannot Calculate because first's j and second's i size is not equal");
    }

//    std::vector<std::vector<long double>> result(a.size(), std::vector<long double>(b[0].size(), 0));
//    for (unsigned long long int i = 0; i < a.size(); i++) {
//        for (unsigned long long int j = 0; j < b[0].size(); j++) {
//            for (unsigned long long int k = 0; k < a[0].size(); k++) {
//                result[i][j] += a[i][k] * b[k][j];
//            }
//        }
//    }
    std::vector<std::vector<long double>> result(b.size());
    for (unsigned long long int i = 0;i<a[0].size();i++) {
        for (unsigned long long int j = 0;j<b.size();j++) {
            long double for_result = 0;
            for (unsigned long long int k = 0;k<a[0].size();k++) {
                for_result += a[k][i] * b[j][k];
            }
            result[i][j] = for_result;
        }
    }
    return result;
}
//
//
//long double** matrix_timesss(long double** a, long double** b) {
//    std::vector<unsigned long long int> size_of_as;
//    std::vector<unsigned long long int> size_of_bs;
//    for (unsigned long long int i = 0;i<a.size();i++) {
//        size_of_as.push_back(a[i].size());
//    }
//    for (unsigned long long int j = 0;j<size_of_as.size();j++) {
//        if (size_of_as[j] != size_of_as[0]) {
//            throw std::invalid_argument("Invalid Matrix");
//        }
//    }
//    for (unsigned long long int i = 0;i<b.size();i++) {
//        size_of_bs.push_back(b[i].size());
//    }
//    for (unsigned long long int k = 0;k<size_of_as.size();k++) {
//        if (size_of_bs[k] != size_of_bs[0]) {
//            throw std::invalid_argument("Invalid Matrix");
//        }
//    }
//
//    if (a.size() != b[0].size()) {
//        throw std::invalid_argument("Cannot Calculate because first's j and second's i size is not equal");
//    }
//
////    std::vector<std::vector<long double>> result(a.size(), std::vector<long double>(b[0].size(), 0));
////    for (unsigned long long int i = 0; i < a.size(); i++) {
////        for (unsigned long long int j = 0; j < b[0].size(); j++) {
////            for (unsigned long long int k = 0; k < a[0].size(); k++) {
////                result[i][j] += a[i][k] * b[k][j];
////            }
////        }
////    }
//    std::vector<std::vector<long double>> result;
//    for (unsigned long long int i = 0;i<a[0].size();i++) {
//        for (unsigned long long int j = 0;j<b.size();j++) {
//            long double for_result = 0;
//            for (unsigned long long int k = 0;k<a[0].size();k++) {
//                for_result += a[k][i] * b[j][k];
//            }
//            result[i][j] = for_result;
//        }
//    }
//    return result;
//}

std::vector<long double> add_subtractv(std::vector<long double> a, std::vector<long double> b, bool plus_or_minus) {//True = +, False = -
    if (a.size() != b.size()) {
        throw std::invalid_argument("Two Vectors Dimesion is different");
    }
    if (!plus_or_minus) {
        std::vector<long double> result(a.size());
        for (unsigned long long int i = 0; i < a.size(); i++) {
            result[i] = a[i] - b[i];
        }
        return result;
    }
    else {
        std::vector<long double> result(b.size());
        for (unsigned long long int i = 0; i < a.size(); i++) {
            result[i] = a[i] + b[i];
        }
        return result;
    }
}

std::vector<std::vector<long double>> add_substractmv(MATRIX_LF a, MATRIX_LF b, bool plus_or_minus) { // As Same as Vector add sub
    if (a.size() != b.size()) {
        throw std::invalid_argument("Two Vectors Dimesion is different");
    }
    if (a[0].size() != b[0].size()) {
        throw std::invalid_argument("Two Vectorsn Dimension is different");
    }
    MATRIX_LF result(a.size());
    if (plus_or_minus) {
        for (unsigned long long int i = 0;i<a.size();i++) {
            for (unsigned long long int j = 0;j<a[0].size();j++) {
                result[i][j] = a[i][j] + b[i][j];
            }
        }
    }
    else {
        for (unsigned long long int i = 0;i<a.size();i++) {
            for (unsigned long long int j=0;j<a[0].size();j++) {
                result[i][j] = a[i][j] - b[i][j];
            }
        }
    }
    return result;
}

long double distance_line(VECTOR_LF a, VECTOR_LF b) {
    return vector_size(add_subtractv(a, b, false));
}


MATRIX_LF transpos(MATRIX_LF matrix) {
    MATRIX_LF result;
    for (unsigned long long int i=0;i<matrix.size();i++) {
        for (unsigned long long int j = 0;j<matrix[0].size();j++) {
            result[i][j] = matrix[j][i];
        }
    }
    return result;
}

long double det_2by2(MATRIX_LF matrix) {
    if (matrix[0].size() != 2) {
        throw std::invalid_argument("Matrix must be 2x2");
    }
    if (matrix.size() != 2) {
        throw std::invalid_argument("Matrix must be 2x2");
    }
}

MATRIX_LF Minor_matrix(MATRIX_LF matrix, unsigned long long int i, unsigned long long int j) {
    MATRIX_LF result(matrix.size() - 1, std::vector<long double>(matrix[0].size() - 1));
    for (unsigned long long int i_ = 0;i_<matrix[0].size();i_++) {
        for (unsigned long long int j_=0;j_<matrix.size();j_++) {
            if (i_ == i || j_ == j)
                continue;
            else {
                unsigned long long int trash_i = i_;
                unsigned long long int trash_j = j_;
                if (i_ >= i) {
                    i_ = i_ - 1;
                }
                if (j_ >= j) {
                    j_ = j_ - 1;
                }
                result[trash_i][trash_j] = matrix[i_][j_];
            }
        }
    }
}

long double det_laplace(MATRIX_LF matrix) {
    unsigned long long int j = 0;
    long double result = 0;
    if (matrix[0].size() == 2 && matrix.size() == 2) {
        return det_2by2(matrix);
    }

    for (unsigned long long int i_=0;i_<matrix.size();i_++) {
        result += pow(-1, i_ + j) * matrix[i_][j] * det_laplace(Minor_matrix(matrix, i_, j));

    }
    return result;
}


MATRIX_LF confactor_matrix(MATRIX_LF matrix) {
    MATRIX_LF result;
    for (unsigned long long int i=0;i<matrix.size();i++) {
        for (unsigned long long int j = 0;j<matrix[0].size();j++) {
            result[i][j] = pow(-1, i + j) * det_laplace(Minor_matrix(matrix, i, j));
        }
    }
    return result;

}

long double vector_dot_product_with_Matrix(VECTOR_LF a, VECTOR_LF b) {
    if (a.size() != b.size()) {
        throw std::invalid_argument("Vectors must have the same size");
    }
    MATRIX_LF a_matrix;
    MATRIX_LF b_matrix;
    a_matrix[0] = a;
    b_matrix[0] = b;
    return matrix_timesv(transpos(b_matrix), a_matrix)[0][0];
}


MATRIX_LF inverse_matrix(MATRIX_LF matrix) {
    if (matrix.size() == 2 && matrix[0].size() == 2) {
        MATRIX_LF result;
        result[0][0] = matrix[1][1];
        result[0][1] = (-1) * matrix[0][1];
        result[1][0] = (-1) * matrix[1][0];
        result[1][1] = matrix[0][0];
        return matrix_scalar_multiply(result, matrix[0][0]*matrix[1][1] - matrix[1][0] * matrix[0][1]);
    }
    else {
        long double det_matrix = det_laplace(matrix);
        MATRIX_LF M_T = transpos(matrix);
        //    MATRIX_LF adjugate_matrix = cofactor_matrix(M_T);
        //    MATRIX_LF inverse = scalar_multiply(adjugate_matrix, 1 / det_matrix);
        //    return inverse;
        MATRIX_LF adjugate_matrix = confactor_matrix(M_T);
        MATRIX_LF inverse = matrix_scalar_multiply(adjugate_matrix, 1 / det_matrix);
        return inverse;
    }
}
