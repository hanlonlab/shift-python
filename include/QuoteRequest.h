#pragma once

#include "Common.h"

#include <string>

namespace QuoteRequest {

void bindPython(py::module& m)
{
    //! bind class
    py::class_<shift::QuoteRequest> QUOTEREQUEST(m, "QuoteRequest");
    QUOTEREQUEST //! bind constructor
        .def(py::init<std::string, int, std::string, std::string, std::string>(), py::arg("quoteID"), py::arg("size"), py::arg("destination"), py::arg("symbol"), py::arg("S2"));
    QUOTEREQUEST //! bind property
        .def_readwrite("quoteID", &shift::QuoteRequest::quoteReqID)
        .def_readwrite("size", &shift::QuoteRequest::size)
        .def_readwrite("destination", &shift::QuoteRequest::destination)
        .def_readwrite("symbol", &shift::QuoteRequest::symbol)
        .def_readwrite("S2", &shift::QuoteRequest::S2)
        .def_readwrite("traderID", &shift::QuoteRequest::traderID);



}
} // QuoteRequest

