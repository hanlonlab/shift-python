#pragma once

#include "Common.h"

#include <string>

namespace OrderBookEntry {

void bindPython(py::module& m)
{
    //! Bind class
    py::class_<shift::OrderBookEntry> ORDER_BOOK_ENTRY(m, "OrderBookEntry");
    ORDER_BOOK_ENTRY //! Bind constructor
        .def(py::init<std::string, double, double, std::string, double>(), py::arg("symbol"), py::arg("price"), py::arg("size"), py::arg("destination"), py::arg("time"));
    ORDER_BOOK_ENTRY //! Bind property
        .def_property("symbol", &shift::OrderBookEntry::getSymbol, &shift::OrderBookEntry::setSymbol, py::return_value_policy::reference)
        .def_property("price", &shift::OrderBookEntry::getPrice, &shift::OrderBookEntry::setPrice, py::return_value_policy::reference)
        .def_property("size", &shift::OrderBookEntry::getSize, &shift::OrderBookEntry::setSize, py::return_value_policy::reference)
        .def_property("destination", &shift::OrderBookEntry::getDestination, &shift::OrderBookEntry::setDestination, py::return_value_policy::reference)
        .def_property("time", &shift::OrderBookEntry::getTime, &shift::OrderBookEntry::setTime, py::return_value_policy::reference);
}

} // OrderBookEntry
