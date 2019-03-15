#pragma once

#include "Common.h"

#include <pybind11/functional.h>

#include <map>
#include <string>
#include <unordered_map>
#include <vector>

class PythonClient;
class Trader;

class PythonClient
    : public shift::CoreClient {
public:
    PythonClient(Trader* t);
    PythonClient(const std::string& username, Trader* t);

    std::function<void(Trader*, const std::string&)> lastPriceUpdatedCb;
    std::function<void(Trader*, const std::string&)> executionReportReceivedCb;
    std::function<void(Trader*)> portfolioSummaryUpdatedCb;
    std::function<void(Trader*, const std::string&)> portfolioItemUpdatedCb;
    std::function<void(Trader*)> waitingListUpdatedCb;

    Trader* trader;

protected:
    virtual void receiveLastPrice(const std::string& symbol) override;
    virtual void receiveExecutionReport(const std::string& orderID) override;
    virtual void receivePortfolioSummary() override;
    virtual void receivePortfolioItem(const std::string& symbol) override;
    virtual void receiveWaitingList() override;

private:
};

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
            .def("submitCancellation", &Trader::submitCancellation, py::arg("order"))
            .def("getPortfolioSummary", &Trader::getPortfolioSummary)
            .def("getPortfolioItems", &Trader::getPortfolioItems)
            .def("getPortfolioItem", &Trader::getPortfolioItem, py::arg("symbol"))
            .def("getSubmittedOrdersSize", &Trader::getSubmittedOrdersSize)
            .def("getSubmittedOrders", &Trader::getSubmittedOrders)
            .def("getOrder", &Trader::getOrder, py::arg("orderID"))
            .def("getWaitingListSize", &Trader::getWaitingListSize)
            .def("getWaitingList", &Trader::getWaitingList)
            .def("cancelAllPendingOrders", &Trader::cancelAllPendingOrders)
            .def("getClosePrice", &Trader::getClosePrice, py::arg("symbol"), py::arg("buy"), py::arg("size"))
            .def("getLastPrice", &Trader::getLastPrice, py::arg("symbol"))
            .def("getLastSize", &Trader::getLastSize, py::arg("symbol"))
            .def("getLastTradeTime", &Trader::getLastTradeTime)
            .def("getBestPrice", &Trader::getBestPrice, py::arg("symbol"))
            .def("getOrderBook", &Trader::getOrderBook, py::arg("symbols"), py::arg("type"), py::arg("maxLevel") = 99)
            .def("getOrderBookWithDestination", &Trader::getOrderBookWithDestination, py::arg("symbols"), py::arg("type"))
            .def("getStockList", &Trader::getStockList)
            .def("requestCompanyNames", &Trader::requestCompanyNames)
            .def("getCompanyNames", &Trader::getCompanyNames)
            .def("getCompanyName", &Trader::getCompanyName, py::arg("symbol"))
            .def("requestSamplePrices", &Trader::requestSamplePrices, py::arg("symbols"), py::arg("samplingFrequency") = 1, py::arg("samplingWindow") = 31)
            .def("cancelSamplePricesRequest", &Trader::cancelSamplePricesRequest, py::arg("symbols"))
            .def("cancelAllSamplePricesRequests", &Trader::cancelAllSamplePricesRequests)
            .def("getSamplePricesSize", &Trader::getSamplePricesSize, py::arg("symbol"))
            .def("getSamplePrices", &Trader::getSamplePrices, py::arg("symbol"), py::arg("midPrices") = false)
            .def("getLogReturnsSize", &Trader::getLogReturnsSize, py::arg("symbol"))
            .def("getLogReturns", &Trader::getLogReturns, py::arg("symbol"), py::arg("midPrices") = false)
            .def("subOrderBook", &Trader::subOrderBook, py::arg("symbol"))
            .def("unsubOrderBook", &Trader::unsubOrderBook, py::arg("symbol"))
            .def("subAllOrderBook", &Trader::subAllOrderBook)
            .def("unsubAllOrderBook", &Trader::unsubAllOrderBook)
            .def("getSubscribedOrderBookList", &Trader::getSubscribedOrderBookList)
            .def("onLastPriceUpdated", &Trader::onLastPriceUpdated)
            .def("onPortfolioItemUpdated", &Trader::onPortfolioItemUpdated)
            .def("onPortfolioSummaryUpdated", &Trader::onPortfolioSummaryUpdated)
            .def("onWaitingListUpdated", &Trader::onWaitingListUpdated);
    }

    Trader();
    Trader(const std::string& username);
    ~Trader();

private:
    std::string getUsername();
    void setUsername(const std::string& username);

    bool connect(const std::string& cfgFile, const std::string& password);
    bool disconnect();
    bool isConnected();

    void submitOrder(const shift::Order& order);
    void submitCancellation(shift::Order order);

    // Portfolio methods
    shift::PortfolioSummary getPortfolioSummary();
    std::map<std::string, shift::PortfolioItem> getPortfolioItems();
    shift::PortfolioItem getPortfolioItem(const std::string& symbol);
    int getSubmittedOrdersSize();
    std::vector<shift::Order> getSubmittedOrders();
    shift::Order getOrder(const std::string& orderID);
    int getWaitingListSize();
    std::vector<shift::Order> getWaitingList();
    void cancelAllPendingOrders();

    // Price methods
    double getClosePrice(const std::string& symbol, bool buy, int size);
    double getLastPrice(const std::string& symbol);
    int getLastSize(const std::string& symbol);
    std::chrono::system_clock::time_point getLastTradeTime();

    // Order book methods
    shift::BestPrice getBestPrice(const std::string& symbol);
    std::vector<shift::OrderBookEntry> getOrderBook(const std::string& symbol, shift::OrderBook::Type type, int maxLevel);
    std::vector<shift::OrderBookEntry> getOrderBookWithDestination(const std::string& symbol, shift::OrderBook::Type type);

    // Symbols list and company names
    std::vector<std::string> getStockList();
    void requestCompanyNames();
    std::map<std::string, std::string> getCompanyNames();
    std::string getCompanyName(const std::string& symbol);

    // Sample prices
    bool requestSamplePrices(std::vector<std::string> symbols, double samplingFrequency, unsigned int samplingWindow);
    bool cancelSamplePricesRequest(const std::vector<std::string>& symbols);
    bool cancelAllSamplePricesRequests();
    int getSamplePricesSize(const std::string& symbol);
    std::list<double> getSamplePrices(const std::string& symbol, bool midPrices);
    int getLogReturnsSize(const std::string& symbol);
    std::list<double> getLogReturns(const std::string& symbol, bool midPrices);

    // Subscription methods
    bool subOrderBook(const std::string& symbol);
    bool unsubOrderBook(const std::string& symbol);
    bool subAllOrderBook();
    bool unsubAllOrderBook();
    std::vector<std::string> getSubscribedOrderBookList();

    // Callback methods
    void onLastPriceUpdated(const std::function<void(Trader*, const std::string&)>& cb);
    void onExecutionReportReceived(const std::function<void(Trader*, const std::string&)>& cb);
    void onPortfolioSummaryUpdated(const std::function<void(Trader*)>& cb);
    void onPortfolioItemUpdated(const std::function<void(Trader*, const std::string&)>& cb);
    void onWaitingListUpdated(const std::function<void(Trader*)>& cb);

private:
    shift::FIXInitiator& m_initiator;
    PythonClient* m_client;
};
