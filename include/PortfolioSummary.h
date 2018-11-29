#pragma once

#include "Common.h"

namespace PortfolioSummary {

void bindPython(py::module& m)
{
    //! Bind class
    py::class_<shift::PortfolioSummary> PORTFOLIO_SUMMARY(m, "PortfolioSummary");
    PORTFOLIO_SUMMARY //! Bind constructor
        .def(py::init<double, int, double>(), py::arg("totalBP"), py::arg("totalShares"), py::arg("totalRealizedPL"));
    PORTFOLIO_SUMMARY //! Bind function
        .def("isOpenBPReady", &shift::PortfolioSummary::isOpenBPReady);
    PORTFOLIO_SUMMARY //! Bind property
        .def_property("totalBP", &shift::PortfolioSummary::getTotalBP, &shift::PortfolioSummary::setTotalBP, py::return_value_policy::reference)
        .def_property("totalShares", &shift::PortfolioSummary::getTotalShares, &shift::PortfolioSummary::setTotalShares, py::return_value_policy::reference)
        .def_property("totalRealizedPL", &shift::PortfolioSummary::getTotalRealizedPL, &shift::PortfolioSummary::setTotalRealizedPL, py::return_value_policy::reference)
        .def_property("openBP", &shift::PortfolioSummary::getOpenBP, &shift::PortfolioSummary::setOpenBP, py::return_value_policy::reference);
}

} // PortfolioSummary
