import shift
import sys
import time


def demo01(trader):

    limitBuy = shift.Order("AAPL", 1.00, 1, shift.Order.LIMIT_BUY)
    trader.submitOrder(limitBuy)

    return


def demo02(trader):

    aaplLimitBuy = shift.Order("AAPL", 1.00, 10, shift.Order.LIMIT_BUY)
    trader.submitOrder(aaplLimitBuy)

    msftLimitBuy = shift.Order("MSFT", 1.00, 10, shift.Order.LIMIT_BUY)
    trader.submitOrder(msftLimitBuy)

    return


def demo03(trader):

    print("Symbol\tPrice\tSize\tType\t\t\t\tID")
    for order in trader.getWaitingList():
        print("%s\t%5.2f\t%4d\t%s\t%s" %
              (order.symbol, order.price, order.size, order.type, order.id))

    return


def demo04(trader):

    print("Symbol\tPrice\tSize\tType\t\t\t\tID")
    for order in trader.getWaitingList():
        print("%s\t%5.2f\t%4d\t%s\t%s" %
              (order.symbol, order.price, order.size, order.type, order.id))

    print()

    print("Waiting list size: " + str(trader.getWaitingListSize()))
    print("Canceling all pending orders...", end=" ")

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


def demo05(trader):

    aaplMarketBuy = shift.Order("AAPL", 0.00, 1, shift.Order.MARKET_BUY)
    trader.submitOrder(aaplMarketBuy)

    msftMarketBuy = shift.Order("MSFT", 0.00, 1, shift.Order.MARKET_BUY)
    trader.submitOrder(msftMarketBuy)

    return


def demo06(trader):

    print("Buying Power\tTotal Shares\tTotal P&L")
    print("%12.2f\t%12d\t%9.2f" % (trader.getPortfolioSummary().totalBP,
                                   trader.getPortfolioSummary().totalShares,
                                   trader.getPortfolioSummary().totalPL))

    print()

    print("Symbol\tShares\t\tPrice\t\tP&L")
    for item in trader.getPortfolioItems().values():
        print("%s\t%6d\t%9.2f\t%7.2f" % (item.getSymbol(), item.getShares(),
                                         item.getPrice(), item.getPL()))

    return


def demo07(trader):

    aaplMarketSell = shift.Order("AAPL", 0.00, 1, shift.Order.MARKET_SELL)
    trader.submitOrder(aaplMarketSell)

    msftMarketSell = shift.Order("MSFT", 0.00, 1, shift.Order.MARKET_SELL)
    trader.submitOrder(msftMarketSell)

    return


def main(argv):
    # create trader object
    trader = shift.Trader("democlient")

    # connect and subscribe to all available stock orderbooks
    try:
        trader.connect("initiator.cfg", "password")
        trader.subAllOrderBook()
    except shift.IncorrectPassword as e:
        print(e)
    except shift.ConnectionTimeout as e:
        print(e)

    demo01(trader)
    # demo02(trader)
    # demo03(trader)
    # demo04(trader)
    # demo05(trader)
    # demo06(trader)
    # demo07(trader)

    # disconnect
    trader.disconnect()

    return


if __name__ == "__main__":
    main(sys.argv)
