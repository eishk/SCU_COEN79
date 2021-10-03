#include "poly.h"
#include <fstream>
#include <cassert>
#include <iostream>
#include <climits>
#include <cmath>
using namespace std;

namespace coen79_lab4 {

	// Constructor	
	polynomial::polynomial(double c, unsigned int exponent) {
		assert(exponent <= MAXIMUM_DEGREE);
		int i;
		for (i = 0; i < MAXIMUM_DEGREE; i++) {
			data[i] = 0.0;
		}
		data[exponent] = c;
        current_degree = exponent;
	}

	// Assigns given coefficient to the given exponent
	void polynomial::assign_coef(const double coefficient, unsigned int exponent) {
		assert(exponent <= MAXIMUM_DEGREE);
		data[exponent] = coefficient;
        update_current_degree();
	}

	// Adds given coefficient to the given exponent
	void polynomial::add_to_coef(const double coefficient, unsigned int exponent) {
		assert(exponent <= MAXIMUM_DEGREE);
		data[exponent] += coefficient;
        update_current_degree();
	}

	// Clears the polynomial
	void polynomial::clear() {
        for (int i = 0; i<=MAXIMUM_DEGREE; i++) {
            data[i]=0.0;
        }
        update_current_degree();
	}

	// Returns the degree of the polynomial
	unsigned int polynomial::degree() const {
        return current_degree;
	}

	// Returns antiderivative of polynomial as polynomial object
	polynomial polynomial::antiderivative() const {
		assert(degree() <= MAXIMUM_DEGREE);
        polynomial anti;
        // loops through and computes antiderivative for each term in array
        for (int i = degree() + 1; i > 0; i--) {
            anti.data[i] = data[i-1]/(i);
        }
        anti.data[0] = 0.0;
        anti.update_current_degree();
        return anti;
	}

	// Returns the coefficient associated with the given exponent
	double polynomial::coefficient(unsigned int exponent) const {
		if (exponent > MAXIMUM_DEGREE) {
			return 0;
		}
		else {
			return data[exponent];
		}
	}
	
	// Returns the definite integral of the polynomial with given bounds
	double polynomial::definite_integral(double x0, double x1) const {
        double sum = 0.0;
        polynomial definite = antiderivative();
        sum = definite.eval(x1)-definite.eval(x0);
        return sum;
	}

	// Returns the derivative of the given polynomial as a polynomial object
	polynomial polynomial::derivative() const {
		polynomial p;
		int i;
		for (i = 0; i <= degree(); i++) {
			p.data[i] = (data[i+1]*(i+1));
		}
        p.update_current_degree();
		return p;
	}

	// Evaluates the polynomial with the given x
	double polynomial::eval(double x) const {
		int i;
		double answer = 0.0;
		for (i = degree(); i >= 0; i--) {
            answer += coefficient(i) * (pow(x, i));
		}
		return answer;
	}

	// Returns if polynomial is a zero polynomial 
	bool polynomial::is_zero() const {
		int i;
		for (i = 0; i < MAXIMUM_DEGREE;i++) {
			if (data[i] != 0) {
				return false;
			}
		}
		return true;
	}

	// Returns the value of the next exponent which is larger than e
	unsigned int polynomial::next_term(unsigned int e) const {
		int i;
		for (i = e; i < MAXIMUM_DEGREE; i++) {
			if (data[i] != 0) {
				return i;
			}
		}
		return 0;
	}

	// Returns the value of the next exponent which is smaller than e
	unsigned int polynomial::previous_term(unsigned int e) const {
		int i;
		for (i = e; i > 0; i--) {
			if (data[i] != 0) {
				return i;
			}
		}
		return 0;
	}

	// Same as eval
	double polynomial::operator()(double x) const {
		return eval(x);
	}

    void polynomial::update_current_degree() {
        current_degree = 0;
        for (int i = 0; i < MAXIMUM_DEGREE; i++) {
            if (data[i] != 0) {
                current_degree = i;
            }
        }
    }

	// + operator
	polynomial operator+(const polynomial& p1, const polynomial& p2) {
        polynomial plus;
		int i;
		for (i = 0; i < polynomial::MAXIMUM_DEGREE; i++) {
            plus.data[i] = p1.data[i] + p2.data[i];
		}
		return plus;
	}

	// - operator
	polynomial operator-(const polynomial& p1, const polynomial& p2) {
		polynomial sub;
		int i;
		for (i = 0; i < polynomial::MAXIMUM_DEGREE; i++) {
            sub.data[i] = p1.data[i] - p2.data[i];
		}
		return sub;
	}

	// * operator
	polynomial operator*(const polynomial& p1, const polynomial& p2) {
		assert(p1.degree()+p2.degree() <
               polynomial::MAXIMUM_DEGREE);
		polynomial p;
		int i, j;
		for (i = 0; i <= p1.degree(); i++) {
			for (j = 0; j <= p2.degree(); j++) {
                p.add_to_coef(p1.coefficient(i) * p2.coefficient(j), i+j);
			}
		}
		return p;
	}

	// ostream operator
	std::ostream& operator <<(ostream& out, const polynomial& p) {
        for (int i = p.degree(); i >= 0; --i) {
                    // first term does not need the + or -
            if (i == p.degree()) {
                if (i == 0) {
                    if (p.coefficient(i) > 0) {
                        out << p.coefficient(i) << " ";
                    } else if (p.coefficient(i) == 0){
                        out << "";
                    } else {
                        out << p.coefficient(i) << " ";
                    }
                    continue;
                }
                if (i == 1) {
                    if (p.coefficient(i) > 0) {
                        out << p.coefficient(i) << "x" << " ";
                    } else if (p.coefficient(i) == 0){
                        out << "";
                    } else {
                        out << p.coefficient(i) << "x" << " ";
                    }
                        continue;
                }
                if (p.coefficient(i) > 0) {
                    out << p.coefficient(i) << "x^" << i << " ";
                } else if (p.coefficient(i) == 0){
                    out << "";
                } else {
                    out << p.coefficient(i) << "x^" << i << " ";
                }
                continue;
            }
            if (i == 0) {
                if (p.coefficient(i) > 0) {
                    out << "+ " << p.coefficient(i) << " ";
                } else if (p.coefficient(i) == 0){
                    out << "";
                } else {
                    out << "- " << p.coefficient(i) << " ";
                }
                continue;
            }
            if (i == 1) {
                if (p.coefficient(i) > 0) {
                    out << "+ " << p.coefficient(i) << "x" << " ";
                } else if (p.coefficient(i) == 0){
                    out << "";
                } else {
                    out << "- " << p.coefficient(i) << "x" << " ";
                }
                continue;
            }
            if (p.coefficient(i) > 0) {
                out << "+ " << p.coefficient(i) << "x^" << i << " ";
            } else if (p.coefficient(i) == 0){
                out<< "";
            } else {
                out<< "- " <<p.coefficient(i) << "x^" << i << " ";
            }
        }
        return out;
    }

} 
