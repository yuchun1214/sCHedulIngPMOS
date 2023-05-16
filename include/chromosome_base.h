#ifndef __CHROMOSOME_H__
#define __CHROMOSOME_H__

class chromosome_base_t
{
protected:
    double *_genes;
    int _size;
    double _fitness;

public:
    chromosome_base_t();
    chromosome_base_t(int size);
    virtual ~chromosome_base_t();
};

#endif