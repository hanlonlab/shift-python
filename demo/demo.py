import sys
import time

import shift


def demo_01(trader: shift.Trader):
    """
    This method submits a limit buy order by indicating order type, symbol, size, and limit price.
    :param trader:
    :return:
    """

    limit_buy = shift.Order(shift.Order.Type.LIMIT_BUY, "AAPL", 1, 10.00)
    trader.submit_order(limit_buy)

    return


def demo_02(trader: shift.Trader):
    """
    This method submits 2 limit buy orders by indicating order type, symbol, size, and limit price.
    :param trader:
    :return:
    """

    aapl_lb = shift.Order(shift.Order.Type.LIMIT_BUY, "AAPL", 10, 10.00)
    trader.submit_order(aapl_lb)

    xom_lb = shift.Order(shift.Order.Type.LIMIT_BUY, "XOM", 10, 10.00)
    trader.submit_order(xom_lb)

    return


def demo_03(trader: shift.Trader):
    """
    This method prints the local bid order book for corresponding symbols.
    :param trader:
    :return:
    """

    print("AAPL:")
    print("  Price\t\tSize\t  Dest\t\tTime")
    for o in trader.get_order_book("AAPL", shift.OrderBookType.LOCAL_BID):
        print("%7.2f\t\t%4d\t%6s\t\t%19s" % (o.price, o.size, o.destination, o.time))

    print()

    print("XOM:")
    print("  Price\t\tSize\t  Dest\t\tTime")
    for o in trader.get_order_book("XOM", shift.OrderBookType.LOCAL_BID):
        print("%7.2f\t\t%4d\t%6s\t\t%19s" % (o.price, o.size, o.destination, o.time))


def demo_04(trader: shift.Trader):
    """
    This method prints all current waiting orders information.
    :param trader:
    :return:
    """

    print(
        "Symbol\t\t\t\tType\t  Price\t\tSize\tExecuted\tID\t\t\t\t\t\t\t\t\t\t\t\t\t\t Status\t\tTimestamp"
    )
    for o in trader.get_waiting_list():
        print(
            "%6s\t%16s\t%7.2f\t\t%4d\t\t%4d\t%36s\t%23s\t\t%26s"
            % (
                o.symbol,
                o.type,
                o.price,
                o.size,
                o.executed_size,
                o.id,
                o.status,
                o.timestamp,
            )
        )

    return


def demo_05(trader: shift.Trader):
    """
    This method cancels all the orders in the waiting list.
    :param trader:
    :return:
    """

    print(
        "Symbol\t\t\t\tType\t  Price\t\tSize\tExecuted\tID\t\t\t\t\t\t\t\t\t\t\t\t\t\t Status\t\tTimestamp"
    )
    for o in trader.get_waiting_list():
        print(
            "%6s\t%16s\t%7.2f\t\t%4d\t\t%4d\t%36s\t%23s\t\t%26s"
            % (
                o.symbol,
                o.type,
                o.price,
                o.size,
                o.executed_size,
                o.id,
                o.status,
                o.timestamp,
            )
        )

    print()

    print("Waiting list size: " + str(trader.get_waiting_list_size()))

    print("Canceling all pending orders...", end=" ")

    # trader.cancel_all_pending_orders() also works
    for o in trader.get_waiting_list():
        trader.submit_cancellation(o)

    i = 0
    while trader.get_waiting_list_size() > 0:
        i += 1
        print(i, end=" ")
        time.sleep(1)

    print()

    print("Waiting list size: " + str(trader.get_waiting_list_size()))

    return


def demo_06(trader: shift.Trader):
    """
    This method shows how to submit market buy orders.
    :param trader:
    :return:
    """

    aapl_mb = shift.Order(shift.Order.Type.MARKET_BUY, "AAPL", 1)
    trader.submit_order(aapl_mb)

    xom_mb = shift.Order(shift.Order.Type.MARKET_BUY, "XOM", 1)
    trader.submit_order(xom_mb)

    return


def demo_07(trader: shift.Trader):
    """
    This method provides information on the structure of PortfolioSummary and PortfolioItem objects:
     get_portfolio_summary() returns a PortfolioSummary object with the following data:
     1. Total Buying Power (get_total_bp())
     2. Total Shares (get_total_shares())
     3. Total Realized Profit/Loss (get_total_realized_pl())
     4. Timestamp of Last Update (get_timestamp())

     get_portfolio_items() returns a dictionary with "symbol" as keys and PortfolioItem as values,
     with each providing the following information:
     1. Symbol (get_symbol())
     2. Shares (get_shares())
     3. Price (get_price())
     4. Realized Profit/Loss (get_realized_pl())
     5. Timestamp of Last Update (get_timestamp())
    :param trader:
    :return:
    """

    print("Buying Power\tTotal Shares\tTotal P&L\tTimestamp")
    print(
        "%12.2f\t%12d\t%9.2f\t%26s"
        % (
            trader.get_portfolio_summary().get_total_bp(),
            trader.get_portfolio_summary().get_total_shares(),
            trader.get_portfolio_summary().get_total_realized_pl(),
            trader.get_portfolio_summary().get_timestamp(),
        )
    )

    print()

    print("Symbol\t\tShares\t\tPrice\t\t  P&L\tTimestamp")
    for item in trader.get_portfolio_items().values():
        print(
            "%6s\t\t%6d\t%9.2f\t%9.2f\t%26s"
            % (
                item.get_symbol(),
                item.get_shares(),
                item.get_price(),
                item.get_realized_pl(),
                item.get_timestamp(),
            )
        )

    return


def demo_08(trader: shift.Trader):
    """
    This method shows how to submit market sell orders.
    :param trader:
    :return:
    """

    aapl_ms = shift.Order(shift.Order.Type.MARKET_SELL, "AAPL", 1)
    trader.submit_order(aapl_ms)

    xom_ms = shift.Order(shift.Order.Type.MARKET_SELL, "XOM", 1)
    trader.submit_order(xom_ms)

    return


def demo_09(trader: shift.Trader):
    """
    This method prints all submitted orders information.
    :param trader:
    :return:
    """

    print(
        "Symbol\t\t\t\tType\t  Price\t\tSize\tExecuted\tID\t\t\t\t\t\t\t\t\t\t\t\t\t\t Status\t\tTimestamp"
    )
    for o in trader.get_submitted_orders():
        if o.status == shift.Order.Status.FILLED:
            price = o.executed_price
        else:
            price = o.price
        print(
            "%6s\t%16s\t%7.2f\t\t%4d\t\t%4d\t%36s\t%23s\t\t%26s"
            % (
                o.symbol,
                o.type,
                price,
                o.size,
                o.executed_size,
                o.id,
                o.status,
                o.timestamp,
            )
        )

    return


def demo_10(trader: shift.Trader):
    """
    This method prints the global bid order book for a corresponding symbol and type.
    :param trader:
    :return:
    """

    print("  Price\t\tSize\t  Dest\t\tTime")
    for o in trader.get_order_book("AAPL", shift.OrderBookType.GLOBAL_BID, 5):
        print("%7.2f\t\t%4d\t%6s\t\t%19s" % (o.price, o.size, o.destination, o.time))


def main(argv):
    # create trader object
    trader = shift.Trader("democlient")

    # connect and subscribe to all available order books
    try:
        trader.connect("initiator.cfg", "password")
        trader.sub_all_order_book()
    except shift.IncorrectPasswordError as e:
        print(e)
    except shift.ConnectionTimeoutError as e:
        print(e)

    # demo_01(trader)
    # demo_02(trader)
    # demo_03(trader)
    # demo_04(trader)
    # demo_05(trader)
    # demo_06(trader)
    # demo_07(trader)
    # demo_08(trader)
    # demo_09(trader)
    # demo_10(trader)

    # disconnect
    trader.disconnect()

    return


if __name__ == "__main__":
    main(sys.argv)
