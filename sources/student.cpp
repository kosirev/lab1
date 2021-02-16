// Copyright 2021 kosirev <qw01w@yandex.ru>

#include <student.hpp>
#include <iomanip>
#include <nlohmann/json.hpp>
#include <vector>
#include <istream>
#include <fstream>

void push_student(const json &j, std::vector<student_t> &studentsInfo) {
  for (const auto & i : j) {
    student_t student;
    student.name = get_name(i.at("name"));
    student.Group = get_Group(i.at("group"));
    student.Avg = get_Avg(i.at("avg"));
    student.Debt = get_Debt(i.at("debt"));
    studentsInfo.push_back(student);
  }
}

vector<student_t> Brain(const string& way)
{
  std::fstream file;
  file.open(way, std::ios::in);
  if (!file.is_open()) {
    throw std::runtime_error(way + " unable to open json");
  }

  json data;
  file >> data;
  file.close();

  if (!data.at("items").is_array()) {
    throw std::runtime_error("Items most be array type");
  }

  if (data.at("items").size() != data.at("_meta").at("count")) {
    throw std::runtime_error("meta_: error with count");
  }
  std::vector<student_t> studentsInfo;
  push_student(data.at("items"), studentsInfo);
  return studentsInfo;
}

auto get_name(const json& jSubject) -> string {
  return jSubject.get<string>();
}

auto get_Debt(const json& jSubject) -> any {
  using std::vector;
  if (jSubject.is_null())
    return nullptr;
  else if (jSubject.is_string())
    return jSubject.get<string>();
  else
    return jSubject.get<vector<string>>();
}

auto get_Avg(const json& jSubject) -> any {
  using std::size_t;
  if (jSubject.is_null())
    return nullptr;
  else if (jSubject.is_string())
    return jSubject.get<string>();
  else if (jSubject.is_number_float())
    return jSubject.get<double>();
  else
    return jSubject.get<size_t>();
}

auto get_Group(const json& jSubject) -> any {
  using std::size_t;
  if (jSubject.is_string())
    return jSubject.get<string>();
  else
    return jSubject.get<size_t>();
}

void PrintName(const student_t& student, ostream& os) {
  using std::setw;
  os << "| " << std::setw(SpaceSize) << student.name << "|";
}

void PrintGroup(const student_t& student, ostream& os) {
  using std::setw;
  using std::any_cast;
  using std::nullptr_t;

  if (student.Group.type() == typeid(nullptr_t)) {
    os  <<  setw(SpaceSize) << "null" << "|";
  } else if (student.Group.type() == typeid(string)) {
    os  << setw(SpaceSize) << any_cast<string>(student.Group) << "|";
  } else {
    os << setw(SpaceSize) << any_cast<size_t>(student.Group) << "|";
  }
}


void PrintAVG(const student_t& student, ostream& os) {
  using std::setw;
  using std::any_cast;
  using std::nullptr_t;

  if (student.Avg.type() == typeid(nullptr_t)) {
    os <<  setw(SpaceSize) << "null" << "|";
  } else if (student.Avg.type() == typeid(string)) {
    os <<  setw(SpaceSize) << any_cast<string>(student.Avg) << "|";
  } else if (student.Avg.type() == typeid(double)) {
    os <<  setw(SpaceSize) << any_cast<double>(student.Avg) << "|";
  } else {
    os <<  setw(SpaceSize) << any_cast<size_t>(student.Avg) << "|";
  }
}

void PrintDebt(const student_t& student, ostream& os) {
  using std::setw;
  using std::vector;
  using std::any_cast;
  using std::nullptr_t;

  if (student.Debt.type() == typeid(nullptr_t)) {
    os << setw(SpaceSize) << "null" << "|";
  } else if (student.Debt.type() == typeid(string)) {
    os << setw(SpaceSize) << any_cast<string>(student.Debt) << "|";
  } else {
    os << setw(SpaceSize - 6)
       << any_cast<vector<string>>(student.Debt).size()
       << " items" << "|";
  }
}

void PrintHeaders(ostream& os)
{
  using std::endl;
  using std::setw;

  string Values[4] = {"Name", "Group", "AVG", "Debt"};
  for (int i = 0, j = 0; i < 4; i++, j++)
  {
    if (i == 0)
      os << "|" << " ";
    os << setw(SpaceSize) << Values[i] << "|";
  }
  os << endl;

  for ( int i = 0; i < TableWidth; i++ ){
    os << "_";
  }
  os << endl;
}


void print(const vector<student_t>& students, ostream& os) {
  using std::endl;

  PrintHeaders(os);

  for (auto const &student : students) {
    PrintName(student, os);
    PrintGroup(student, os);
    PrintAVG(student, os);
    PrintDebt(student, os);
    os << endl;
    for (int i = 0; i < TableWidth; i++){
      os << "_";
    }
    os << endl;
  }
}