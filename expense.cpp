#include "expense.hpp"

Expense::Expense(const boost_date &date,
                 const std::string &description,
                 const double &amount)
{
    _date = date;
    _description = description;
    _amount = amount;
}

Expense::~Expense()
{
}

const boost_date Expense::get_date() const
{
    return _date;
}

const std::string Expense::get_description() const
{
    return _description;
}

const double Expense::get_amount() const
{
    return _amount;
}

const void Expense::set_date(const boost_date &date)
{
    this->_date = date;
}

const void Expense::set_description(const std::string &description)
{
    this->_description = description;
}

const void Expense::set_amount(const double &amount)
{
    this->_amount = amount;
}