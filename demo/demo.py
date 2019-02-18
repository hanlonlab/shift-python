import shift
import sys
import time


def demo01(trader):
    """
    This method submits a limit buy order by indicating order type, symbol, size, and limit price.
    :param trader:
    :return:
    """

    limit_buy = shift.Order(shift.Order.LIMIT_BUY, "AAPL", 1, 10.00)
    trader.submitOrder(limit_buy)

    return


def demo02(trader):
    """
    This method submits 2 limit buy orders by indicating order type, symbol, size, and limit price.
    :param trader:
    :return:
    """

    aapl_limit_buy = shift.Order(shift.Order.LIMIT_BUY, "AAPL", 10, 10.00)
    trader.submitOrder(aapl_limit_buy)

    xom_limit_buy = shift.Order(shift.Order.LIMIT_BUY, "XOM", 10, 10.00)
    trader.submitOrder(xom_limit_buy)

    return


def demo03(trader):
    """
    This method prints the local bid order book for corresponding symbols.
    :param trader:
    :return:
    """

    print("AAPL:")
    print("  Price\t\tSize\t  Dest\t\tTime")
    for order in trader.getOrderBook("AAPL", shift.OrderBookType.LOCAL_BID):
        print("%7.2f\t\t%4d\t%6s\t\t%19s" %
              (order.price, order.size, order.destination, order.time))

    print()

    print("XOM:")
    print("  Price\t\tSize\t  Dest\t\tTime")
    for order in trader.getOrderBook("XOM", shift.OrderBookType.LOCAL_BID):
        print("%7.2f\t\t%4d\t%6s\t\t%19s" %
              (order.price, order.size, order.destination, order.time))


def demo04(trader):
    """
    This method prints all current waiting orders information.
    :param trader:
    :return:
    """

    print("Symbol\t\t\t\t\t Type\t  Price\t\tSize\tID\t\t\t\t\t\t\t\t\t\tTimestamp")
    for order in trader.getWaitingList():
        print("%6s\t%21s\t%7.2f\t\t%4d\t%36s\t%26s" %
              (order.symbol, order.type, order.price, order.size, order.id, order.timestamp))

    return


def demo05(trader):
    """
    This method cancels all the orders in the waiting list.
    :param trader:
    :return:
    """

    print("Symbol\t\t\t\t\t Type\t  Price\t\tSize\tID\t\t\t\t\t\t\t\t\t\tTimestamp")
    for order in trader.getWaitingList():
        print("%6s\t%21s\t%7.2f\t\t%4d\t%36s\t%26s" %
              (order.symbol, order.type, order.price, order.size, order.id, order.timestamp))

    print()

    print("Waiting list size: " + str(trader.getWaitingListSize()))

    print("Canceling all pending orders...", end=" ")

    # trader.cancelAllPendingOrders() also works
    for order in trader.getWaitingList():
        if order.type == shift.Order.LIMIT_BUY:
            order.type = shift.Order.CANCEL_BID
        else:
            order.type = shift.Order.CANCEL_ASK
        trader.submitOrder(order)

    i = 0
    while trader.getWaitingListSize() > 0:
        i += 1
        print(i, end=" ")
        time.sleep(1)

    print()

    print("Waiting list size: " + str(trader.getWaitingListSize()))

    return


def demo06(trader):
    """
    This method shows how to submit market buy orders.
    :param trader:
    :return:
    """

    aapl_market_buy = shift.Order(shift.Order.MARKET_BUY, "AAPL", 1)
    trader.submitOrder(aapl_market_buy)

    xom_market_buy = shift.Order(shift.Order.MARKET_BUY, "XOM", 1)
    trader.submitOrder(xom_market_buy)

    return


def demo07(trader):
    """
    This method provides information on the structure of PortfolioSummary and PortfolioItem objects:
     getPortfolioSummary() returns a PortfolioSummary object with the following data:
     1. Total Buying Power (totalBP)
     2. Total Shares (totalShares)
     3. Total Realized Profit/Loss (totalRealizedPL)
     4. Timestamp of Last Update (timestamp)

     getPortfolioItems() returns a dictionary with "symbol" as keys and PortfolioItem as values, with each providing the following information:
     1. Symbol (getSymbol())
     2. Shares (getShares())
     3. Price (getPrice())
     4. Realized Profit/Loss (getRealizedPL())
     5. Timestamp of Last Update (getTimestamp())
    :param trader:
    :return:
    """

    print("Buying Power\tTotal Shares\tTotal P&L\tTimestamp")
    print("%12.2f\t%12d\t%9.2f\t%26s" % (trader.getPortfolioSummary().getTotalBP(),
                                         trader.getPortfolioSummary().getTotalShares(),
                                         trader.getPortfolioSummary().getTotalRealizedPL(),
                                         trader.getPortfolioSummary().getTimestamp()))

    print()

    print("Symbol\t\tShares\t\tPrice\t\tP&L\t\tTimestamp")
    for item in trader.getPortfolioItems().values():
        print("%6s\t\t%6d\t%9.2f\t%7.2f\t\t%26s" %
              (item.getSymbol(), item.getShares(), item.getPrice(), item.getRealizedPL(), item.getTimestamp()))

    return


def demo08(trader):
    """
    This method shows how to submit market sell orders.
    :param trader:
    :return:
    """

    aapl_market_sell = shift.Order(shift.Order.MARKET_SELL, "AAPL", 1)
    trader.submitOrder(aapl_market_sell)

    xom_market_sell = shift.Order(shift.Order.MARKET_SELL, "XOM", 1)
    trader.submitOrder(xom_market_sell)

    return


def demo09(trader):
    """
    This method prints all submitted orders information.
    :param trader:
    :return:
    """

    print("Symbol\t\t\t\t\t Type\t  Price\t\tSize\tID\t\t\t\t\t\t\t\t\t\tTimestamp")
    for order in trader.getSubmittedOrders():
        print("%6s\t%21s\t%7.2f\t\t%4d\t%36s\t%26s" %
              (order.symbol, order.type, order.price, order.size, order.id, order.timestamp))

    return


def demo10(trader):
    """
    This method prints the global bid order book for a corresponding symbol and type.
    :param trader:
    :return:
    """

    print("  Price\t\tSize\t  Dest\t\tTime")
    for order in trader.getOrderBook("AAPL", shift.OrderBookType.GLOBAL_BID, 5):
        print("%7.2f\t\t%4d\t%6s\t\t%19s" %
              (order.price, order.size, order.destination, order.time))


def main(argv):
    # create trader object
    trader = shift.Trader("democlient")

    # connect and subscribe to all available order books
    try:
        trader.connect("initiator.cfg", "password")
        trader.subAllOrderBook()
    except shift.IncorrectPassword as e:
        print(e)
    except shift.ConnectionTimeout as e:
        print(e)

    # demo01(trader)
    # demo02(trader)
    # demo03(trader)
    # demo04(trader)
    # demo05(trader)
    # demo06(trader)
    # demo07(trader)
    # demo08(trader)
    # demo09(trader)
    # demo10(trader)

    # disconnect
    trader.disconnect()

    return


if __name__ == "__main__":
    main(sys.argv)
