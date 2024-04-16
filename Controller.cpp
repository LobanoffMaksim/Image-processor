#include "Controller.h"

#include <stdexcept>

Controller::Controller(CmdLineParser input) {
    for (const FilterSetting& filter_setting : input.GetFilters()) {
        std::shared_ptr<Filter> filter = nullptr;
        try {
            filter = filter_factory_.GetFilter(filter_setting.GetFilterName());
        } catch (std::invalid_argument& e) {
            throw e;
        }
        pipeline_.push_back({filter, filter_setting});
    }
}

void Controller::ApplyFilters(BMPImage& image) {
    for (auto& [filter, filter_setting] : pipeline_) {
        try {
            filter->ApplyFilter(image, filter_setting);
        } catch (std::invalid_argument& e) {
            throw e;
        }
    }
}
