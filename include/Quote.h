#pragma once

#include "Common.h"

#include <string>

namespace Quote {

void bindPython(py::module& m)
{
    //! bind class
    py::class_<shift::Quote> QUOTE(m, "Quote");
    QUOTE //! bind constructor
        .def(py::init<std::string, double, double, int, std::string, std::string, std::string, std::string>(), py::arg("quoteID"), py::arg("bid_price"), py::arg("ask_price"), py::arg("size"), py::arg("destination"), py::arg("symbol"), py::arg("S2"), py::arg("traderID"));
    QUOTE //! bind property
        .def_readwrite("quoteID", &shift::Quote::quoteID)
        .def_readwrite("bid_price", &shift::Quote::bidPx)
        .def_readwrite("ask_price", &shift::Quote::askPx)
        .def_readwrite("size", &shift::Quote::size)
        .def_readwrite("destination", &shift::Quote::destination)
        .def_readwrite("symbol", &shift::Quote::symbol)
        .def_readwrite("S2", &shift::Quote::S2)
        .def_readwrite("traderID", &shift::Quote::traderID);

}
} // Quote

