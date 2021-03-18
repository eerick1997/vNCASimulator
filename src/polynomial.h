#include <iostream>
#include <map>
#include <unordered_map>
#include <utility>
#include <vector>

#define VON_NEUMANN true
#define MOORE false
#define VON_NEUMANN_NEIGHBOR 5
#define MOORE_NEIGHBOR 9
#define EPS 1e-6
#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

class polynomial {
private:
    // Attributes
    std::vector<int64_t> factorial;
    std::vector<int64_t> producto;
    std::map<std::pair<int32_t, int32_t>, int64_t> term;
    std::map<std::pair<int32_t, int32_t>, int64_t> derivat;
    std::string super_index[10] = {"⁰", "¹", "²", "³", "⁴",
                                   "⁵", "⁶", "⁷", "⁸", "⁹"};
    int8_t S_min, S_max, B_min, B_max, n;

public:
    polynomial(int8_t, int8_t, int8_t, int8_t, bool);
    void build_factorial(int64_t);
    int64_t get_binomial(int64_t, int64_t);
    void build_polynomial();
    void build_polynomial(std::vector<int8_t>);
    void set_s_min(int8_t);
    void set_s_max(int8_t);
    void set_b_min(int8_t);
    void set_b_max(int8_t);
    void set_n(int8_t);
    void derivate();
    double evaluate_derivate(double);
    double evaluate(double x);
    std::string get_text();
    std::string get_text_derivate();
    ~polynomial();
};

#endif // POLYNOMIAL_H
