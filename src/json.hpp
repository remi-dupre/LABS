#pragma once

#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "labs.hpp"


void serialize_json(std::ostream& stream, const std::string& key, const std::string& value);
void serialize_json(std::ostream& stream, const std::string& key, int value);
void serialize_json(std::ostream& stream, const std::string& key, double value);

void serialize_json_f(std::ostream& stream, const std::vector<std::string>& value, std::string sep=", ");
void serialize_json_f(std::ostream& stream, const std::string& key, const std::vector<std::string>& value, std::string sep=", ");

void serialize_json(std::ostream& stream, const Sequence& value);
void serialize_json(std::ostream& stream, const std::string& key, const Sequence& value);
void serialize_json(std::ostream& stream, const std::string& key, const std::vector<Sequence>& value);

void serialize_json(std::ostream& stream, const std::string& key, const std::map<std::string, double> &value);
void serialize_json(std::ostream& stream, const std::string& key, const std::vector<std::map<std::string, double>> &value, const std::string& line_prefix = "");
