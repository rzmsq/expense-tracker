#include "expenses.hpp"

inline const bool is_numeric(const std::string &str)
{
    std::regex pattern("[0-8]+");
    return std::regex_match(str, pattern);
}

int main(int argc, char const *argv[])
{
    Expenses exps = Expenses();

    boost_date today = boost::gregorian::from_string("2024-09-03");

    exps.add_expense(today, "Cofee", 4);
    exps.add_expense(today, "Books", 400);
    exps.add_expense(today, "products", 47);
    exps.print_expenses();
    exps.print_summary();
    exps.print_summary_date(9);

    exps.edit_expense(0, "description", "milk");
    exps.edit_expense(1, "amount", "5");
    exps.edit_expense(2, "date", "2024-07-23");
    exps.print_expenses();

    exps.del_expense(2);
    exps.print_expenses();

    return 0;
}
