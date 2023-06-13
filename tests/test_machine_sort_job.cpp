#include <gtest/gtest.h>
#include <algorithm>
#include <vector>
#include "include/job_base.h"
#include "include/list.h"
#include "include/machine_base.h"

using namespace std;

namespace test_machine_add_sort_job
{
class test_job_t : public job_base_t
{
public:
    test_job_t(double os_gene_val) : job_base_t()
    {
        _os_gene = new double(os_gene_val);
    }

    ~test_job_t() { delete _os_gene; }
};

class add_sort_job_test_data_t
{
public:
    vector<double> data;
    friend ostream &operator<<(ostream &out,
                               const add_sort_job_test_data_t &data)
    {
        out << "[";
        for (auto &d : data.data) {
            out << d << ", ";
        }
        out << "]";
        return out;
    }
};

class test_machine_add_sort_job_t
    : public testing::TestWithParam<add_sort_job_test_data_t>
{
};

TEST_P(test_machine_add_sort_job_t, test_add_job_to_the_tail)
{
    auto cs = GetParam();
    machine_base_t *machine = new machine_base_t();

    for (auto &d : cs.data) {
        job_base_t *j = new test_job_t(d);
        machine->appendJob(j);
    }

    EXPECT_EQ(machine->getSizeOfJobs(), cs.data.size());

    list_node_t<double> *iter = machine->getHeadOfJob();
    list_node_t<double> *prev;
    int i = 0;

    while (iter != nullptr) {
        EXPECT_EQ(iter->getData(), cs.data[i++]);
        prev = iter;
        iter = iter->getNext();
        delete prev;
    }

    delete machine;
}

TEST_P(test_machine_add_sort_job_t, test_insert_job_to_the_head)
{
    auto cs = GetParam();
    machine_base_t *machine = new machine_base_t();

    for (auto &d : cs.data) {
        job_base_t *j = new test_job_t(d);
        machine->insertJobToHead(j);
    }

    EXPECT_EQ(machine->getSizeOfJobs(), cs.data.size());

    list_node_t<double> *iter = machine->getHeadOfJob();
    list_node_t<double> *prev;

    size_t i = cs.data.size();
    while (iter != nullptr) {
        EXPECT_EQ(iter->getData(), cs.data[--i]);
        prev = iter;
        iter = iter->getNext();
        delete prev;
    }


    delete machine;
}

TEST_P(test_machine_add_sort_job_t, test_sort_jobs)
{
    auto cs = GetParam();
    machine_base_t *machine = new machine_base_t();

    for (auto &d : cs.data) {
        job_base_t *j = new test_job_t(d);
        machine->insertJobToHead(j);
    }

    EXPECT_EQ(machine->getSizeOfJobs(), cs.data.size());

    machine->sortJob();

    list_node_t<double> *iter = machine->getHeadOfJob();
    list_node_t<double> *prev;

    // sort cs.data
    sort(cs.data.begin(), cs.data.end());

    int i = 0;
    while (iter != nullptr) {
        EXPECT_EQ(iter->getData(), cs.data[i++]);
        prev = iter;
        iter = iter->getNext();
        delete prev;
    }


    delete machine;
}


INSTANTIATE_TEST_SUITE_P(
    test_machine_add_sort_job,
    test_machine_add_sort_job_t,
    testing::Values(
        add_sort_job_test_data_t{{1, 2, 3, 4, 5}},
        add_sort_job_test_data_t{{5, 4, 3, 2, 1}},
        add_sort_job_test_data_t{{1, 3, 5, 2, 4}},
        add_sort_job_test_data_t{{1, 1, 1, 1, 1}},
        add_sort_job_test_data_t{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}},
        add_sort_job_test_data_t{{10, 9, 8, 7, 6, 5, 4, 3, 2, 1}},
        add_sort_job_test_data_t{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}},
        add_sort_job_test_data_t{{11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1}},
        add_sort_job_test_data_t{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}},
        add_sort_job_test_data_t{{12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1}},
        add_sort_job_test_data_t{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13}},
        add_sort_job_test_data_t{{13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1}},
        add_sort_job_test_data_t{
            {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}}));

}  // namespace test_machine_add_sort_job
