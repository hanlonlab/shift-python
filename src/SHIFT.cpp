#include "BestPrice.h"
#include "Order.h"
#include "OrderBook.h"
#include "OrderBookEntry.h"
#include "PortfolioItem.h"
#include "PortfolioSummary.h"
#include "Trader.h"

/*!
 * @brief PYBIND11_MODULE creates module entry points
 */
PYBIND11_MODULE(shift, m)
{
    m.doc() = "SHIFT-Python API";
    m.attr("__version__") = "1.3.0";

    py::register_exception<shift::IncorrectPasswordError>(m, "IncorrectPasswordError");
    py::register_exception<shift::ConnectionTimeoutError>(m, "ConnectionTimeoutError");

    BestPrice::bindPython(m);
    Order::bindPython(m);
    OrderBook::bindPython(m);
    OrderBookEntry::bindPython(m);
    PortfolioItem::bindPython(m);
    PortfolioSummary::bindPython(m);
    Trader::bindPython(m);
}
