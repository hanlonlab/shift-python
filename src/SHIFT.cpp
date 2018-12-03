#include "BestPrice.h"
#include "Order.h"
#include "OrderBook.h"
#include "OrderBookEntry.h"
#include "PortfolioItem.h"
#include "PortfolioSummary.h"
#include "Trader.h"

/*!
 * \brief PYBIND11_MODULE create module entry points
 */
PYBIND11_MODULE(shift, m)
{
    m.doc() = "Python SHIFT plugin";

    py::register_exception<shift::IncorrectPassword>(m, "IncorrectPassword");
    py::register_exception<shift::ConnectionTimeout>(m, "ConnectionTimeout");

    BestPrice::bindPython(m);
    Order::bindPython(m);
    OrderBook::bindPython(m);
    OrderBookEntry::bindPython(m);
    PortfolioItem::bindPython(m);
    PortfolioSummary::bindPython(m);
    Trader::bindPython(m);
}
