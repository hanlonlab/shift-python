#pragma once

#include "Common.h"

namespace BestPrice {

void bindPython(py::module& m)
{
    //! Bind class
    py::class_<shift::BestPrice> BEST_PRICE(m, "BestPrice");
    BEST_PRICE //! Bind constructor
        .def(py::init<double, int, double, int, double, int, double, int>(), py::arg("global_bid_price"), py::arg("global_bid_size"), py::arg("global_ask_price"), py::arg("global_ask_size"), py::arg("local_bid_price"), py::arg("local_bid_size"), py::arg("local_ask_price"), py::arg("local_ask_size"));
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
