#include "BlurFilter.h"
#include "CropFilter.h"
#include "EdgeFilter.h"
#include "FilterFactory.h"
#include "FolderFilter.h"
#include "GrayscaleFilter.h"
#include "NegFilter.h"
#include "SharpFilter.h"

FilterFactory::FilterFactory() {
    try {
        std::shared_ptr<Filter> crop_pointer = std::make_shared<CropFilter>();
        AddFilter("-crop", crop_pointer);

        std::shared_ptr<Filter> gs_pointer = std::make_shared<GrayscaleFilter>();
        AddFilter("-gs", gs_pointer);

        std::shared_ptr<Filter> neg_pointer = std::make_shared<NegFilter>();
        AddFilter("-neg", neg_pointer);

        std::shared_ptr<Filter> sharp_pointer = std::make_shared<SharpFilter>();
        AddFilter("-sharp", sharp_pointer);

        std::shared_ptr<Filter> edge_pointer = std::make_shared<EdgeFilter>();
        AddFilter("-edge", edge_pointer);

        std::shared_ptr<Filter> blur_pointer = std::make_shared<BlurFilter>();
        AddFilter("-blur", blur_pointer);

        std::shared_ptr<Filter> folder_pointer = std::make_shared<FolderFilter>();
        AddFilter("-folder", folder_pointer);
    } catch (std::logic_error& e) {
        throw e;
    }
}

std::shared_ptr<Filter> FilterFactory::GetFilter(const std::string& filter_name) {
    auto it = filters_prods_.find(filter_name);
    if (it == filters_prods_.end()) {
        throw std::invalid_argument("Filter not found.");
    }
    return it->second;
}

template <class T>
void FilterFactory::AddFilter(std::string filter_name, T& filter) {
    try {
        std::shared_ptr<Filter> base_filter = filter;
        filters_prods_[filter_name] = base_filter;
    } catch (...) {
        throw std::logic_error("Can't cast filter to Filter*");
    }
}
