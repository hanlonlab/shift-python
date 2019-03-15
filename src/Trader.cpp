#include "Trader.h"

PythonClient::PythonClient(Trader* t)
    : trader(t)
{
}

PythonClient::PythonClient(const std::string& username, Trader* t)
    : shift::CoreClient(username)
    , trader(t)
{
}

void PythonClient::receiveLastPrice(const std::string& symbol)
{
    if (lastPriceUpdatedCb)
        lastPriceUpdatedCb(trader, symbol);
}

void PythonClient::receiveExecutionReport(const std::string& orderID)
{
    if (executionReportReceivedCb)
        executionReportReceivedCb(trader, orderID);
}

void PythonClient::receivePortfolioSummary()
{
    if (portfolioSummaryUpdatedCb)
        portfolioSummaryUpdatedCb(trader);
}

void PythonClient::receivePortfolioItem(const std::string& symbol)
{
    if (portfolioItemUpdatedCb)
        portfolioItemUpdatedCb(trader, symbol);
}

void PythonClient::receiveWaitingList()
{
    if (waitingListUpdatedCb)
        waitingListUpdatedCb(trader);
}

Trader::Trader()
    : m_initiator(shift::FIXInitiator::getInstance())
    , m_client(new PythonClient(this))
{
}

Trader::Trader(const std::string& username)
    : m_initiator(shift::FIXInitiator::getInstance())
    , m_client(new PythonClient(username, this))
{
}

Trader::~Trader()
{
    delete m_client;
}

std::string Trader::getUsername()
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
bool Trader::connect(const std::string& cfgFile, const std::string& password)
{
    if (isConnected()) {
        Log(Log::WARN) << "Already connected.";
        return false;
    }

    try {
        m_initiator.connectBrokerageCenter(cfgFile, m_client, password);
        Log(Log::INFO) << "Connection established.";
    } catch (shift::ConnectionTimeout& e) {
        Log(Log::ERRO) << e.what();
        throw e;
    } catch (shift::IncorrectPassword& e) {
        Log(Log::ERRO) << e.what();
        throw e;
    }

    return true;
}

bool Trader::disconnect()
{
    if (!isConnected()) {
        Log(Log::ERRO) << "No connection established.";
        return false;
    }

    m_initiator.disconnectBrokerageCenter();
    Log(Log::INFO) << "Disconnected.";

    return true;
}

bool Trader::isConnected()
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

shift::PortfolioSummary Trader::getPortfolioSummary()
{
    return m_client->getPortfolioSummary();
}

std::map<std::string, shift::PortfolioItem> Trader::getPortfolioItems()
{
    return m_client->getPortfolioItems();
}

shift::PortfolioItem Trader::getPortfolioItem(const std::string& symbol)
{
    return m_client->getPortfolioItem(symbol);
}

int Trader::getSubmittedOrdersSize()
{
    return m_client->getSubmittedOrdersSize();
}

std::vector<shift::Order> Trader::getSubmittedOrders()
{
    return m_client->getSubmittedOrders();
}

shift::Order Trader::getOrder(const std::string& orderID)
{
    return m_client->getOrder(orderID);
}

int Trader::getWaitingListSize()
{
    return m_client->getWaitingListSize();
}

std::vector<shift::Order> Trader::getWaitingList()
{
    return m_client->getWaitingList();
}

void Trader::cancelAllPendingOrders()
{
    return m_client->cancelAllPendingOrders();
}

double Trader::getClosePrice(const std::string& symbol, bool buy, int size)
{
    return m_client->getClosePrice(symbol, buy, size);
}

double Trader::getLastPrice(const std::string& symbol)
{
    return m_client->getLastPrice(symbol);
}

int Trader::getLastSize(const std::string& symbol)
{
    return m_client->getLastSize(symbol);
}

std::chrono::system_clock::time_point Trader::getLastTradeTime()
{
    return m_client->getLastTradeTime();
}

shift::BestPrice Trader::getBestPrice(const std::string& symbol)
{
    return m_client->getBestPrice(symbol);
}

std::vector<shift::OrderBookEntry> Trader::getOrderBook(const std::string& symbol, shift::OrderBook::Type type, int maxLevel)
{
    return m_client->getOrderBook(symbol, type, maxLevel);
}

std::vector<shift::OrderBookEntry> Trader::getOrderBookWithDestination(const std::string& symbol, shift::OrderBook::Type type)
{
    return m_client->getOrderBookWithDestination(symbol, type);
}

std::vector<std::string> Trader::getStockList()
{
    return m_client->getStockList();
}

void Trader::requestCompanyNames()
{
    return m_client->requestCompanyNames();
}

std::map<std::string, std::string> Trader::getCompanyNames()
{
    return m_client->getCompanyNames();
}

std::string Trader::getCompanyName(const std::string& symbol)
{
    return m_client->getCompanyName(symbol);
}

bool Trader::requestSamplePrices(std::vector<std::string> symbols, double samplingFrequency, unsigned int samplingWindow)
{
    return m_client->requestSamplePrices(symbols, samplingFrequency, samplingWindow);
}

bool Trader::cancelSamplePricesRequest(const std::vector<std::string>& symbols)
{
    return m_client->cancelSamplePricesRequest(symbols);
}

bool Trader::cancelAllSamplePricesRequests()
{
    return m_client->cancelAllSamplePricesRequests();
}

int Trader::getSamplePricesSize(const std::string& symbol)
{
    return m_client->getSamplePricesSize(symbol);
}

std::list<double> Trader::getSamplePrices(const std::string& symbol, bool midPrices)
{
    return m_client->getSamplePrices(symbol, midPrices);
}

int Trader::getLogReturnsSize(const std::string& symbol)
{
    return m_client->getLogReturnsSize(symbol);
}

std::list<double> Trader::getLogReturns(const std::string& symbol, bool midPrices)
{
    return m_client->getLogReturns(symbol, midPrices);
}

bool Trader::subOrderBook(const std::string& symbol)
{
    return m_client->subOrderBook(symbol);
}

bool Trader::unsubOrderBook(const std::string& symbol)
{
    return m_client->unsubOrderBook(symbol);
}

bool Trader::subAllOrderBook()
{
    return m_client->subAllOrderBook();
}

bool Trader::unsubAllOrderBook()
{
    return m_client->unsubAllOrderBook();
}

std::vector<std::string> Trader::getSubscribedOrderBookList()
{
    return m_client->getSubscribedOrderBookList();
}

void Trader::onLastPriceUpdated(const std::function<void(Trader*, const std::string&)>& cb)
{
    m_client->lastPriceUpdatedCb = cb;
}

void Trader::onExecutionReportReceived(const std::function<void(Trader*, const std::string&)>& cb)
{
    m_client->executionReportReceivedCb = cb;
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
