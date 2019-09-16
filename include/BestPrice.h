#pragma once

#include "Common.h"

namespace BestPrice {

void bindPython(py::module& m)
{
    //! bind class
    py::class_<shift::BestPrice> BEST_PRICE(m, "BestPrice");
    BEST_PRICE //! bind constructor
        .def(py::init<double, int, double, int, double, int, double, int>(), py::arg("global_bid_price"), py::arg("global_bid_size"), py::arg("global_ask_price"), py::arg("global_ask_size"), py::arg("local_bid_price"), py::arg("local_bid_size"), py::arg("local_ask_price"), py::arg("local_ask_size"));
    BEST_PRICE //! bind function
        .def("get_bid_price", &shift::BestPrice::getBidPrice)
        .def("get_bid_size", &shift::BestPrice::getBidSize)
        .def("get_ask_price", &shift::BestPrice::getAskPrice)
        .def("get_ask_size", &shift::BestPrice::getAskSize)
        .def("get_global_bid_price", &shift::BestPrice::getGlobalBidPrice)
        .def("get_global_bid_size", &shift::BestPrice::getGlobalBidSize)
        .def("get_global_ask_price", &shift::BestPrice::getGlobalAskPrice)
        .def("get_global_ask_size", &shift::BestPrice::getGlobalAskSize)
        .def("get_local_bid_price", &shift::BestPrice::getLocalBidPrice)
        .def("get_local_bid_size", &shift::BestPrice::getLocalBidSize)
        .def("get_local_ask_price", &shift::BestPrice::getLocalAskPrice)
        .def("get_local_ask_size", &shift::BestPrice::getLocalAskSize);
}

} // BestPrice
