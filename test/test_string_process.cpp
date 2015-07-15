#include "../src/string_process.h"
#include "../include/gtest/gtest.h"
#include <stdlib.h>

class StringProcessTest:public testing::Test
{
protected:
    virtual void SetUp() {}
    virtual void TearDown() {}
};


TEST_F(StringProcessTest, squeeze_test)
{
    char str[BUFSIZ] = "Hello Nanjing University!";
    const char dict[BUFSIZ] = "el";
    EXPECT_EQ(4,squeeze(str,dict));
    EXPECT_STREQ("Ho Nanjing Univrsity!", str);
}

TEST_F(StringProcessTest, decode_test)
{
    std::string str_src("N BTZQI WFYMJW GJ KNWXY NS F QNYYQJ NGJWNFS ANQQFLJ YMFS XJHTSI NS WTRJ");
    decode(str_src);
    EXPECT_STREQ("I WOULD RATHER BE FIRST IN A LITTLE IBERIAN VILLAGE THAN SECOND IN ROME",str_src.c_str());
}

TEST_F(StringProcessTest, FindOne_test)
{
    char input[256] = "I love you";
    char output[256];
    FindOne(input, output);
    EXPECT_STREQ(output, "Ieluvy");
}
