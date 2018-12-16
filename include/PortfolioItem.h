#pragma once

#include "Common.h"

#include <string>

#include <pybind11/chrono.h>

namespace PortfolioItem {

void bindPython(py::module& m)
{
    //! Bind class
    py::class_<shift::PortfolioItem> PORTFOLIO_ITEM(m, "PortfolioItem");
    PORTFOLIO_ITEM //! Bind constructor
        .def(py::init<>())
        .def(py::init<std::string, int, int, double, double, double>());
    PORTFOLIO_ITEM //! Bind function
        .def("getSymbol", &shift::PortfolioItem::getSymbol)
        .def("getShares", &shift::PortfolioItem::getShares)
        .def("getLongShares", &shift::PortfolioItem::getLongShares)
        .def("getShortShares", &shift::PortfolioItem::getShortShares)
        .def("getPrice", &shift::PortfolioItem::getPrice)
        .def("getLongPrice", &shift::PortfolioItem::getLongPrice)
        .def("getShortPrice", &shift::PortfolioItem::getShortPrice)
        .def("getRealizedPL", &shift::PortfolioItem::getRealizedPL)
        .def("getTimestamp", &shift::PortfolioItem::getTimestamp);
}

} // PortfolioItem
