#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <vector>

#include "include/forward_declaration.h"
#include "include/job_base.h"
#include "include/machine_base.h"

using namespace std;

namespace test_job_base_machine_selection
{
class test_data_t
{
public:
    std::vector<int> machine_set;
    double gene_val;
    int selected_machine;

    test_data_t(std::vector<int> machine_set,
                double gene_val,
                int selected_machine)
    {
        this->machine_set = machine_set;
        this->gene_val = gene_val;
        this->selected_machine = selected_machine;
    }


    friend ostream &operator<<(ostream &out, const test_data_t &data)
    {
        out << "machine_set: [";
        for (auto &m : data.machine_set) {
            out << m << ", ";
        }
        out << "], gene_val: " << data.gene_val
            << ", selected_machine: " << data.selected_machine;
        return out;
    }
};

class machine_t : public machine_base_t
{
private:
    int machine_no;

public:
    machine_t(int no) { machine_no = no; }

    int getMachineNo() { return machine_no; }
};

class job_t : public job_base_t
{
};

class test_job_base_machine_selection_t
    : public testing::TestWithParam<test_data_t>
{
};

TEST_P(test_job_base_machine_selection_t, test_machine_selection)
{
    auto cs = GetParam();
    job_base_t *job = new job_t();

    double *ms_gene = new double(cs.gene_val);
    job->setMsGene(ms_gene);
    std::vector<machine_base_t *> machines;
    for (auto &m : cs.machine_set) {
        machine_base_t *mb = new machine_t(m);
        machines.push_back(mb);
        job->addAvailableMachine(mb, 0);
    }

    machine_t *selected_machine = (machine_t *) job->machineSelection();

    EXPECT_EQ(selected_machine->getMachineNo(), cs.selected_machine);

    delete job;
    delete ms_gene;
    for (auto &m : machines) {
        delete m;
    }
}

TEST_P(test_job_base_machine_selection_t,
       test_machine_selection_exception_for_initialization)
{
    job_base_t *job = new job_t();
    EXPECT_THROW(job->machineSelection(), std::runtime_error);
    delete job;
}

TEST_P(test_job_base_machine_selection_t,
       test_machine_selection_exception_for_positive_gene_value)
{
    auto cs = GetParam();
    job_base_t *job = new job_t();
    double *ms_gene = new double(cs.gene_val + 1.0);
    job->setMsGene(ms_gene);
    EXPECT_THROW(job->machineSelection(), std::runtime_error);

    delete job;
    delete ms_gene;
}


TEST_P(test_job_base_machine_selection_t,
       test_machine_selection_exception_for_negative_gene_value)
{
    auto cs = GetParam();
    job_base_t *job = new job_t();
    double *ms_gene = new double(cs.gene_val - 1.0);
    job->setMsGene(ms_gene);
    EXPECT_THROW(job->machineSelection(), std::runtime_error);

    delete job;
    delete ms_gene;
}

INSTANTIATE_TEST_SUITE_P(
    test_job_base_machine_selection,
    test_job_base_machine_selection_t,
    testing::Values(test_data_t(std::vector<int>{1, 2, 3}, 0.5, 2),
                    test_data_t(std::vector<int>{1, 2, 3}, 0.0, 1),
                    test_data_t(std::vector<int>{1, 2, 3}, 0.9999, 3),
                    test_data_t(std::vector<int>{1, 2, 3}, 0.1, 1),
                    test_data_t(vector<int>{1, 2, 3, 4, 5}, 0.5, 3),
                    test_data_t(vector<int>{1, 2, 3, 4}, 0.25, 2)));
};  // namespace test_job_base_machine_selection