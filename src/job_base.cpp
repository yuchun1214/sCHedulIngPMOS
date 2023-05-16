#include "include/job_base.h"


job_base_t::job_base_t()
{
    // initialization for job_base_t object
    _ms_gene = nullptr;
    _os_gene = nullptr;
    _partition = 0;
    _start_time = 0;
    _end_time = 0;
    _arrival_time = 0;
    _machine = nullptr;
}

job_base_t::~job_base_t() {}

machine_base_t *job_base_t::machineSelection()
{
    if (_ms_gene == nullptr) {
        throw std::runtime_error("ms_gene is not initialized");
    }
    double ms_gene_val = *_ms_gene;

    if (ms_gene_val < 0 || ms_gene_val >= 1) {
        throw std::runtime_error("ms_gene value is out of range");
    }

    int index = ms_gene_val / _partition;
    std::pair<machine_base_t *, double> _machine_and_processing_time =
        _available_machines_and_proessing_time[index];
    _machine = _machine_and_processing_time.first;
    _processing_time = _machine_and_processing_time.second;

    return _machine;
}