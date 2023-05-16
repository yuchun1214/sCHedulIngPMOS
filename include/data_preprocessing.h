#ifndef __DATA_PREPROCESSING_H__
#define __DATA_PREPROCESSING_H__

#include <vector>
#include "include/lot_base.h"

class data_preprocessing_t{
public:
    virtual std::vector<lot_base_t *>  createLots() = 0;
};

class data_preprocessing_from_sources_t{
public:

    virtual std::vector<lot_base_t *>  createLots();
};


#endif