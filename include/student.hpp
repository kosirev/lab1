// Copyright 2021 kosirev <qw01w@yandex.ru>

#ifndef INCLUDE_STUDENT_HPP_
#define INCLUDE_STUDENT_HPP_

#include <iostream>
#include <any>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

const int SpaceSize = 13;
const int TableWidth = 57;


using nlohmann::json;
using std::string;
using std::any;
using std::ostream;
using std::vector;
using std::cout;

struct student_t {
  std::string name;
  std::any Group;
  std::any Avg;
  std::any Debt;
};

auto get_name(const json&) -> string;
auto get_Debt(const json&)  -> any;
auto get_Avg(const json&) -> any;
auto get_Group(const json&) -> any;
void PrintName(const student_t&, ostream&);
void PrintDebt(const student_t&, ostream&);
void PrintGroup(const student_t&, ostream&);
void PrintAVG(const student_t&, ostream&);
void print(const vector<student_t>&, ostream&);
vector<student_t> Brain(const string& way);

#endif  // INCLUDE_STUDENT_HPP_