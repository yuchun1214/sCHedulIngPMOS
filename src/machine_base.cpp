#include "include/machine_base.h"
#include "include/job_base.h"
#include "include/list.h"

#include <iostream>

void machine_base_t::appendJob(job_base_t *job)
{
    job->setMachine(this);
    if (size_of_jobs > 0) {
        tail->setNext(job);
        tail = job;
    } else {
        tail = head = job;
    }

    ++size_of_jobs;
}

void machine_base_t::insertJobToHead(job_base_t *job)
{
    job->setMachine(this);
    if (size_of_jobs > 0) {
        job->setNext(head);
        head = job;
    } else {
        tail = head = job;
    }

    ++size_of_jobs;
}

void machine_base_t::sortJob()
{
    head = (job_base_t *) list_merge_sort(head);
}

double machine_base_t::scheduling()
{
    sortJob();

    list_node_t<double> *iter = head, *prev = nullptr;
    job_base_t *job;
    double time_line = available_time + machineInitialSetupTime();

    // while(iter != nullptr){
    //     job = (job_base_t *)iter;
    //     job->setStartTime(time_line);
    //
    // }
}