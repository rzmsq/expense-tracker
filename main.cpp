#include <iostream>
#include <iomanip>
#include <variant>
#include <string>
#include <vector>
#include <map>

#include <boost/date_time/gregorian/gregorian.hpp>

using boost_date = boost::gregorian::date;

class Expense
{
private:
    boost_date _date;
    std::string _description;
    int32_t _amount;

public:
    Expense(const boost_date &,
            const std::string &,
            const int32_t &);
    ~Expense();

    boost_date get_date() const;
    std::string get_description() const;
    int32_t get_amount() const;
};

Expense::Expense(const boost_date &date,
                 const std::string &description,
                 const int32_t &amount)
{
    _date = date;
    _description = description;
    _amount = amount;
}

Expense::~Expense()
{
}

boost_date Expense::get_date() const
{
    return _date;
}

std::string Expense::get_description() const
{
    return _description;
}

int32_t Expense::get_amount() const
{
    return _amount;
}

class Expenses
{
private:
    std::vector<Expense> exps;

public:
    Expenses();
    ~Expenses();

    const void add_expense(const boost_date &, const std::string &, const int32_t &);
    const void print_expenses() const;
};

const void Expenses::add_expense(const boost_date &date,
                                 const std::string &description,
                                 const int32_t &amount)
{
    Expense exp = Expense(date, description, amount);

    exps.push_back(exp);
}
const void Expenses::print_expenses() const
{
    if (exps.empty())
    {
        std::cout << "You have no expenses\n";
        return;
    }

    std::cout << "#  ID" << std::setw(10)
              << "Date" << std::setw(20)
              << "Description" << std::setw(10)
              << "Amount\n";
    for (size_t i = 0; i < exps.size(); i++)
    {
        std::cout << "#  " << i << "\t" // i dont know why but here std::setw(10) just dont work
                  << exps[i].get_date() << std::setw(13)
                  << exps[i].get_description() << std::setw(10)
                  << exps[i].get_amount() << '$' << '\n';
    }
};

Expenses::Expenses()
{
}

Expenses::~Expenses()
{
}

int main(int argc, char const *argv[])
{
    Expenses exps = Expenses();

    boost_date today = boost::gregorian::day_clock::local_day();

    exps.add_expense(today, "Cofee", 4);
    exps.add_expense(today, "Books", 400);
    exps.add_expense(today, "products", 47);
    exps.print_expenses();

    return 0;
}
