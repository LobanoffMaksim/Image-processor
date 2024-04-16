#ifndef CPP_HSE_CONTROLLER_H
#define CPP_HSE_CONTROLLER_H

#include "BMPImage.h"
#include "CmdLineParser.h"
#include "FilterFactory.h"

#include <utility>
#include <vector>
#include <memory>

class Controller {
public:
    Controller() = default;

    explicit Controller(CmdLineParser input);

public:
    void ApplyFilters(BMPImage& image);

private:
    FilterFactory filter_factory_;
    std::vector<std::pair<std::shared_ptr<Filter>, FilterSetting> > pipeline_;
};

#endif  // CPP_HSE_CONTROLLER_H
