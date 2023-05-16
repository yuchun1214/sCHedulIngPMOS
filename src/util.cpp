#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <regex>
#include <string>
#include <vector>

#include "include/def.h"
#include "include/util.h"

#ifdef WIN32
#include <intrin.h>
#endif


std::vector<std::string> split(char *text, char delimiter)
{
    char *iter = text, *prev = text;
    std::vector<std::string> data;
    while (*iter) {
        if (*iter == delimiter ||
            *iter == '\n') {  // for unix-like newline character
            *iter = '\0';
            data.push_back(prev);
            prev = ++iter;
        } else if (*iter == '\r' &&
                   *(iter + 1) ==
                       '\n') {  // for windows newline characters '\r\n'
            *iter = '\0';
            data.push_back(prev);
            iter += 2;
            prev = iter;
        } else if (*(iter + 1) == '\0') {
            data.push_back(prev);
            ++iter;
        } else {
            ++iter;
        }
    }

    return data;
}

std::string join(std::vector<std::string> strings, std::string delimiter)
{
    if (strings.size() == 0)
        return "";
    std::string s;
    iter_range(strings, i, 0, strings.size() - 1)
    {
        s += strings[i];
        s += delimiter;
    }
    s += strings[strings.size() - 1];
    return s;
}

void stringToLower(char *text)
{
    for (; *text; ++text)
        *text |= 0x20;
}

void stringToUpper(char *text)
{
    for (; *text; ++text)
        *text ^= 0x20;
}


void random(double *genes, int size)
{
    for (int i = 0; i < size; ++i) {
        genes[i] = randomDouble();
    }
}

int randomRange(int start, int end, int different_num)
{
    if (different_num < 0) {
        return start + rand() % (end - start);
    } else {
        int rnd = start + (rand() % (end - start));
        while (rnd == different_num) {
            rnd = start + (rand() % (end - start));
        }
        return rnd;
    }
}

double randomDouble()
{
    return (double) rand() / (double) (RAND_MAX + 1.0);
}


std::regex isNumeric::_regex(R"([-]?(([0-9]+[.]?[0-9]*)|([0-9]*[.]?[0-9]+)))");

bool isNumeric::operator()(std::string text)
{
    return regex_match(text, _regex);
}
