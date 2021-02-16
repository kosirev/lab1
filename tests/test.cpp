// Copyright 2020 Your Name <your_email>

#include <gtest/gtest.h>

#include <iostream>
#include <vector>
#include <student.hpp>
#include <fstream>


TEST(PrintTable, PrintTable) {
  std::fstream file{"file.json", std::ios::out};
  const char* tabl = R"(|          Name|        Group|          AVG|         Debt|
_________________________________________________________
|   Ivanov Petr|            1|         4.25|         null|
_________________________________________________________
|  Sidorov Ivan|           31|            4|          C++|
_________________________________________________________
| Pertov Nikita|       IU8-31|         3.33|      3 items|
_________________________________________________________
)";
  std::string json_string = R"({
    "items": [
    {
      "name": "Ivanov Petr",
          "group": "1",
          "avg": "4.25",
          "debt": null
    },
    {
      "name": "Sidorov Ivan",
          "group": 31,
          "avg": 4,
          "debt": "C++"
    },
    {
      "name": "Pertov Nikita",
          "group": "IU8-31",
          "avg": 3.33,
          "debt": [
      "C++",
          "Linux",
          "Network"
      ]
    }
    ],
    "_meta": {
      "count": 3
    }
 })";

  file << json_string;
  file.close();
  std::stringstream ss;
  auto students = Brain("file.json");
  print(students, ss);
  EXPECT_EQ(tabl, ss.str());
}

TEST(Errors, NonExistingFile) {
  std::string exception_string;
  try {
    auto students = Brain("non/existing/file.json");
  } catch (std::runtime_error &e) {
    exception_string = e.what();
  }
  EXPECT_EQ(exception_string, "non/existing/file.json unable to open json");
}

TEST(Errors, ItemsIsNotArray) {
  std::fstream file{"file.json", std::ios::out};
  std::string exception_string;

  std::string json_string = R"({
    "items":
    {
      "name": "Ivanov Petr",
          "group": "1",
          "avg": "4.25",
          "debt": null
    },
    "_meta": {
      "count": 3
    }
 })";

  file << json_string;
  file.close();

  try {
    auto students = Brain("file.json");
  } catch (std::runtime_error &e) {
    exception_string = e.what();
  }
  EXPECT_EQ(exception_string, "Items most be array type");
}

TEST(Errors, IncorrectMeta) {
  std::fstream file{"file.json", std::ios::out};
  std::string exception_string;

  std::string json_string = R"({
    "items": [
    {
      "name": "Ivanov Petr",
          "group": "1",
          "avg": "4.25",
          "debt": null
    },
    {
      "name": "Sidorov Ivan",
          "group": 31,
          "avg": 4,
          "debt": "C++"
    },
    {
      "name": "Pertov Nikita",
          "group": "IU8-31",
          "avg": 3.33,
          "debt": [
      "C++",
          "Linux",
          "Network"
      ]
    }
    ],
    "_meta": {
      "count": 123
    }
 })";

  file << json_string;
  file.close();

  try {
    auto students = Brain("file.json");
  } catch (std::runtime_error &e) {
    exception_string = e.what();
  }
  EXPECT_EQ(exception_string, "meta_: error with count");
}
int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
