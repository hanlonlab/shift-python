import sys
import time
import math
import shift

def demo_07(trader: shift.Trader):
    """
    This method provides information on the structure of PortfolioSummary and PortfolioItem objects:
     get_portfolio_summary() returns a PortfolioSummary object with the following data:
     1. Total Buying Power (get_total_bp())
     2. Total Shares (get_total_shares())
     3. Total Realized Profit/Loss (get_total_realized_pl())
     4. Timestamp of Last Update (get_timestamp())

     get_portfolio_items() returns a dictionary with "smidbol" as keys and PortfolioItem as values,
     with each providing the following information:
     1. Smidbol (get_smidbol())
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

    print("Smidbol\t\tShares\t\tPrice\t\t  P&L\tTimestamp")
    for item in trader.get_portfolio_items().values():
        print(
            "%6s\t\t%6d\t%9.2f\t%9.2f\t%26s"
            % (
                item.get_smidbol(),
                item.get_shares(),
                item.get_price(),
                item.get_realized_pl(),
                item.get_timestamp(),
            )
        )

    return


'''
a = 100
b = 100
x = 50
(100+50)*(100-y) = 10000
150*100 - 150y = 10000
15000 - 150y = 10000
-150y = -5000
y = 5000/150 = 33.33...
'''
def utility_function(a, b):
        return a*b

    
def solver(a, b, quantity_in, asset_in):

    def f(quantity_out):     
        ux_val = a+quantity_in if asset_in == 'a' else a-quantity_out
        uy_val = b+quantity_in if asset_in == 'b' else b-quantity_out  
        return utility_function(ux_val, uy_val) - utility_function(a,b) 
    '''
    start with left = 0, y1 = b
    '''
    epsilon = 1e-3
    
    left = 0
    right = b if asset_in == 'a' else a
    mid = (left+right)/2
    left_val = f(left)
    right_val = f(right)
    mid_val = f(mid)
    
    while(not (abs(mid_val) < epsilon)):
    
        if(left_val*mid_val < 0):
            #root is on left side
            right = mid
            mid = (left+right)/2
            right_val = mid_val
            mid_val = f(mid)
        else:
            #root is on right side
            left = mid
            mid = (left+right)/2
            left_val = mid_val
            mid_val = f(mid)

    return mid
    
def solver(a, b, quantity_in, asset_in):

    def f(quantity_out):     
        ux_val = a+quantity_in if asset_in == 'a' else a-quantity_out
        uy_val = b+quantity_in if asset_in == 'b' else b-quantity_out  
        return utility_function(ux_val, uy_val) - utility_function(a,b) 
    '''
    start with left = 0, y1 = b
    '''
    epsilon = 1e-3
    
    left = -b if asset_in == 'a' else -a
    right = b if asset_in == 'a' else a
    mid = (left+right)/2
    left_val = f(left)
    right_val = f(right)
    mid_val = f(mid)
    
    while(not (abs(mid_val) < epsilon)):
     
        if(left_val*mid_val < 0):
            #root is on left side
            right = mid
            mid = (left+right)/2
            right_val = mid_val
            mid_val = f(mid)
        else:
            #root is on right side
            left = mid
            mid = (left+right)/2
            left_val = mid_val
            mid_val = f(mid)
        
    return mid

'''
another approaches: 
solver(100,100,1) => price for first share
solver(100,100,2) => average price for 2 shares
solver(100,100,3) => average price for 3 shares
best bid price per share : price for first share
next: (average price for 2 shares*2) - price for 1
next: (average price for 3 shares*3) - price for 2 
'''



one = solver(100, 100, 1, 'a')
two = solver(100+1, 100-one, 1, 'a')
three = solver(100+2, 100-one-two, 1, 'a')
four = solver(100+3, 100-one-two-three, 1, 'a')
five = solver(100+4, 100-four, 1, 'a')
six = solver(100+5, 100-five, 1, 'a')
seven = solver(100+6, 100-six, 1, 'a')
eight = solver(100+7, 100-seven, 1, 'a')


# create_orderbook()

class AMM:

    def __init__(self, trader, ticker):
        self.trader = trader
        self.shares_quantity = trader.get_portfolio_item(ticker).get_long_shares()
        # self.shares_quantity = 100
        print(self.shares_quantity)
        self.usd_quantity = self.trader.get_portfolio_summary().get_total_bp()
        # self.usd_quantity = 100
        print(self.usd_quantity)
        self.ticker = ticker

    def generate_orderbook(self, depth = 10):
        #generate bid prices for market maker to buy asset a with asset b
        q = 100
        prev_out = []
        bid_prices = []
        for i in range(depth):
            if self.usd_quantity-sum(prev_out) > 0:
                out = solver(self.shares_quantity+(i*q), self.usd_quantity-sum(prev_out), q, 'a')
                bid_prices.append(out/q)
                prev_out.append(out)
        
        print(bid_prices)
        
        
        #generate ask prices for market maker to sell asset a for asset b
        prev_in = []
        ask_prices = []
        for i in range(depth):
            if self.shares_quantity-(i*q) >= 0:
                #shares to give for 100 dollars
                in_amount = solver(self.shares_quantity-(i*q), self.usd_quantity+sum(prev_in), -q, 'a')
                in_amount = in_amount * -1
                ask_prices.append(in_amount/100)
                prev_in.append(in_amount)
        
        bid_orders = []
        for p in bid_prices:
            order = shift.Order(shift.Order.Type.LIMIT_BUY, self.ticker, 1, p)
            bid_orders.append(order)

        
        ask_orders = []
        
        for p in ask_prices:
            order = shift.Order(shift.Order.Type.LIMIT_SELL, self.ticker, 1, p)
            ask_orders.append(order)

        for o in bid_orders:
            print(f'{o.price:.2f}, {o.type}, {o.size}')
        for o in ask_orders:
            print(f'{o.price:.2f}, {o.type}, {o.size}')

        for o in bid_orders:
            self.trader.submit_order(o)
        for o in ask_orders:
            self.trader.submit_order(o)

    #order_ids needs to be consistently updated
    #queue of order_ids, and check the status only within the queue
    
    def check_order_executed(order_ids):
        while(True):
            for i in order_ids:
                e = trader.get_order(i).executed
                if e:
                    #kick out from queue
                    
                    #recalculate orderbook
                    self.generate_orderbook()
                else:
                    continue
            sleep(1)
                
    
        
    # def placeAMMTrade(self,OrderType,quantity, stock):
    #     print("Shares Quantity: "+ str(self.shares_quantity))
    #     print("Utility Function: " + str(self.utility_function))
    #     total_share_price = 0
    #     direction = 1 if OrderType == shift.Order.Type.LIMIT_BUY else -1
    #     new_shares_quantity = self.shares_quantity + (direction*quantity)
    #     print("New shares quantity: "+ str(new_shares_quantity))

    #     # this assumes there is no price impact from the trade
    #     # look into a numerical implementation
    #     # make the order book staggered by 1 
    #     total_share_price = (self.utility_function/new_shares_quantity) - self.shares_quantity
    #     new_usd_quantity = self.usd_quantity + (-1* direction * total_share_price)
    #     print("New usd quantity: " +str(new_usd_quantity))
    #     self.shares_quantity = new_shares_quantity
    #     self.usd_quantity = new_usd_quantity

    #     '''
    #     placeAMMTrade
    #     item = trader.get_portfolio_item(t)
    #     if item.get_long_shares() > 0:
    #         while(item.get_long_shares() > 0):
    #             order = shift.Order(shift.Order.Type.MARKET_SELL,t, int(item.get_long_shares() / 100))
    #             trader.submit_order(order)
    #             sleep(10)
    #             item = trader.get_portfolio_item(ticker)
    #         sleep(1)
    #     for order in trader.get_waiting_list():
    #     trader.submit_cancellation(order)
    #     order = trader.get_order("b3a60493-ad7b-4096-8271-e058fd05be7d")
    #     '''
    #     order = shift.Order(OrderType, stock, quantity, total_share_price)
    #     order_id = order.id
    #     # trackOrder()
    #     trader.submit_order(order)
    #     return order_id
    # only need to change the order book 
    # def trackOrder(order_id):
    #     order_id = trader.submit_order(order)
    #     order = trader.get_order(order_id)
    #     while(order.status != 'FILLED' or order.status != 'CANCELLED'):
    #         time.sleep(2)
    #     if order.status == 'CANCELLED':
    #         return
    #     orders_to_cancel = trader.get_waiting_list()
    #     for order in orders_to_cancel:
    #         trader.submit_cancellation(order)
    #         placeAMMTrade(order.Type, ) 

def createMarket(trader: shift.Trader):
    stock = "CS1"
    amm = AMM(trader, stock)
    amm.generate_orderbook()
     
    time.sleep(5)

def main(argv):
    # create trader object
    trader = shift.Trader("amm")
    print("App running")
    # connect and subscribe to all available order books
    try:
        trader.connect("initiator.cfg", "amm22")
        trader.sub_all_order_book()
    except shift.IncorrectPasswordError as e:
        print(e)
    except shift.ConnectionTimeoutError as e:
        print(e)
    time.sleep(5)
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

    createMarket(trader)

    # disconnect
    trader.disconnect()

    return


if __name__ == "__main__":
    main(sys.argv)


'''

Market price over time (calculate volatility)
Record inventory of MM
Test to see the effect of different constant functions


Look to add more market makers and fees
'''
