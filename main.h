#pragma once
void runApp(const char *argv[], int argc);

enum option
{
    add,
    edit,
    del,
    p_all,
    p_sum,
    p_sum_m,
    help,
    err
};