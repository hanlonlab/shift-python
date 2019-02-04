#pragma once

#include "Common.h"

#include <pybind11/chrono.h>

namespace PortfolioSummary {

void bindPython(py::module& m)
{
    //! Bind class
    py::class_<shift::PortfolioSummary> PORTFOLIO_SUMMARY(m, "PortfolioSummary");
    PORTFOLIO_SUMMARY //! Bind constructor
        .def(py::init<>())
        .def(py::init<double, int, double>(), py::arg("totalBP"), py::arg("totalShares"), py::arg("totalRealizedPL"));
    PORTFOLIO_SUMMARY //! Bind function
        // .def("isOpenBPReady", &shift::PortfolioSummary::isOpenBPReady)
        // .def("getOpenBP", &shift::PortfolioSummary::getOpenBP)
        .def("getTotalBP", &shift::PortfolioSummary::getTotalBP)
        .def("getTotalShares", &shift::PortfolioSummary::getTotalShares)
        .def("getTotalRealizedPL", &shift::PortfolioSummary::getTotalRealizedPL)
        .def("getTimestamp", &shift::PortfolioSummary::getTimestamp);
}

} // PortfolioSummary
