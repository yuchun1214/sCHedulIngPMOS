#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include "include/list.h"

using namespace std;

namespace list
{
template <typename T>
class list_test_data_t
{
public:
    vector<T> data;
    friend ostream &operator<<(ostream &out, const list_test_data_t<T> &data)
    {
        out << "[";
        for (auto &d : data.data) {
            out << d << ", ";
        }
        out << "]";
        return out;
    }
};

class test_list_int_t : public testing::TestWithParam<list_test_data_t<int>>
{
};

// class test_list_double_t : public
// testing::TestWithParam<list_test_data_t<double>>
// {
// };

TEST_P(test_list_int_t, test_sorted)
{
    auto cs = GetParam();
    list_node_t<int> *head, *iter;
    head = iter = nullptr;
    for (auto &d : cs.data) {
        if (head == nullptr) {
            iter = head = new list_node_t<int>(d);
        } else {
            iter->setNext(new list_node_t<int>(d));
            iter = iter->getNext();
        }
    }

    int number_of_elements = 0;
    iter = head;
    while (iter != nullptr) {
        number_of_elements++;
        iter = iter->getNext();
    }

    EXPECT_EQ(number_of_elements, cs.data.size());

    list_node_t<int> *sorted_result = list_merge_sort(head);

    // sort cs.data
    sort(cs.data.begin(), cs.data.end());

    // compare sorted_result with cs.data
    iter = sorted_result;
    for (auto &d : cs.data) {
        EXPECT_EQ(iter->getData(), d);
        iter = iter->getNext();
    }
}

INSTANTIATE_TEST_SUITE_P(
    list,
    test_list_int_t,
    testing::Values(list_test_data_t<int>{vector<int>{1, 2, 3, 4, 5}},
                    list_test_data_t<int>{vector<int>{5, 4, 3, 2, 1}},
                    list_test_data_t<int>{vector<int>{1, 3, 5, 2, 4}},
                    list_test_data_t<int>{vector<int>{1, 1, 1, 1, 1}},
                    list_test_data_t<int>{vector<int>{1, 2, 3, 4, 5, 6}},
                    list_test_data_t<int>{vector<int>{6, 5, 4, 3, 2, 1}},
                    list_test_data_t<int>{vector<int>{1, 3, 5, 2, 4, 6}},
                    list_test_data_t<int>{vector<int>{1, 1, 1, 1, 1, 1}}));

// INSTANTIATE_TEST_SUITE_P(
//     list,
//     test_list_double_t,
//     testing::Values(
//         list_test_data_t<double>{vector<double>{1.0, 2.0, 3.0, 4.0, 5.0}},
//         list_test_data_t<double>{vector<double>{5.0, 4.0, 3.0, 2.0, 1.0}},
//         list_test_data_t<double>{vector<double>{1.0, 3.0, 5.0, 2.0, 4.0}},
//         list_test_data_t<double>{vector<double>{1.0, 1.0, 1.0, 1.0, 1.0}},
//         list_test_data_t<double>{vector<double>{1.0, 2.0, 3.0, 4.0, 5.0, 6.0}},
//         list_test_data_t<double>{vector<double>{6.0, 5.0, 4.0, 3.0, 2.0, 1.0}},
//         list_test_data_t<double>{vector<double>{1.0, 3.0, 5.0, 2.0, 4.0, 6.0}},
//         list_test_data_t<double>{vector<double>{1.0, 1.0, 1.0, 1.0, 1.0, 1.0}}
//     )
// );
};  // namespace list