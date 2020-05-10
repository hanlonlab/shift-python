#pragma once

#include "Common.h"

#include <pybind11/functional.h>

#include <map>
#include <string>
#include <unordered_map>
#include <vector>

class PythonClient;
class Trader;

class PythonClient : public shift::CoreClient {
public:
    PythonClient(Trader* t);
    PythonClient(std::string username, Trader* t);

    std::function<void(Trader*, const std::string&)> lastPriceUpdatedCb;
    std::function<void(Trader*, const std::string&)> executionUpdatedCb;
    std::function<void(Trader*)> portfolioSummaryUpdatedCb;
    std::function<void(Trader*, const std::string&)> portfolioItemUpdatedCb;
    std::function<void(Trader*)> waitingListUpdatedCb;

    Trader* trader;

protected:
    virtual void receiveLastPrice(const std::string& symbol) override;
    virtual void receiveExecution(const std::string& orderID) override;
    virtual void receivePortfolioSummary() override;
    virtual void receivePortfolioItem(const std::string& symbol) override;
    virtual void receiveWaitingList() override;
};

class Trader {
public:
    static void bindPython(py::module& m)
    {
        //! bind class
        py::class_<Trader> TRADER(m, "Trader");
        TRADER //! bind constructor
            .def(py::init<const std::string&>(), py::arg("username"));
        TRADER //! bind property
            .def_property("username", &Trader::getUsername, &Trader::setUsername, py::return_value_policy::reference);
        TRADER //! bind function
            .def("connect", &Trader::connect, py::arg("cfg_file"), py::arg("password"))
            .def("disconnect", &Trader::disconnect)
            .def("is_connected", &Trader::isConnected)
            .def("submit_order", &Trader::submitOrder, py::arg("order"))
            .def("submit_cancellation", &Trader::submitCancellation, py::arg("order"))
            .def("get_portfolio_summary", &Trader::getPortfolioSummary)
            .def("get_portfolio_items", &Trader::getPortfolioItems)
            .def("get_portfolio_item", &Trader::getPortfolioItem, py::arg("symbol"))
            .def("get_unrealized_pl", &Trader::getUnrealizedPL, py::arg("symbol") = "")
            .def("get_submitted_orders_size", &Trader::getSubmittedOrdersSize)
            .def("get_submitted_orders", &Trader::getSubmittedOrders)
            .def("get_order", &Trader::getOrder, py::arg("order_id"))
            .def("get_executed_orders", &Trader::getExecutedOrders, py::arg("order_id"))
            .def("get_waiting_list_size", &Trader::getWaitingListSize)
            .def("get_waiting_list", &Trader::getWaitingList)
            .def("cancel_all_pending_orders", &Trader::cancelAllPendingOrders, py::arg("timeout") = 10)
            .def("get_close_price", py::overload_cast<const std::string&, bool, int>(&Trader::getClosePrice), py::arg("symbol"), py::arg("buy"), py::arg("size"))
            .def("get_close_price", py::overload_cast<const std::string&>(&Trader::getClosePrice), py::arg("symbol"))
            .def("get_last_price", &Trader::getLastPrice, py::arg("symbol"))
            .def("get_last_size", &Trader::getLastSize, py::arg("symbol"))
            .def("get_last_trade_time", &Trader::getLastTradeTime)
            .def("get_best_price", &Trader::getBestPrice, py::arg("symbol"))
            .def("get_order_book", &Trader::getOrderBook, py::arg("symbol"), py::arg("type"), py::arg("max_level") = 99)
            .def("get_order_book_with_destination", &Trader::getOrderBookWithDestination, py::arg("symbol"), py::arg("type"))
            .def("get_stock_list", &Trader::getStockList)
            .def("request_company_names", &Trader::requestCompanyNames)
            .def("get_company_names", &Trader::getCompanyNames)
            .def("get_company_name", &Trader::getCompanyName, py::arg("symbol"))
            .def("request_sample_prices", &Trader::requestSamplePrices, py::arg("symbols"), py::arg("sampling_frequency") = 1.0, py::arg("sampling_window") = 31)
            .def("cancel_sample_prices_request", &Trader::cancelSamplePricesRequest, py::arg("symbols"))
            .def("cancel_all_sample_prices_requests", &Trader::cancelAllSamplePricesRequests)
            .def("get_sample_prices_size", &Trader::getSamplePricesSize, py::arg("symbol"))
            .def("get_sample_prices", &Trader::getSamplePrices, py::arg("symbol"), py::arg("mid_prices") = false)
            .def("get_log_returns_size", &Trader::getLogReturnsSize, py::arg("symbol"))
            .def("get_log_returns", &Trader::getLogReturns, py::arg("symbol"), py::arg("mid_prices") = false)
            .def("sub_order_book", &Trader::subOrderBook, py::arg("symbol"))
            .def("unsub_order_book", &Trader::unsubOrderBook, py::arg("symbol"))
            .def("sub_all_order_book", &Trader::subAllOrderBook)
            .def("unsub_all_order_book", &Trader::unsubAllOrderBook)
            .def("get_subscribed_order_book_list", &Trader::getSubscribedOrderBookList)
            .def("on_last_price_updated", &Trader::onLastPriceUpdated, py::arg("cb"))
            .def("on_execution_updated", &Trader::onExecutionUpdated, py::arg("cb"))
            .def("on_portfolio_item_updated", &Trader::onPortfolioItemUpdated, py::arg("cb"))
            .def("on_portfolio_summary_updated", &Trader::onPortfolioSummaryUpdated, py::arg("cb"))
            .def("on_waiting_list_updated", &Trader::onWaitingListUpdated, py::arg("cb"));
    }

    Trader();
    Trader(std::string username);
    ~Trader();

private:
    auto getUsername() const -> const std::string&;
    void setUsername(const std::string& username);

    auto connect(const std::string& cfgFile, const std::string& password) -> bool;
    auto disconnect() -> bool;
    auto isConnected() -> bool;

    void submitOrder(const shift::Order& order);
    void submitCancellation(shift::Order order);

    // portfolio methods
    auto getPortfolioSummary() -> shift::PortfolioSummary;
    auto getPortfolioItems() -> std::map<std::string, shift::PortfolioItem>;
    auto getPortfolioItem(const std::string& symbol) -> shift::PortfolioItem;
    auto getUnrealizedPL(const std::string& symbol) -> double;
    auto getSubmittedOrdersSize() -> int;
    auto getSubmittedOrders() -> std::vector<shift::Order>;
    auto getOrder(const std::string& orderID) -> shift::Order;
    auto getExecutedOrders(const std::string& orderID) -> std::vector<shift::Order>;
    auto getWaitingListSize() -> int;
    auto getWaitingList() -> std::vector<shift::Order>;
    void cancelAllPendingOrders(int timeout);

    // price methods
    auto getClosePrice(const std::string& symbol, bool buy, int size) -> double;
    auto getClosePrice(const std::string& symbol) -> double;
    auto getLastPrice(const std::string& symbol) -> double;
    auto getLastSize(const std::string& symbol) -> int;
    auto getLastTradeTime() -> std::chrono::system_clock::time_point;

    // order book methods
    auto getBestPrice(const std::string& symbol) -> shift::BestPrice;
    auto getOrderBook(const std::string& symbol, shift::OrderBook::Type type, int maxLevel) -> std::vector<shift::OrderBookEntry>;
    auto getOrderBookWithDestination(const std::string& symbol, shift::OrderBook::Type type) -> std::vector<shift::OrderBookEntry>;

    // symbols list and company names
    auto getStockList() -> std::vector<std::string>;
    void requestCompanyNames();
    auto getCompanyNames() -> std::map<std::string, std::string>;
    auto getCompanyName(const std::string& symbol) -> std::string;

    // sample prices
    auto requestSamplePrices(std::vector<std::string> symbols, double samplingFrequencyS, int samplingWindow) -> bool;
    auto cancelSamplePricesRequest(const std::vector<std::string>& symbols) -> bool;
    auto cancelAllSamplePricesRequests() -> bool;
    auto getSamplePricesSize(const std::string& symbol) -> int;
    auto getSamplePrices(const std::string& symbol, bool midPrices) -> std::list<double>;
    auto getLogReturnsSize(const std::string& symbol) -> int;
    auto getLogReturns(const std::string& symbol, bool midPrices) -> std::list<double>;

    // subscription methods
    auto subOrderBook(const std::string& symbol) -> bool;
    auto unsubOrderBook(const std::string& symbol) -> bool;
    auto subAllOrderBook() -> bool;
    auto unsubAllOrderBook() -> bool;
    auto getSubscribedOrderBookList() -> std::vector<std::string>;

    // callback methods
    void onLastPriceUpdated(const std::function<void(Trader*, const std::string&)>& cb);
    void onExecutionUpdated(const std::function<void(Trader*, const std::string&)>& cb);
    void onPortfolioSummaryUpdated(const std::function<void(Trader*)>& cb);
    void onPortfolioItemUpdated(const std::function<void(Trader*, const std::string&)>& cb);
    void onWaitingListUpdated(const std::function<void(Trader*)>& cb);

private:
    shift::FIXInitiator& m_initiator;
    PythonClient* m_client;
};
