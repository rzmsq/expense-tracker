#include "expenses.hpp"

const void Expenses::save_to_json() const
{
    try
    {
        std::ofstream f;
        f.open("data.json", std::ios_base::ate);

        json f_j;

        for (size_t i = 0; i < exps.size(); i++)
        {
            std::string id_s = std::to_string(i);
            f_j["id"][id_s]["date"] =
                boost::gregorian::to_iso_string(exps[i].get_date());
            f_j["id"][id_s]["description"] = exps[i].get_description();
            f_j["id"][id_s]["amount"] = exps[i].get_amount();
        }

        f << f_j;
        f.close();
    }
    catch (...)
    {
        std::cout << "Error saving data\n";
    }
};
const void Expenses::take_from_json()
{
    try
    {
        std::ifstream f("data.json");
        if (f.good())
        {
            json f_j = json::parse(f);

            for (size_t i = 0; i < f_j["id"].size(); i++)
            {
                std::string id_s = std::to_string(i);
                boost_date date =
                    boost::gregorian::from_undelimited_string(f_j["id"][id_s]["date"]);
                std::string description = f_j["id"][id_s]["description"];
                double amount = f_j["id"][id_s]["amount"];

                Expense exp = Expense(date, description, amount);
                exps.push_back(exp);
                this->calc_sum(exp.get_amount());
            }
        }
        else
            std::runtime_error("file");

        f.close();
    }
    catch (...)
    {
        std::cout << "Error loading data\n";
    }
};

const void Expenses::add_expense(const boost_date &date,
                                 const std::string &description,
                                 const double &amount)
{
    try
    {
        Expense exp = Expense(date, description, amount);

        exps.push_back(exp);
        this->calc_sum(exp.get_amount());
        this->save_to_json();
        std::cout << "Expense added successfully (ID: " << exps.size() - 1 << ")\n";
    }
    catch (...)
    {
        std::cout << "Failed! Unknown error\n";
    }
}
const void Expenses::del_expense(const int32_t &id)
{

    try
    {
        if (id > exps.size() || id < 0 || exps.size() == 0)
            throw std::out_of_range("doesnt exists id");

        exps.erase(exps.begin() + id);
        this->save_to_json();
        std::cout << "Success!\n";
    }
    catch (std::out_of_range)
    {
        std::cout << "Failed! Incorrect ID";
    }
    catch (...)
    {
        std::cout << "Failed! Please enter: delete <ID>\n";
    }
}

const void Expenses::edit_expense(const int32_t &id,
                                  const std::string &tbl,
                                  const std::string &newVal)
{
    try
    {
        if (tbl == "--date")
            /*! Accepted formats are: "2003-02-10" or " 2003-Feb-10" or
             * "2003-Feburary-10"
             */
            exps.at(id).set_date(boost::gregorian::from_string(newVal));
        else if (tbl == "--description")
            exps.at(id).set_description(newVal);
        else if (tbl == "--amount")
        {
            double amount = std::stod(newVal);
            if (amount <= 0)
                throw std::runtime_error("amount <= 0");

            exps.at(id).set_amount(std::stod(newVal));
        }
        this->save_to_json();
        std::cout << "Success\n";
    }
    catch (std::out_of_range)
    {
        std::cout << "Failed! Incorrect ID or date\n";
    }
    catch (...)
    {
        std::cout << "Failed! Please enter: "
                     " or edit <ID> --date <YYYY-MM-DD>"
                     " or edit <ID> --description <description up to 13 symb>"
                     " or edit <ID> --amount <sum more than 0>\n";
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

inline const void Expenses::calc_sum(const double &amount)
{
    sum += amount;
}

const void Expenses::print_summary_date(const int32_t &month)
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
    this->take_from_json();
}

Expenses::~Expenses()
{
}