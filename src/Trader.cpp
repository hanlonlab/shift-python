#include "Trader.h"

Trader::Trader()
    : m_initiator(shift::FIXInitiator::getInstance())
    , m_client(new shift::CoreClient())
{
}

Trader::Trader(const std::string& username)
    : m_initiator(shift::FIXInitiator::getInstance())
    , m_client(new shift::CoreClient(username))
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

shift::PortfolioItem Trader::getPortfolioItemBySymbol(const std::string& symbol)
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

double Trader::getOpenPriceBySymbol(const std::string& symbol)
{
    return m_client->getOpenPriceBySymbol(symbol);
}

double Trader::getLastPriceBySymbol(const std::string& symbol)
{
    return m_client->getLastPriceBySymbol(symbol);
}

double Trader::getClosePriceBySymbol(const std::string& symbol, bool buy, int size)
{
    return m_client->getClosePriceBySymbol(symbol, buy, size);
}

shift::BestPrice Trader::getBestPriceBySymbol(const std::string& symbol)
{
    return m_client->getBestPriceBySymbol(symbol);
}

std::vector<shift::OrderBookEntry> Trader::getOrderBook(const std::string& symbol, char type)
{
    return m_client->getOrderBook(symbol, type);
}

std::vector<shift::OrderBookEntry> Trader::getOrderBookWithDestination(const std::string& symbol, char type)
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

std::string Trader::getCompanyNameBySymbol(const std::string& symbol)
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

int Trader::getSamplePricesSizeBySymbol(const std::string& symbol)
{
    return m_client->getSamplePricesSizeBySymbol(symbol);
}

std::list<double> Trader::getSamplePricesBySymbol(const std::string& symbol, bool midPrices)
{
    return m_client->getSamplePricesBySymbol(symbol, midPrices);
}

int Trader::getLogReturnsSizeBySymbol(const std::string& symbol)
{
    return m_client->getLogReturnsSizeBySymbol(symbol);
}

std::list<double> Trader::getLogReturnsBySymbol(const std::string& symbol, bool midPrices)
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
