#pragma once

#include "Common.h"

#include <pybind11/chrono.h>

namespace PortfolioSummary {

void bindPython(py::module& m)
{
    //! bind class
    py::class_<shift::PortfolioSummary> PORTFOLIO_SUMMARY(m, "PortfolioSummary");
    PORTFOLIO_SUMMARY //! bind constructor
        .def(py::init<>())
        .def(py::init<double, int, double>(), py::arg("total_bp"), py::arg("total_shares"), py::arg("total_realized_pl"));
    PORTFOLIO_SUMMARY //! bind function
        // .def("isOpenBPReady", &shift::PortfolioSummary::isOpenBPReady)
        // .def("getOpenBP", &shift::PortfolioSummary::getOpenBP)
        .def("getTotalBP", &shift::PortfolioSummary::getTotalBP)
        .def("getTotalShares", &shift::PortfolioSummary::getTotalShares)
        .def("getTotalRealizedPL", &shift::PortfolioSummary::getTotalRealizedPL)
        .def("getTimestamp", &shift::PortfolioSummary::getTimestamp);
}

} // PortfolioSummary
