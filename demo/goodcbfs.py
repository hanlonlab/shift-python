# good callback functions/functors:


# on last price updated callbacks:

def last_price_updated_cb(trader, symbol):
    print(f"{symbol} Trade: {trader.getLastPrice(symbol):.2f}")


class LastPriceUpdatedCB(object):
    def __init__(self, stock_ticker, verbose=False):
        self.stock_ticker = stock_ticker
        self.verbose = verbose

    def __call__(self, trader, symbol):
        if self.verbose and symbol == self.stock_ticker:
            print(f"{symbol} Trade: {trader.getLastPrice(symbol):.2f}")


# on portfolio summary updated callbacks:

def portfolio_summary_updated_cb(trader):
    print(f"Buying Power: {trader.getPortfolioSummary().getTotalBP():.2f}")


class PortfolioSummaryUpdatedCB(object):
    def __init__(self, verbose=False):
        self.verbose = verbose

    def __call__(self, trader):
        if self.verbose:
            print(f"Buying Power: {trader.getPortfolioSummary().getTotalBP():.2f}")


# on portfolio item updated callbacks:

def portfolio_item_updated_cb(trader, symbol):
    print(f"{symbol} Shares: {trader.getPortfolioItem(symbol).getShares()}")


class PortfolioItemUpdatedCB(object):
    def __init__(self, stock_ticker, verbose=False):
        self.stock_ticker = stock_ticker
        self.verbose = verbose

    def __call__(self, trader, symbol):
        if self.verbose and symbol == self.stock_ticker:
            print(f"{symbol} Shares: {trader.getPortfolioItem(symbol).getShares()}")


# on waiting list updated callbacks:

def waiting_list_updated_cb(trader):
    if trader.getWaitingListSize() > 0:
        print("Waiting List:")
        curr_waiting_list = trader.getWaitingList()
        for order in curr_waiting_list:
            print("%6s\t%21s\t%7.2f\t\t%4d\t%36s\t%26s" %
                  (order.symbol, order.type, order.price, order.size, order.id, order.timestamp))
    else:
        print("Waiting List Empty!")


class WaitingListUpdatedCB(object):
    def __init__(self, verbose=False):
        self.verbose = verbose

    def __call__(self, trader):
        if self.verbose:
            if trader.getWaitingListSize() > 0:
                print("Waiting List:")
                curr_waiting_list = trader.getWaitingList()
                for order in curr_waiting_list:
                    print("%6s\t%21s\t%7.2f\t\t%4d\t%36s\t%26s" %
                          (order.symbol, order.type, order.price, order.size, order.id, order.timestamp))
            else:
                print("Waiting List Empty!")
