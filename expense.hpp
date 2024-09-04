#pragma once

#include <algorithm>
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
    double _amount;

public:
    Expense(const boost_date &,
            const std::string &,
            const double &);
    ~Expense();

    const boost_date get_date() const;
    const std::string get_description() const;
    const double get_amount() const;

    const void set_date(const boost_date &);
    const void set_description(const std::string &);
    const void set_amount(const double &);
};