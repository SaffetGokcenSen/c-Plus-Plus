#ifndef GUARD_GRADE_ANALYSIS
#define GUARD_GRADE_ANALYSIS

#include <vector>
#include <string>
#include <iostream>

struct Student_info {
    std::string name;
    double midterm, final;
    std::vector<double> homework;
};

std::istream& read_hw(std::istream&, std::vector<double>&);

std::istream& read(std::istream&, Student_info&);

double grade(double, double, double);

double median(std::vector<double>);

double grade(double, double, const std::vector<double>&);

double grade(const Student_info&);

double grade_aux(const Student_info&);

double average(const std::vector<double>&);

double average_grade(const Student_info&);

double optimistic_median(const Student_info&);

template <class T, class X>
double grade_analysis(const std::vector<T>& v, X x);

#include "grade_analysis.hpp"

#endif