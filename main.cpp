#include "expenses.hpp"
#include "main.h"

int main(int argc, char const *argv[])
{
    try
    {
        if (argc < 2)
        {
            std::cout << "Error for more information enter ./expense-tracker help\n";
            return EXIT_FAILURE;
        }
        runApp(argv, argc);
    }
    catch (...)
    {
        std::cout << "Unknown error\n";
    }

    return 0;
}

void runApp(const char *argv[], int argc)
{
    int16_t opt{-1};
    const std::string argv1 = argv[1];

    if (argv1 == "add" && argc == 6)
        opt = option::add;
    else if (argv1 == "edit" && argc == 5)
        opt = option::edit;
    else if (argv1 == "delete" && argc == 3)
        opt = option::del;
    else if (argv1 == "list" && argc == 2)
        opt = option::p_all;
    else if (argv1 == "summary" && argc == 2)
        opt = option::p_sum;
    else if (argv1 == "summary" && argc == 4)
        opt = option::p_sum_m;
    else if (argv1 == "help")
        opt = option::help;
    else
        opt = option::err;

    Expenses exps = Expenses();
    switch (opt)
    {
    case option::add:
    {
        const std::string description = argv[3];
        const double amount = std::stod(argv[5]);
        if (description.size() < 13 && amount > 0)
        {
            boost_date today = boost::gregorian::day_clock::local_day();
            exps.add_expense(today, description, amount);
        }
        else
            std::cout << "Failed! Please enter: add --description <description up to 13 symb>"
                         " --amount <sum more than 0>\n";
        break;
    }
    case option::edit:
    {
        const int32_t id = std::stoi(argv[2]);
        const std::string tbl = argv[3];
        const std::string newVal = argv[4];

        exps.edit_expense(id, tbl, newVal);
        break;
    }
    case option::del:
    {
        const int32_t id = std::stoi(argv[2]);
        exps.del_expense(id);
        break;
    }
    case option::p_all:
        exps.print_expenses();
        break;
    case option::p_sum:
        exps.print_summary();
        break;
    case option::p_sum_m:
    {
        const int32_t month = std::stoi(argv[3]);
        if (month <= 0 || month > 12)
            std::cout << "Failed! Please enter summary --month <number of month 1-12>\n";
        else
            exps.print_summary_date(month);
        break;
    }
    case option::help:
        std::cout << "\n\nThis is expenses tracker app, which can help to follow your finance\n\n"
                     "Commands that are supported:\n"
                     "For adding new expense\n"
                     "\tadd --description <description up to 13 symb>"
                     " --amount <sum more than 0>\n\n"
                     "For editing existing expense\n"
                     "\tor edit <ID> --date <XXXX-XX-XX>\n"
                     "\tor edit <ID> --description <description up to 13 symb>\n"
                     "\tor edit <ID> --amount <sum more than 0>\n\n"
                     "For delete existing expense\n"
                     "\tdelete <ID>\n\n"
                     "To print all expenses\n"
                     "\tlist\n\n"
                     "To print your all expense amount\n"
                     "\tsummary\n\n"
                     "To print the amount of your expense for a specific month\n"
                     "\tsummary --month <number of month 1-12>\n\n";
        break;
    default:
        std::cout << "Unknown command!\n";
        break;
    }
}
