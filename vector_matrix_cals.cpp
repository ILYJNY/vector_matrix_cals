#include "vector"
#include "cmath"
#include "complex"
#define MATRIX_LF std::vector<std::vector<long double>>
#define VECTOR_LF std::vector<long double>
#define MATRIX_CLF std::vector<std::vector<std::complex<long double>>>
#define VECTOR_CLF std::vector<std::complex<long double>>

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