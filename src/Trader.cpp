#include "Trader.h"

PythonClient::PythonClient(Trader* t)
    : shift::CoreClient()
    , trader(t)
{

}

PythonClient::PythonClient(const std::string &username, Trader* t)
    : shift::CoreClient(username)
    , trader(t)
{

}

void PythonClient::receiveCandlestickData(const std::string &symbol, double open, double high, double low, double close, const std::string &timestamp)
{
    if(candleDataUpdatedCb )
        candleDataUpdatedCb(trader, symbol, open, high, low, close, timestamp);
}

void PythonClient::receiveLastPrice(const std::string &symbol)
{
    if(lastPriceUpdatedCb)
        lastPriceUpdatedCb(trader, symbol);
}

void PythonClient::receivePortfolio(const std::string &symbol)
{
    if(portfolioUpdatedCb)
        portfolioUpdatedCb(trader, symbol);
}

void PythonClient::receiveWaitingList()
{
    if(waitingListUpdatedCb)
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
    } catch (shift::ConnectionTimeout e) {
        Log(Log::ERRO) << e.what();
        throw e;
    } catch (shift::IncorrectPassword e) {
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
    return m_client->getPortfolioItemBySymbol(symbol);
}

int Trader::getSubmittedOrdersSize()
{
    return m_client->getSubmittedOrdersSize();
}

std::vector<shift::Order> Trader::getSubmittedOrders()
{
    return m_client->getSubmittedOrders();
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

double Trader::getLastPrice(const std::string& symbol)
{
    return m_client->getLastPriceBySymbol(symbol);
}

double Trader::getClosePrice(const std::string& symbol, bool buy, int size)
{
    return m_client->getClosePriceBySymbol(symbol, buy, size);
}

shift::BestPrice Trader::getBestPrice(const std::string& symbol)
{
    return m_client->getBestPriceBySymbol(symbol);
}

std::vector<shift::OrderBookEntry> Trader::getOrderBook(const std::string& symbol, shift::OrderBook::Type type)
{
    return m_client->getOrderBook(symbol, type);
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
    return m_client->getCompanyNameBySymbol(symbol);
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
    return m_client->getSamplePricesSizeBySymbol(symbol);
}

std::list<double> Trader::getSamplePrices(const std::string& symbol, bool midPrices)
{
    return m_client->getSamplePricesBySymbol(symbol, midPrices);
}

int Trader::getLogReturnsSize(const std::string& symbol)
{
    return m_client->getLogReturnsSizeBySymbol(symbol);
}

std::list<double> Trader::getLogReturns(const std::string& symbol, bool midPrices)
{
    return m_client->getLogReturnsBySymbol(symbol, midPrices);
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

void Trader::onSetCandleDataUpdated(const std::function<void (Trader *, const std::string &, double, double, double, double, const std::string &)> &cb)
{
    m_client->candleDataUpdatedCb = cb;
}

void Trader::onSetLastPriceUpdated(const std::function<void(Trader*, const std::string&)>& cb)
{
    m_client->lastPriceUpdatedCb = cb;
}

void Trader::onSetPortfolioUpdated(const std::function<void(Trader*, const std::string &)> &cb)
{
    m_client->portfolioUpdatedCb = cb;
}

void Trader::onSetWaitingListUpdated(const std::function<void(Trader *)> &cb)
{
    m_client->waitingListUpdatedCb = cb;
}


