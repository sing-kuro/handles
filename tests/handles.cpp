#include <stdexcept>
#include <string>
#include <algorithm>
#include <gtest/gtest.h>
#include <handles/handles.hpp>

TEST(handles_test, insert_erase)
{
    hdl::handles<unsigned int, std::string> strings;
    unsigned int a = strings.insert("a");
    unsigned int b = strings.insert("b");
    unsigned int c = strings.insert("c");
    unsigned int d = strings.insert("d");
    EXPECT_EQ(strings[a], "a");
    EXPECT_EQ(strings[b], "b");
    EXPECT_EQ(strings[c], "c");
    EXPECT_EQ(strings[d], "d");
    strings.erase(b);
    EXPECT_THROW(strings.at(b), std::out_of_range);
    EXPECT_EQ(strings[a], "a");
    EXPECT_EQ(strings[c], "c");
    EXPECT_EQ(strings[d], "d");
    unsigned int e = strings.insert("e");
    EXPECT_EQ(e, b);
    EXPECT_EQ(strings[e], "e");
    auto all = strings.all_handles();
    EXPECT_EQ(all.size(), 4);
    EXPECT_NE(std::ranges::find(all, a), all.end());
    EXPECT_NE(std::ranges::find(all, c), all.end());
    EXPECT_NE(std::ranges::find(all, d), all.end());
    EXPECT_NE(std::ranges::find(all, e), all.end());
}
