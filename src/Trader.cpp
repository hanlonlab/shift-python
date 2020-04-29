#include "Trader.h"

PythonClient::PythonClient(Trader* t)
    : trader { t }
{
}

PythonClient::PythonClient(std::string username, Trader* t)
    : shift::CoreClient { std::move(username) }
    , trader { t }
{
}

void PythonClient::receiveLastPrice(const std::string& symbol)
{
    if (lastPriceUpdatedCb) {
        lastPriceUpdatedCb(trader, symbol);
    }
}

void PythonClient::receiveExecution(const std::string& orderID)
{
    if (executionUpdatedCb) {
        executionUpdatedCb(trader, orderID);
    }
}

void PythonClient::receivePortfolioSummary()
{
    if (portfolioSummaryUpdatedCb) {
        portfolioSummaryUpdatedCb(trader);
    }
}

void PythonClient::receivePortfolioItem(const std::string& symbol)
{
    if (portfolioItemUpdatedCb) {
        portfolioItemUpdatedCb(trader, symbol);
    }
}

void PythonClient::receiveWaitingList()
{
    if (waitingListUpdatedCb) {
        waitingListUpdatedCb(trader);
    }
}

Trader::Trader()
    : m_initiator { shift::FIXInitiator::getInstance() }
    , m_client { new PythonClient(this) }
{
}

Trader::Trader(std::string username)
    : m_initiator { shift::FIXInitiator::getInstance() }
    , m_client { new PythonClient(std::move(username), this) }
{
}

Trader::~Trader()
{
    delete m_client;
}

auto Trader::getUsername() const -> const std::string&
{
    return m_client->getUsername();
}

void Trader::setUsername(const std::string& username)
{
    m_client->setUsername(username);
}

/*!
 * \brief Trader::connect Try to connect FixInitiator to the BrokerageCenter.
 * \param password Password
 * \return Success
 */
auto Trader::connect(const std::string& cfgFile, const std::string& password) -> bool
{
    if (isConnected()) {
        Log(Log::WARNING) << "Already connected.";
        return false;
    }

    try {
        m_initiator.connectBrokerageCenter(cfgFile, m_client, password);
        Log(Log::INFO) << "Connection established.";
    } catch (shift::ConnectionTimeoutError& e) {
        Log(Log::ERROR) << e.what();
        throw e;
    } catch (shift::IncorrectPasswordError& e) {
        Log(Log::ERROR) << e.what();
        throw e;
    }

    return true;
}

auto Trader::disconnect() -> bool
{
    if (!isConnected()) {
        Log(Log::ERROR) << "No connection established.";
        return false;
    }

    m_initiator.disconnectBrokerageCenter();
    Log(Log::INFO) << "Disconnected.";

    return true;
}

auto Trader::isConnected() -> bool
{
    return m_client->isConnected();
}

void Trader::submitOrder(const shift::Order& order)
{
    return m_client->submitOrder(order);
}

void Trader::submitCancellation(shift::Order order)
{
    return m_client->submitCancellation(order);
}

auto Trader::getPortfolioSummary() -> shift::PortfolioSummary
{
    return m_client->getPortfolioSummary();
}

auto Trader::getPortfolioItems() -> std::map<std::string, shift::PortfolioItem>
{
    return m_client->getPortfolioItems();
}

auto Trader::getPortfolioItem(const std::string& symbol) -> shift::PortfolioItem
{
    return m_client->getPortfolioItem(symbol);
}

auto Trader::getUnrealizedPL(const std::string& symbol) -> double
{
    return m_client->getUnrealizedPL(symbol);
}

auto Trader::getSubmittedOrdersSize() -> int
{
    return m_client->getSubmittedOrdersSize();
}

auto Trader::getSubmittedOrders() -> std::vector<shift::Order>
{
    return m_client->getSubmittedOrders();
}

auto Trader::getOrder(const std::string& orderID) -> shift::Order
{
    return m_client->getOrder(orderID);
}

auto Trader::getExecutedOrders(const std::string& orderID) -> std::vector<shift::Order>
{
    return m_client->getExecutedOrders(orderID);
}

auto Trader::getWaitingListSize() -> int
{
    return m_client->getWaitingListSize();
}

auto Trader::getWaitingList() -> std::vector<shift::Order>
{
    return m_client->getWaitingList();
}

void Trader::cancelAllPendingOrders()
{
    return m_client->cancelAllPendingOrders();
}

auto Trader::getClosePrice(const std::string& symbol, bool buy, int size) -> double
{
    return m_client->getClosePrice(symbol, buy, size);
}

auto Trader::getClosePrice(const std::string& symbol) -> double
{
    return m_client->getClosePrice(symbol);
}

auto Trader::getLastPrice(const std::string& symbol) -> double
{
    return m_client->getLastPrice(symbol);
}

auto Trader::getLastSize(const std::string& symbol) -> int
{
    return m_client->getLastSize(symbol);
}

auto Trader::getLastTradeTime() -> std::chrono::system_clock::time_point
{
    return m_client->getLastTradeTime();
}

auto Trader::getBestPrice(const std::string& symbol) -> shift::BestPrice
{
    return m_client->getBestPrice(symbol);
}

auto Trader::getOrderBook(const std::string& symbol, shift::OrderBook::Type type, int maxLevel) -> std::vector<shift::OrderBookEntry>
{
    return m_client->getOrderBook(symbol, type, maxLevel);
}

auto Trader::getOrderBookWithDestination(const std::string& symbol, shift::OrderBook::Type type) -> std::vector<shift::OrderBookEntry>
{
    return m_client->getOrderBookWithDestination(symbol, type);
}

auto Trader::getStockList() -> std::vector<std::string>
{
    return m_client->getStockList();
}

void Trader::requestCompanyNames()
{
    return m_client->requestCompanyNames();
}

auto Trader::getCompanyNames() -> std::map<std::string, std::string>
{
    return m_client->getCompanyNames();
}

auto Trader::getCompanyName(const std::string& symbol) -> std::string
{
    return m_client->getCompanyName(symbol);
}

auto Trader::requestSamplePrices(std::vector<std::string> symbols, double samplingFrequency, unsigned int samplingWindow) -> bool
{
    return m_client->requestSamplePrices(symbols, samplingFrequency, samplingWindow);
}

auto Trader::cancelSamplePricesRequest(const std::vector<std::string>& symbols) -> bool
{
    return m_client->cancelSamplePricesRequest(symbols);
}

auto Trader::cancelAllSamplePricesRequests() -> bool
{
    return m_client->cancelAllSamplePricesRequests();
}

auto Trader::getSamplePricesSize(const std::string& symbol) -> int
{
    return m_client->getSamplePricesSize(symbol);
}

auto Trader::getSamplePrices(const std::string& symbol, bool midPrices) -> std::list<double>
{
    return m_client->getSamplePrices(symbol, midPrices);
}

auto Trader::getLogReturnsSize(const std::string& symbol) -> int
{
    return m_client->getLogReturnsSize(symbol);
}

auto Trader::getLogReturns(const std::string& symbol, bool midPrices) -> std::list<double>
{
    return m_client->getLogReturns(symbol, midPrices);
}

auto Trader::subOrderBook(const std::string& symbol) -> bool
{
    return m_client->subOrderBook(symbol);
}

auto Trader::unsubOrderBook(const std::string& symbol) -> bool
{
    return m_client->unsubOrderBook(symbol);
}

auto Trader::subAllOrderBook() -> bool
{
    return m_client->subAllOrderBook();
}

auto Trader::unsubAllOrderBook() -> bool
{
    return m_client->unsubAllOrderBook();
}

auto Trader::getSubscribedOrderBookList() -> std::vector<std::string>
{
    return m_client->getSubscribedOrderBookList();
}

void Trader::onLastPriceUpdated(const std::function<void(Trader*, const std::string&)>& cb)
{
    m_client->lastPriceUpdatedCb = cb;
}

void Trader::onExecutionUpdated(const std::function<void(Trader*, const std::string&)>& cb)
{
    m_client->executionUpdatedCb = cb;
}

void Trader::onPortfolioSummaryUpdated(const std::function<void(Trader*)>& cb)
{
    m_client->portfolioSummaryUpdatedCb = cb;
}

void Trader::onPortfolioItemUpdated(const std::function<void(Trader*, const std::string&)>& cb)
{
    m_client->portfolioItemUpdatedCb = cb;
}

void Trader::onWaitingListUpdated(const std::function<void(Trader*)>& cb)
{
    m_client->waitingListUpdatedCb = cb;
}
