#pragma once

#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "labs.hpp"


std::string json_value(const std::string& key, const std::string& value);
std::string json_value(const std::string& key, int value);
std::string json_value(const std::string& key, double value);

std::string json_value_f(const std::vector<std::string>& value, std::string sep=", ");
std::string json_value_f(const std::string& key, const std::vector<std::string>& value, std::string sep=", ");

std::string json_value(const Sequence& value);
std::string json_value(const std::string& key, const Sequence& value);
std::string json_value(const std::string& key, const std::vector<Sequence>& value);

std::string json_value(const std::string& key, const std::map<std::string, double> &value);
