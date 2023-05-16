#include "include/chromosome_base.h"

chromosome_base_t::chromosome_base_t()
{
    _genes = nullptr;
    _size = 0;
    _fitness = 0;
}

chromosome_base_t::chromosome_base_t(int size)
{
    _genes = new double[size];
    _size = size;
    _fitness = 0;
}

chromosome_base_t::~chromosome_base_t()
{
    delete[] _genes;
}