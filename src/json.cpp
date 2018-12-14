#include "json.hpp"


std::string json_value(const std::string& key, const std::string& value)
{
    return "\"" + key + "\": \"" + value + "\"";
}

std::string json_value(const std::string& key, int value)
{
    return "\"" + key + "\": " + std::to_string(value);
}

std::string json_value(const std::string& key, double value)
{
    return "\"" + key + "\": " + std::to_string(value);
}

std::string json_value_f(const std::vector<std::string>& value, std::string sep)
{
    std::string ret = "[";

    for (size_t i = 0 ; i < value.size() ; i++) {
        ret += value[i];

        if (i + 1 < value.size())
            ret += sep;
    }

    return ret + "]";
}

std::string json_value_f(const std::string& key, const std::vector<std::string>& value, std::string sep)
{
    return  "\"" + key + "\": " + json_value_f(value, sep);
}

std::string json_value(const Sequence& value)
{
    std::vector<std::string> value_f(value.size());

    for (size_t i = 0 ; i < value.size() ; i++)
        value_f[i] = std::to_string(value[i]);

    return json_value_f(value_f);
}

std::string json_value(const std::string& key, const Sequence& value)
{
    std::vector<std::string> value_f(value.size());

    for (size_t i = 0 ; i < value.size() ; i++)
        value_f[i] = std::to_string(value[i]);

    return json_value_f(key, value_f);
}

std::string json_value(const std::string& key, const std::vector<Sequence>& value)
{
    std::vector<std::string> value_f(value.size());

    for (size_t i = 0 ; i < value.size() ; i++)
        value_f[i] = "\t\t" + json_value(value[i]);

    value_f.front() = "\n" + value_f.front();
    value_f.back() += "\n\t";

    return json_value_f(key, value_f, ",\n");
}

std::string json_value(const std::string& key, const std::map<std::string, double> &value)
{
    std::string value_f = "{";

    for (const auto &kv: value) {
        value_f += json_value(kv.first, kv.second) + ", ";
    }

    value_f = value_f.substr(0, value_f.size() - 2) + "}";
    return "\"" + key + "\": " + value_f;
}
