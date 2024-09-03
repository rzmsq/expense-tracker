#include "expenses.hpp"

const void Expenses::add_expense(const boost_date &date,
                                 const std::string &description,
                                 const int32_t &amount)
{
    try
    {
        Expense exp = Expense(date, description, amount);

        exps.push_back(exp);
        this->calc_sum(exp.get_amount());
    }
    catch (...)
    {
        std::cout << "Failed! Unknown error\n";
    }
}
const void Expenses::del_expense(const size_t &id)
{
    if (id > exps.size())
    {
        std::cout << "Failed! Incorrect id\n";
        return;
    }

    try
    {
        exps.erase(exps.begin() + id);
    }
    catch (...)
    {
        std::cout << "Failed! Unknown error\n";
    }
}

const void Expenses::edit_expense(const size_t &id,
                                  const std::string &tbl,
                                  const std::string &newVal)
{
    try
    {
        if (tbl == "date")
            /*! Accepted formats are: "2003-02-10" or " 2003-Feb-10" or
             * "2003-Feburary-10"
             */
            exps.at(id).set_date(boost::gregorian::from_string(newVal));
        else if (tbl == "description")
            exps.at(id).set_description(newVal);
        else if (tbl == "amount")
            exps.at(id).set_amount(std::stoi(newVal));
        else
        {
            std::cout << "Error! Please enter --date or --description or --amount\n";
            return;
        }
        std::cout << "Success\n";
    }
    catch (...)
    {
        std::cout << "Failed! Unknown error\n";
    }
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

const void Expenses::print_summary() const
{
    std::cout << "Your total expenses: " << sum << "$\n";
}

inline const void Expenses::calc_sum(const int32_t &amount)
{
    sum += amount;
}

const void Expenses::print_summary_date(const int16_t &month)
{
    this->calc_sum_month(month);
    std::cout << "Your total expenses for " << month << " month: " << this->sumMonth << "$\n";
}

const void Expenses::calc_sum_month(const int16_t &month)
{
    this->sumMonth = 0;
    for (auto &&el : exps)
    {
        if (el.get_date().month().as_number() == month)
            this->sumMonth += el.get_amount();
    }
}

Expenses::Expenses()
{
}

Expenses::~Expenses()
{
}