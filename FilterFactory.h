#ifndef CPP_HSE_FILTERFACTORY_H
#define CPP_HSE_FILTERFACTORY_H

#include "CropFilter.h"
#include "Filter.h"

#include <map>
#include <stdexcept>
#include <string>
#include <memory>

class FilterFactory {
public:
    FilterFactory();

    std::shared_ptr<Filter> GetFilter(const std::string& filter_name);

protected:
    template <class T>
    void AddFilter(std::string filter_name, T& filter);

protected:
    std::map<std::string, std::shared_ptr<Filter> > filters_prods_;
};

#endif  // CPP_HSE_FILTERFACTORY_H
