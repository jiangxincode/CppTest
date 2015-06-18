#ifndef QUOTE_H_INCLUDED
#define QUOTE_H_INCLUDED

#include <string>
#include <iostream>

class Quote
{

public:
    Quote() = default;
    Quote(const std::string &book, double sales_price) : bookNo(book), price(sales_price) {}
    std::string isbn() const
    {
        return bookNo;
    }
    virtual double net_price(std::size_t n) const
    {
        return n * price ;
    }
    virtual ~Quote() = default;

public:
    double price = 0.0;
    std::string bookNo;
};

double print_total(std::ostream &, const Quote &, std::size_t);


class Bulk_quote : public Quote
{
public:
    Bulk_quote() = default;
    Bulk_quote(const std::string& book, double p, std::size_t qty, double disc) : Quote(book, p), min_qty(qty), discount(disc) {}
    double net_price(std::size_t) const override;

private:
    std::size_t min_qty = 0;
    double discount = 0.0;
};


#endif // QUOTE_H_INCLUDED
