#ifndef CPP_HSE_CMDLINEPARSER_H
#define CPP_HSE_CMDLINEPARSER_H

#include <stdexcept>
#include <string>
#include <vector>

struct FilterSetting {
public:
    FilterSetting(std::string filter_name) : filter_name_(filter_name) {
    }

public:
    const std::string& GetFilterName() const {
        return filter_name_;
    }

    const std::vector<std::string>& GetParameters() const {
        return parameters_;
    }

    void AddParameter(const std::string& parameter) {
        parameters_.push_back(parameter);
    }

protected:
    std::string filter_name_;
    std::vector<std::string> parameters_;
};

class CmdLineParser {
public:
    CmdLineParser() = default;

    explicit CmdLineParser(int argc, char** argv);

public:
    const std::string& GetInputFile() const {
        return input_file_;
    }

    const std::string& GetOutputFile() const {
        return output_file_;
    }

    const std::vector<FilterSetting>& GetFilters() const {
        return filters_;
    }

protected:
    std::string input_file_;
    std::string output_file_;
    std::vector<FilterSetting> filters_;
};

#endif  // CPP_HSE_CMDLINEPARSER_H
