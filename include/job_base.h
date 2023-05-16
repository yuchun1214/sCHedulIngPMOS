#ifndef __JOB_BASE_H__
#define __JOB_BASE_H__

#include <exception>
#include <string>
#include <utility>
#include <vector>
#include "include/forward_declaration.h"
#include "include/list.h"

class job_base_t : public list_node_t<double>
{
protected:
    double const *_ms_gene;
    double const *_os_gene;

    double _partition;

    double _arrival_time, _start_time, _end_time;
    double _processing_time;

    machine_base_t *_machine;

    std::vector<std::pair<machine_base_t *, double> >
        _available_machines_and_proessing_time;

public:
    job_base_t();
    job_base_t(double arrival_time);
    virtual ~job_base_t();

    virtual double getData() { return *_os_gene; }

    virtual inline void setMachine(machine_base_t *machine)
    {
        _machine = machine;
    }

    virtual inline void addAvailableMachine(machine_base_t *machine,
                                            double process_time)
    {
        _available_machines_and_proessing_time.push_back(
            std::pair<machine_base_t *, double>(machine, process_time));
        _partition = 1.0 / _available_machines_and_proessing_time.size();
    }

    virtual inline void setMsGene(double const *ms_gene) { _ms_gene = ms_gene; }

    virtual inline void setOsGene(double const *os_gene) { _os_gene = os_gene; }

    virtual inline void setStartTime(double start_time)
    {
        _start_time = start_time;
        _end_time = _start_time + _processing_time;
    }

    virtual inline double getArrivalTime() { return _arrival_time; }

    virtual inline double getStartTime() { return _start_time; }

    virtual inline double getEndTime() { return _end_time; }

    virtual inline double getProcessingTime() { return _processing_time; }

    virtual machine_base_t *machineSelection();
};


#endif