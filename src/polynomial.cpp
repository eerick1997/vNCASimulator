#include "polynomial.h"
#include <QDebug>
#include <iostream>
#include <math.h>

polynomial::polynomial(int8_t S_min, int8_t S_max, int8_t B_min, int8_t B_max,
                       bool neighbor)
    : S_min(S_min), S_max(S_max), B_min(B_min), B_max(B_max),
      n(neighbor == MOORE ? MOORE_NEIGHBOR : VON_NEUMANN_NEIGHBOR) {
  build_factorial(10);
}

void polynomial::build_factorial(int64_t limit) {
  factorial.resize(limit + 1);
  factorial[0] = 1;
  for (int32_t n = 1; n <= limit; n++)
    factorial[n] = n * factorial[n - 1];
}

int64_t polynomial::get_binomial(int64_t m, int64_t k) {
  return ((m < 0) or (k < 0))
             ? 0
             : (factorial[m] / (factorial[k] * factorial[m - k]));
}

void polynomial::build_polynomial() {
  int64_t coefficient = 0;
  term.clear();
  int32_t exp_p = 0, exp_q = 0;
  for (int32_t v = S_min; v <= S_max; v++) {
    exp_p = v + 1, exp_q = n - v - 1;
    coefficient = get_binomial(n - 1, v);
    term[{exp_p, exp_q}] += coefficient;
  }
  for (int32_t v = B_min; v <= B_max; v++) {
    exp_p = v, exp_q = n - v;
    coefficient = get_binomial(n - 1, v);
    term[{exp_p, exp_q}] += coefficient;
  }
  derivate();
}

void polynomial::build_polynomial(std::vector<int8_t> bitmask) {
  int32_t v, exp_p, exp_q;
  term.clear();
  for (int i = 0; i < 32; i++) {
    v = __builtin_popcount(i);
    exp_p = v, exp_q = n - v;
    term[{exp_p, exp_q}] += bitmask[i];
  }
  derivate();
}

double polynomial::evaluate(double x) {
  double ans = 0;
  // C * p^n * q^m
  for (auto element : term)
    ans += element.second * pow(x, element.first.first) *
           pow(1 - x, element.first.second);
  return ans;
}

std::string polynomial::get_text() {
  std::string ans = "";
  int32_t index = 0;
  int64_t C = 0;
  int32_t n = 0, m = 0;
  for (auto element : term) {
      C = element.second;
      m = element.first.first, n = element.first.second;
      if(C != 0) {
          if(C != 1)
              ans += std::to_string(element.second);
          if(m != 0)
              ans += "p" + (m > 1 ? super_index[m] : "");
          if(n != 0)
              ans += "q" + (n > 1 ? super_index[n] : "") + " + ";
      }
      index++;
  }

  if (ans.size() > 2 and ans[ans.size() - 2] == '+')
      ans[ans.size() - 2] = ' ';

  return "f(p) = " + ans;
}

std::string polynomial::get_text_derivate() {
  std::string ans = "";
  int32_t index = 0;
  int64_t C = 0;
  int32_t n = 0, m = 0;

  for (auto element : derivat) {
      C = element.second;
      m = element.first.first, n = element.first.second;
      if(C != 0) {
          if(C != 1)
              ans += std::to_string(element.second);
          if(m != 0)
              ans += "p" + (m > 1 ? super_index[m] : "");
          if(n != 0)
              ans += "q" + (n > 1 ? super_index[n] : "") + " + ";
      }
      index++;
  }
  if (ans.size() > 2 and ans[ans.size() - 2] == '+')
      ans[ans.size() - 2] = ' ';
  return "f'(p) = " + ans;
}

void polynomial::derivate() {
  int64_t C = 0;
  int32_t n = 0, m = 0;
  derivat.clear();
  for (auto element : term) {
    C = element.second;
    m = element.first.first, n = element.first.second;

    //p, q > 0
    //p > 0, q == 0
    //p == 0, q > 0
    //p + q => 1 - 1, {{0, 0}, 0}

    //C(p^m * q^n) = C (m * p^{m - 1} * q^{n}) +
    if(m > 0)
        derivat[{m - 1, n}] += m * C;
    //C(p^m * q^n) = C (-n * p^{m} * q^{n - 1})
    if(n > 0)
        derivat[{m, n - 1}] -= n * C;
  }
  qDebug() << QString::fromUtf8(get_text().c_str());
  qDebug() << QString::fromUtf8(get_text_derivate().c_str());
}

//f(p) = p^{1} => 1 * p^{1 - 1} = 1 * p^{0} =>
//f'(p) = 1

double polynomial::evaluate_derivate(double p) {
  double ans = 0;
  int64_t C = 0;
  int32_t n = 0, m = 0;
  double q = 1 - p;
  for (auto element : derivat) {
    C = element.second;
    m = element.first.first, n = element.first.second;

    ans += C * (m == 0 ? 1 : pow(p, m)) * (n == 0 ? 1 : pow(q, n));
    qDebug() << "m = " << m << " n = " << n << " ans = " << (C * (m == 0 ? 1 : pow(p, m)) * (n == 0 ? 1 : pow(q, n)));
  }
  qDebug() << "(" << p << "," << ans << ")";
  return ans;
}

void polynomial::set_s_min(int8_t n_S_min) { S_min = n_S_min; }

void polynomial::set_s_max(int8_t n_S_max) { S_max = n_S_max; }

void polynomial::set_b_min(int8_t n_B_min) { B_min = n_B_min; }

void polynomial::set_b_max(int8_t n_B_max) { B_max = n_B_max; }

void polynomial::set_n(int8_t n_n) { n = n_n; }

polynomial::~polynomial() {
  factorial.clear();
  producto.clear();
  term.clear();
}
