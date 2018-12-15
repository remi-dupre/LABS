#include "json.hpp"


void serialize_json(std::ostream& stream, const std::string& key, const std::string& value)
{
    stream << "\"" << key << "\": \"" << value << "\"";
}

void serialize_json(std::ostream& stream, const std::string& key, int value)
{
    stream << "\"" << key << "\": " << value;
}

void serialize_json(std::ostream& stream, const std::string& key, double value)
{
    stream << "\"" << key << "\": " << value;
}

void serialize_json_f(std::ostream& stream, const std::vector<std::string>& value, std::string sep)
{
    stream << "[";

    for (size_t i = 0 ; i < value.size() ; i++) {
        stream << value[i];

        if (i + 1 < value.size())
            stream << sep;
    }

    stream << "]";
}

void serialize_json_f(std::ostream& stream, const std::string& key, const std::vector<std::string>& value, std::string sep)
{
    stream << "\"" << key << "\": ";
    serialize_json_f(stream, value, sep);
}

void serialize_json(std::ostream& stream, const Sequence& value)
{
    std::vector<std::string> value_f(value.size());

    for (size_t i = 0 ; i < value.size() ; i++)
        value_f[i] = std::to_string(value[i]);

    serialize_json_f(stream, value_f);
}

void serialize_json(std::ostream& stream, const std::string& key, const Sequence& value)
{
    std::vector<std::string> value_f(value.size());

    for (size_t i = 0 ; i < value.size() ; i++)
        value_f[i] = std::to_string(value[i]);

    return serialize_json_f(stream, key, value_f);
}

void serialize_json(std::ostream& stream, const std::string& key, const std::vector<Sequence>& value)
{
    std::vector<std::stringstream> value_fs(value.size());
    value_fs.front() << "\n";

    for (size_t i = 0 ; i < value.size() ; i++) {
        value_fs[i] << "\t\t";
        serialize_json(value_fs[i], value[i]);
    }

    value_fs.back() << "\n\t";
    std::vector<std::string> value_f(value.size());

    for (size_t i = 0 ; i < value.size() ; i++)
        value_f[i] = value_fs[i].str();

    return serialize_json_f(stream, key, value_f, ",\n");
}

void serialize_json(std::ostream& stream, const std::string& key, const std::map<std::string, double> &value)
{
    stream << "{" << "\"" << key << "\": ";

    bool first = true;
    for (const auto &kv: value) {
        if (!first)
            stream << ", ";
        else
            first = false;

        serialize_json(stream, kv.first, kv.second);
    }

    stream << "}";
}
