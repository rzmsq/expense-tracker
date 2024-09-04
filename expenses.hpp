#pragma once

#include <fstream>
#include <nlohmann/json.hpp>

#include "./expense.hpp"

class Expenses
{
private:
    using json = nlohmann::json;

    std::vector<Expense> exps;

    double sumMonth;
    double sum{0};

    inline const void calc_sum(const double &);
    const void calc_sum_month(const int16_t &);
    const void save_to_json() const;
    const void take_from_json();

public:
    Expenses();
    ~Expenses();

    const void add_expense(const boost_date &, const std::string &, const double &);
    const void edit_expense(const int32_t &, const std::string &, const std::string &);
    const void del_expense(const int32_t &);
    const void print_expenses() const;
    const void print_summary() const;
    const void print_summary_date(const int32_t &);
};