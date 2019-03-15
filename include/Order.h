#pragma once

#include "Common.h"

#include <string>

namespace Order {

void bindPython(py::module& m)
{
    //! Bind class
    py::class_<shift::Order> ORDER(m, "Order");
    ORDER //! Bind constructor
        .def(py::init<shift::Order::Type, std::string, int, double, std::string>(), py::arg("type"), py::arg("symbol"), py::arg("size"), py::arg("price") = 0.0, py::arg("id") = "");
    ORDER //! Bind property
        .def_property("type", &shift::Order::getType, &shift::Order::setType, py::return_value_policy::reference)
        .def_property("symbol", &shift::Order::getSymbol, &shift::Order::setSymbol, py::return_value_policy::reference)
        .def_property("size", &shift::Order::getSize, &shift::Order::setSize, py::return_value_policy::reference)
        .def_property("price", &shift::Order::getPrice, &shift::Order::setPrice, py::return_value_policy::reference)
        .def_property("id", &shift::Order::getID, &shift::Order::setID, py::return_value_policy::reference)
        .def_property("status", &shift::Order::getStatus, &shift::Order::setStatus, py::return_value_policy::reference)
        .def_property("timestamp", &shift::Order::getTimestamp, &shift::Order::setTimestamp, py::return_value_policy::reference);

    //! Bind enum
    py::enum_<shift::Order::Type> Type(ORDER, "OrderType");
    Type
        .value("LIMIT_BUY", shift::Order::Type::LIMIT_BUY)
        .value("LIMIT_SELL", shift::Order::Type::LIMIT_SELL)
        .value("MARKET_BUY", shift::Order::Type::MARKET_BUY)
        .value("MARKET_SELL", shift::Order::Type::MARKET_SELL)
        .value("CANCEL_BID", shift::Order::Type::CANCEL_BID)
        .value("CANCEL_ASK", shift::Order::Type::CANCEL_ASK)
        .export_values();

    //! Bind enum
    py::enum_<shift::Order::Status> Status(ORDER, "OrderStatus");
    Status
        .value("PENDING_NEW", shift::Order::Status::PENDING_NEW)
        .value("NEW", shift::Order::Status::NEW)
        .value("PARTIALLY_FILLED", shift::Order::Status::PARTIALLY_FILLED)
        .value("FILLED", shift::Order::Status::FILLED)
        .value("CANCELED", shift::Order::Status::CANCELED)
        .value("PENDING_CANCEL", shift::Order::Status::PENDING_CANCEL)
        .value("REJECTED", shift::Order::Status::REJECTED)
        .export_values();
}

} // Order
