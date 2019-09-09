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


# on execution updated callbacks:


def execution_updated_cb(trader, order_id):
    order = trader.getOrder(order_id)
    if order.executed_size == order.size:
        price = order.executed_price
    else:
        price = order.price
    print("Report:")
    print(
        "%6s\t%16s\t%7.2f\t\t%4d\t\t%4d\t%36s\t%23s\t\t%26s"
        % (
            order.symbol,
            order.type,
            price,
            order.size,
            order.executed_size,
            order.id,
            order.status,
            order.timestamp,
        )
    )


class ExecutionUpdatedCB(object):
    def __init__(self, verbose=False):
        self.verbose = verbose

    def __call__(self, trader, order_id):
        if self.verbose:
            order = trader.getOrder(order_id)
            if order.executed_size == order.size:
                price = order.executed_price
            else:
                price = order.price
            print("Report:")
            print(
                "%6s\t%16s\t%7.2f\t\t%4d\t\t%4d\t%36s\t%23s\t\t%26s"
                % (
                    order.symbol,
                    order.type,
                    price,
                    order.size,
                    order.executed_size,
                    order.id,
                    order.status,
                    order.timestamp,
                )
            )


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
    def __init__(self, verbose=False):
        self.verbose = verbose

    def __call__(self, trader, symbol):
        if self.verbose:
            print(f"{symbol} Shares: {trader.getPortfolioItem(symbol).getShares()}")


# on waiting list updated callbacks:


def waiting_list_updated_cb(trader):
    if trader.getWaitingListSize() > 0:
        waiting_list = trader.getWaitingList()
        print("Waiting List:")
        for order in waiting_list:
            print(
                "%6s\t%21s\t%7.2f\t\t%4d\t\t%4d\t%36s\t%28s\t%26s"
                % (
                    order.symbol,
                    order.type,
                    order.price,
                    order.size,
                    order.executed_size,
                    order.id,
                    order.status,
                    order.timestamp,
                )
            )
    else:
        print("Waiting List Empty!")


class WaitingListUpdatedCB(object):
    def __init__(self, verbose=False):
        self.verbose = verbose

    def __call__(self, trader):
        if self.verbose:
            if trader.getWaitingListSize() > 0:
                waiting_list = trader.getWaitingList()
                print("Waiting List:")
                for order in waiting_list:
                    print(
                        "%6s\t%16s\t%7.2f\t\t%4d\t\t%4d\t%36s\t%23s\t\t%26s"
                        % (
                            order.symbol,
                            order.type,
                            order.price,
                            order.size,
                            order.executed_size,
                            order.id,
                            order.status,
                            order.timestamp,
                        )
                    )
            else:
                print("Waiting List Empty!")
