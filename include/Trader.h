#pragma once

#include "Common.h"

#include <map>
#include <string>
#include <unordered_map>
#include <vector>

class Trader;

class Trader {
public:
    static void bindPython(py::module& m)
    {
        //! Bind class
        py::class_<Trader> TRADER(m, "Trader");
        TRADER //! Bind constructor
            .def(py::init<const std::string&>(), py::arg("username"));
        TRADER //! Bind property
            .def_property("username", &Trader::getUsername, &Trader::setUsername, py::return_value_policy::reference);
        TRADER //! Bind function
            .def("connect", &Trader::connect, py::arg("cfgFile"), py::arg("password"))
            .def("disconnect", &Trader::disconnect)
            .def("isConnected", &Trader::isConnected)
            .def("submitOrder", &Trader::submitOrder, py::arg("order"))
            .def("getPortfolioSummary", &Trader::getPortfolioSummary)
            .def("getPortfolioItems", &Trader::getPortfolioItems)
            .def("getPortfolioItemBySymbol", &Trader::getPortfolioItemBySymbol, py::arg("symbol"))
            .def("getSubmittedOrdersSize", &Trader::getSubmittedOrdersSize)
            .def("getSubmittedOrders", &Trader::getSubmittedOrders)
            .def("getWaitingListSize", &Trader::getWaitingListSize)
            .def("getWaitingList", &Trader::getWaitingList)
            .def("cancelAllPendingOrders", &Trader::cancelAllPendingOrders)
            .def("getOpenPriceBySymbol", &Trader::getOpenPriceBySymbol, py::arg("symbol"))
            .def("getLastPriceBySymbol", &Trader::getLastPriceBySymbol, py::arg("symbol"))
            .def("getClosePriceBySymbol", &Trader::getClosePriceBySymbol, py::arg("symbol"), py::arg("buy"), py::arg("size"))
            .def("getBestPriceBySymbol", &Trader::getBestPriceBySymbol, py::arg("symbol"))
            .def("getOrderBookBySymbolAndType", &Trader::getOrderBook, py::arg("symbol"), py::arg("type"))
            .def("getOrderBookWithDestBySymbolAndType", &Trader::getOrderBookWithDestination, py::arg("symbol"), py::arg("type"))
            .def("getStockList", &Trader::getStockList)
            .def("requestCompanyNames", &Trader::requestCompanyNames)
            .def("getCompanyNames", &Trader::getCompanyNames)
            .def("getCompanyNameBySymbol", &Trader::getCompanyNameBySymbol, py::arg("symbol"))
            .def("requestSamplePrices", &Trader::requestSamplePrices, py::arg("symbol"), py::arg("samplingFrequency") = 1, py::arg("samplingWindow") = 31)
            .def("cancelSamplePricesRequest", &Trader::cancelSamplePricesRequest, py::arg("symbols"))
            .def("cancelAllSamplePricesRequests", &Trader::cancelAllSamplePricesRequests)
            .def("getSamplePricesSizeBySymbol", &Trader::getSamplePricesSizeBySymbol, py::arg("symbol"))
            .def("getSamplePricesBySymbol", &Trader::getSamplePricesBySymbol, py::arg("symbol"), py::arg("midPrices") = false)
            .def("getLogReturnsSizeBySymbol", &Trader::getLogReturnsSizeBySymbol, py::arg("symbol"))
            .def("getLogReturnsBySymbol", &Trader::getLogReturnsBySymbol, py::arg("symbol"), py::arg("midPrices") = false)
            .def("subOrderBook", &Trader::subOrderBook, py::arg("symbol"))
            .def("unsubOrderBook", &Trader::unsubOrderBook, py::arg("symbol"))
            .def("subAllOrderBook", &Trader::subAllOrderBook)
            .def("unsubAllOrderBook", &Trader::unsubAllOrderBook)
            .def("getSubscribedOrderBookList", &Trader::getSubscribedOrderBookList);
    }

    Trader();
    Trader(const std::string& username);
    ~Trader();

    std::string getUsername();
    void setUsername(const std::string& username);

    bool connect(const std::string& cfgFile, const std::string& password);
    bool disconnect();
    bool isConnected();

    void submitOrder(const shift::Order& order);

    // Portfolio methods
    shift::PortfolioSummary getPortfolioSummary();
    std::map<std::string, shift::PortfolioItem> getPortfolioItems();
    shift::PortfolioItem getPortfolioItemBySymbol(const std::string& symbol);
    int getSubmittedOrdersSize();
    std::vector<shift::Order> getSubmittedOrders();
    int getWaitingListSize();
    std::vector<shift::Order> getWaitingList();
    void cancelAllPendingOrders();

    // Price methods
    double getOpenPriceBySymbol(const std::string& symbol);
    double getLastPriceBySymbol(const std::string& symbol);
    double getClosePriceBySymbol(const std::string& symbol, bool buy, int size);

    // Order book methods
    shift::BestPrice getBestPriceBySymbol(const std::string& symbol);
    std::vector<shift::OrderBookEntry> getOrderBook(const std::string& symbol, char type);
    std::vector<shift::OrderBookEntry> getOrderBookWithDestination(const std::string& symbol, char type);

    // Symbols list and company names
    std::vector<std::string> getStockList();
    void requestCompanyNames();
    std::map<std::string, std::string> getCompanyNames();
    std::string getCompanyNameBySymbol(const std::string& symbol);

    // Sample prices
    bool requestSamplePrices(std::vector<std::string> symbols, double samplingFrequency, unsigned int samplingWindow);
    bool cancelSamplePricesRequest(const std::vector<std::string>& symbols);
    bool cancelAllSamplePricesRequests();
    int getSamplePricesSizeBySymbol(const std::string& symbol);
    std::list<double> getSamplePricesBySymbol(const std::string& symbol, bool midPrices);
    int getLogReturnsSizeBySymbol(const std::string& symbol);
    std::list<double> getLogReturnsBySymbol(const std::string& symbol, bool midPrices);

    // Subscription methods
    bool subOrderBook(const std::string& symbol);
    bool unsubOrderBook(const std::string& symbol);
    bool subAllOrderBook();
    bool unsubAllOrderBook();
    std::vector<std::string> getSubscribedOrderBookList();

private:
    shift::FIXInitiator& m_initiator;
    shift::CoreClient* m_client;
};
