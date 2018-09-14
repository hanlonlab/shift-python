#pragma once

#include "Common.h"

#include <string>

namespace PortfolioItem {

void bindPython(py::module& m)
{
    //! Bind class
    py::class_<shift::PortfolioItem> PORTFOLIO_ITEM(m, "PortfolioItem");
    PORTFOLIO_ITEM //! Bind constructor
        .def(py::init<>())
        .def(py::init<std::string, int, double, double>());
    PORTFOLIO_ITEM //! Bind function
        .def("getSymbol", &shift::PortfolioItem::getSymbol)
        .def("getShares", &shift::PortfolioItem::getShares)
        .def("getPrice", &shift::PortfolioItem::getPrice)
        .def("getPL", &shift::PortfolioItem::getPL);
}

} // PortfolioItem
