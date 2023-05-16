#ifndef __MACHINE_BASE_H__
#define __MACHINE_BASE_H__

#include <string>
#include "include/forward_declaration.h"
#include "include/list.h"

class machine_base_t
{
protected:
    job_base_t *head;
    job_base_t *tail;

    std::string machine_no;
    int size_of_jobs;
    double available_time;

public:
    void appendJob(job_base_t *job);
    void insertJobToHead(job_base_t *job);
    void sortJob();

    job_base_t *getHeadOfJob() { return head; }

    int getSizeOfJobs() { return size_of_jobs; }

    virtual double setupTime(job_base_t *job1, job_base_t *job2) { return 0; }
    virtual double machineInitialSetupTime() { return 0; }

    double scheduling();
    // double getQuality();
    // double getAvailableTime();
};

#endif