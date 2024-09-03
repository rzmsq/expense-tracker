#pragma once

#include "./expense.hpp"

class Expenses
{
private:
    std::vector<Expense> exps;

    size_t sumMonth;
    size_t sum{0};

    inline const void calc_sum(const int32_t &);
    const void calc_sum_month(const int16_t &);

public:
    Expenses();
    ~Expenses();

    const void add_expense(const boost_date &, const std::string &, const int32_t &);
    const void edit_expense(const size_t &, const std::string &, const std::string &);
    const void del_expense(const size_t &);
    const void print_expenses() const;
    const void print_summary() const;
    const void print_summary_date(const int16_t &);
};