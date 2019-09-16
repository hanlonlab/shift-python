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
        // .def("is_open_bp_ready", &shift::PortfolioSummary::isOpenBPReady)
        // .def("get_open_bp", &shift::PortfolioSummary::getOpenBP)
        .def("get_total_bp", &shift::PortfolioSummary::getTotalBP)
        .def("get_total_shares", &shift::PortfolioSummary::getTotalShares)
        .def("get_total_realized_pl", &shift::PortfolioSummary::getTotalRealizedPL)
        .def("get_timestamp", &shift::PortfolioSummary::getTimestamp);
}

} // PortfolioSummary
