#include <gtest/gtest.h>
#include <cstring>
#include <string>
#include <vector>

#define UNIT_TEST
#include "include/csv.h"

using namespace std;

typedef struct bom_data_t {
    unsigned int bom;
    string text;
    bool ans;
} bom_data_t;

ostream &operator<<(ostream &out, bom_data_t cs)
{
    return out << "(" << cs.bom << "," << cs.text << "," << cs.ans << ")";
}

class test_csv_has_bom_t : public testing::TestWithParam<bom_data_t>
{
public:
    string insertBom(string text, unsigned int bom)
    {
        typedef union bom_union {
            unsigned int bom;
            char text[4];
        } bom_union_t;

        bom_union_t _bom;
        _bom.bom = 0;
        _bom.bom = bom;
        text.insert(0, _bom.text,
                    (sizeof(unsigned int) - __builtin_clz(_bom.bom)) >> 2);
        return text;
    }
};

TEST_P(test_csv_has_bom_t, test_has_bom)
{
    auto cs = GetParam();
    csv_t csv;

    // UTF-8
    string test_text = cs.text;

    // test_text = insertBom(test_text, cs.bom);
    char *text = strdup(test_text.c_str());
    bool retval = csv._hasBOM(text, cs.bom, (short) __builtin_clz(cs.bom));
    EXPECT_EQ(retval, cs.ans);
    // free(text);

    // for (unsigned int i = 0; i < data.size(); ++i) {
    //     string test_text = data[i].text;
    //     if (data[i].insert_bom) {
    //         test_text = insertBom(test_text, data[i].bom);
    //     }
    //     char *text = strdup(test_text.c_str());
    //     bool retval =
    //         csv._hasBOM(text, data[i].bom, (short)
    //         __builtin_clz(data[i].bom));
    //     EXPECT_EQ(retval, data[i].ans);
    //     free(text);
    // }
}

INSTANTIATE_TEST_SUITE_P(
    test_has_bom,
    test_csv_has_bom_t,
    testing::Values(

        // UTF-8
        bom_data_t{0x00BFBBEF, "\xEF\xBB\xBFTEXT", true},
        bom_data_t{0x00BFBBEF, "\xEF\xBB\xBF", true},
        bom_data_t{0x00BFBBEF, "TEXT", false},

        // // UTF-16
        bom_data_t{0x0000FFFE, "\xFE\xFFTEXT", true},
        bom_data_t{0x0000FFFE, "\xFE\xFF ", true},
        bom_data_t{0x0000FFFE, "TEXT", false},

        // UTF-7
        bom_data_t{0x00762F2B, "\x2B\x2F\x76TEXT", true},
        bom_data_t{0x00762F2B, "\x2B\x2F\x76", true},
        bom_data_t{0x00762F2B, "TEXT", false},

        // // UTF-1
        bom_data_t{0x004C64F7, "\xF7\x64\x4CTEXT", true},
        bom_data_t{0x004C64F7, "\xF7\x64\x4C", true},
        bom_data_t{0x004C64F7, "TEXT", false},

        // EDBIC
        bom_data_t{0x736673DD, "\xDD\x73\x66\x73TEXT", true},
        bom_data_t{0x736673DD, "\xDD\x73\x66\x73", true},
        bom_data_t{0x736673DD, "TEXT", false},
        // SCSU
        bom_data_t{0x00FFFE0E, "\x0E\xFE\xFFTEXT", true},
        bom_data_t{0x00FFFE0E, "\x0E\xFE\xFF", true},
        bom_data_t{0x00FFFE0E, "TEXT", false},

        // BOCU-1
        bom_data_t{0x0028EEFB, "\xFB\xEE\x28TEXT", true},
        bom_data_t{0x0028EEFB, "\xFB\xEE\x28", true},
        bom_data_t{0x0028EEFB, "TEXT", false},

        // GB-18030
        bom_data_t{0x33953184, "\x84\x31\x95\x33TEXT", true},
        bom_data_t{0x33953184, "\x84\x31\x95\x33", true},
        bom_data_t{0x33953184, "TEXT", false}

        ));