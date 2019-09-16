import shift

# good callback functions/functors:


# on last price updated callbacks:


def last_price_updated_cb(trader: shift.Trader, symbol: str):
    print(f"{symbol} Trade: {trader.get_last_price(symbol):.2f}")


class LastPriceUpdatedCB(object):
    def __init__(self, stock_ticker: str, verbose: bool = False):
        self.stock_ticker = stock_ticker
        self.verbose = verbose

    def __call__(self, trader: shift.Trader, symbol: str):
        if self.verbose and symbol == self.stock_ticker:
            print(f"{symbol} Trade: {trader.get_last_price(symbol):.2f}")


# on execution updated callbacks:


def execution_updated_cb(trader: shift.Trader, order_id: str):
    order = trader.get_order(order_id)
    if order.status == shift.Order.Status.FILLED:
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
    def __init__(self, verbose: bool = False):
        self.verbose = verbose

    def __call__(self, trader: shift.Trader, order_id: str):
        if self.verbose:
            order = trader.get_order(order_id)
            if order.status == shift.Order.Status.FILLED:
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


def portfolio_summary_updated_cb(trader: shift.Trader):
    print(f"Buying Power: {trader.get_portfolio_summary().get_total_bp():.2f}")


class PortfolioSummaryUpdatedCB(object):
    def __init__(self, verbose: bool = False):
        self.verbose = verbose

    def __call__(self, trader: shift.Trader):
        if self.verbose:
            print(f"Buying Power: {trader.get_portfolio_summary().get_total_bp():.2f}")


# on portfolio item updated callbacks:


def portfolio_item_updated_cb(trader: shift.Trader, symbol: str):
    print(f"{symbol} Shares: {trader.get_portfolio_item(symbol).get_shares()}")


class PortfolioItemUpdatedCB(object):
    def __init__(self, verbose: bool = False):
        self.verbose = verbose

    def __call__(self, trader: shift.Trader, symbol: str):
        if self.verbose:
            print(f"{symbol} Shares: {trader.get_portfolio_item(symbol).get_shares()}")


# on waiting list updated callbacks:


def waiting_list_updated_cb(trader: shift.Trader):
    if trader.get_waiting_list_size() > 0:
        waiting_list = trader.get_waiting_list()
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
    def __init__(self, verbose: bool = False):
        self.verbose = verbose

    def __call__(self, trader: shift.Trader):
        if self.verbose:
            if trader.get_waiting_list_size() > 0:
                waiting_list = trader.get_waiting_list()
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
