#include <glib.h>
#include <locale.h>
#include <stdlib.h>

#include "../src/string_process.h"

typedef struct
{
} Fixture;

static void set_up(Fixture *fixture, gconstpointer user_data)
{
}

static void tear_down(Fixture *fixture, gconstpointer user_data)
{
}

static void test1(Fixture *fixture, gconstpointer user_data)
{
    char str[100] = "hello";
    char *reverse = reverse_str(str);
    g_assert_cmpstr(reverse, == , "olleh");
}

static void test2(Fixture *fixture, gconstpointer user_data)
{
    char str[100] = "jiangxin";
    char *reverse = reverse_str(str);
    g_assert_cmpstr(reverse, == , "nixgnaij");
}

int test_string_process(int argc, char *argv[])
{
    g_test_init(&argc, &argv, NULL);
    // Define the tests.
    g_test_add("/my-object/test1", Fixture, NULL,
               set_up, test1,
               tear_down);
    g_test_add("/my-object/test2", Fixture, NULL,
               set_up, test2,
               tear_down);
    return g_test_run();
}
