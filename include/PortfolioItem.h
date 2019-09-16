#pragma once

#include "Common.h"

#include <string>

#include <pybind11/chrono.h>

namespace PortfolioItem {

void bindPython(py::module& m)
{
    //! bind class
    py::class_<shift::PortfolioItem> PORTFOLIO_ITEM(m, "PortfolioItem");
    PORTFOLIO_ITEM //! bind constructor
        .def(py::init<>())
        .def(py::init<std::string, int, int, double, double, double>(), py::arg("symbol"), py::arg("long_shares"), py::arg("short_shares"), py::arg("long_price"), py::arg("short_price"), py::arg("realized_pl"));
    PORTFOLIO_ITEM //! bind function
        .def("get_symbol", &shift::PortfolioItem::getSymbol)
        .def("get_shares", &shift::PortfolioItem::getShares)
        .def("get_long_shares", &shift::PortfolioItem::getLongShares)
        .def("get_short_shares", &shift::PortfolioItem::getShortShares)
        .def("get_price", &shift::PortfolioItem::getPrice)
        .def("get_long_price", &shift::PortfolioItem::getLongPrice)
        .def("get_short_price", &shift::PortfolioItem::getShortPrice)
        .def("get_realized_pl", &shift::PortfolioItem::getRealizedPL)
        .def("get_timestamp", &shift::PortfolioItem::getTimestamp);
}

} // PortfolioItem
