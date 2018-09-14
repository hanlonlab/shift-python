#pragma once

#include "Common.h"

#include <string>

namespace Order {

void bindPython(py::module& m)
{
    //! Bind class
    py::class_<shift::Order> ORDER(m, "Order");
    ORDER //! Bind constructor
        .def(py::init<std::string, double, int, shift::Order::ORDER_TYPE>(), py::arg("symbol"), py::arg("price"), py::arg("size"), py::arg("type"));
    ORDER //! Bind property
        .def_property("symbol", &shift::Order::getSymbol, &shift::Order::setSymbol, py::return_value_policy::reference)
        .def_property("price", &shift::Order::getPrice, &shift::Order::setPrice, py::return_value_policy::reference)
        .def_property("size", &shift::Order::getSize, &shift::Order::setSize, py::return_value_policy::reference)
        .def_property("type", &shift::Order::getType, &shift::Order::setType, py::return_value_policy::reference)
        .def_property("id", &shift::Order::getID, &shift::Order::setID, py::return_value_policy::reference);

    //! Bind enum type
    py::enum_<shift::Order::ORDER_TYPE> ORDER_TYPE(ORDER, "OrderType");
    ORDER_TYPE
        .value("CANCEL_ASK", shift::Order::ORDER_TYPE::CANCEL_ASK)
        .value("CANCEL_BID", shift::Order::ORDER_TYPE::CANCEL_BID)
        .value("LIMIT_BUY", shift::Order::ORDER_TYPE::LIMIT_BUY)
        .value("LIMIT_SELL", shift::Order::ORDER_TYPE::LIMIT_SELL)
        .value("MARKET_BUY", shift::Order::ORDER_TYPE::MARKET_BUY)
        .value("MARKET_SELL", shift::Order::ORDER_TYPE::MARKET_SELL)
        .export_values();
}

} // Order
