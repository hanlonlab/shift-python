#pragma once

#include "Common.h"

namespace BestPrice {

void bindPython(py::module& m)
{
    //! Bind class
    py::class_<shift::BestPrice> BEST_PRICE(m, "BestPrice");
    BEST_PRICE //! Bind constructor
        .def(py::init<double, int, double, int, double, int, double, int>(), py::arg("globalBidPrice"), py::arg("globalBidSize"), py::arg("globalAskPrice"), py::arg("globalAskSize"), py::arg("localBidPrice"), py::arg("localBidSize"), py::arg("localAskPrice"), py::arg("localAskSize"));
    BEST_PRICE //! Bind function
        .def("getBidPrice", &shift::BestPrice::getBidPrice)
        .def("getBidSize", &shift::BestPrice::getBidSize)
        .def("getAskPrice", &shift::BestPrice::getAskPrice)
        .def("getAskSize", &shift::BestPrice::getAskSize)
        .def("getGlobalBidPrice", &shift::BestPrice::getGlobalBidPrice)
        .def("getGlobalBidSize", &shift::BestPrice::getGlobalBidSize)
        .def("getGlobalAskPrice", &shift::BestPrice::getGlobalAskPrice)
        .def("getGlobalAskSize", &shift::BestPrice::getGlobalAskSize)
        .def("getLocalBidPrice", &shift::BestPrice::getLocalBidPrice)
        .def("getLocalBidSize", &shift::BestPrice::getLocalBidSize)
        .def("getLocalAskPrice", &shift::BestPrice::getLocalAskPrice)
        .def("getLocalAskSize", &shift::BestPrice::getLocalAskSize);
}

} // BestPrice
