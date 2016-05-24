#ifndef BaseModel_hpp
#define BaseModel_hpp

#include <map>
#include <set>
#include <vector>
#include <iostream>

#include "../sqlite/SQLiteCpp.h"

/**
 * SQlite mapper
 * Adrien Poupa & Timothée Barbot
 * December 2015
 */
class BaseModel {
private:
    BaseModel(){}

public:
    static std::map<std::string, std::string> getById(const std::string& table, const int& id);
    static int getCount(const std::string& table, std::string filter = "");
    static std::map<int, std::map<std::string, std::string>> select(const std::string& table, const std::string& fields = "*", const std::string& where = "");
    static int save(const std::string& table, std::map<std::string, std::vector<std::string>> data);
    static bool remove(const std::string& table, const int& id);

};

#endif
