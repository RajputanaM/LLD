#include <bits/stdc++.h>
using namespace std;
 
struct Order {
    int clientId;
    int quantity;
    double price;
 
    Order(int c, int q, double p)
        : clientId(c), quantity(q), price(p) {}
};
 
struct BuyComparator {
    bool operator()(const Order& a, const Order& b) {
        return a.price < b.price;
    }
};
 
struct SellComparator {
    bool operator()(const Order& a, const Order& b) {
        return a.price > b.price;
    }
};
 
class ShippingYard {
private:
    int totalContainers = 0; 
    int availableContainers = 0; 

public:
    void addContainers(int count) {
        totalContainers += count;
        availableContainers += count; 
        cout << "Added " << count << " containers\n";
    }

    bool removeContainers(int count) {
        if (availableContainers < count) 
            return false;

        availableContainers -= count; 
        return true;
    }

    int getAvailable() const {
        return availableContainers; 
    }
};;
 
class OrderBook {
private:
    priority_queue<Order, vector<Order>, greater<Order>> buyOrders; 
    priority_queue<Order> sellOrders; 
    vector<string> transactions;

public:
    void addBuyOrder(const Order& order) {
        buyOrders.push(order);
        cout << "Buy order placed: price " << order.price
             << ", qty " << order.quantity << endl;
    }

    void addSellOrder(const Order& order) {
        sellOrders.push(order);
        cout << "Sell order placed: price " << order.price
             << ", qty " << order.quantity << endl;
    }

    bool hasMatch() const {
        return !buyOrders.empty() && !sellOrders.empty()
            && buyOrders.top().price >= sellOrders.top().price;
    }

    Order getBestBuy() { return buyOrders.top(); }
    Order getBestSell() { return sellOrders.top(); }

    void popBuy() { buyOrders.pop(); }
    void popSell() { sellOrders.pop(); }

    void logTransaction(const string& tx) {
        transactions.push_back(tx);
        cout << tx << endl;
    }
};;
 
class MatchingEngine {
private:
    ShippingYard& yard;
    OrderBook& orderBook;
 
public:
    MatchingEngine(ShippingYard& y, OrderBook& ob)
        : yard(y), orderBook(ob) {}
 
    void processTrades() {
        while (orderBook.hasMatch()) {
            Order buy = orderBook.getBestBuy();
            Order sell = orderBook.getBestSell();
 
            int tradeQty = min(buy.quantity, sell.quantity);
 
            if (!yard.removeContainers(tradeQty)) {
                cout << "Not enough containers available\n";
                break;
            }
 
            orderBook.popBuy();
            orderBook.popSell();
 
            string tx = "Transaction: "
                        + to_string(tradeQty)
                        + " containers at price "
                        + to_string(sell.price);
 
            orderBook.logTransaction(tx);
        }
    }
};
 
int main() {
    ShippingYard yard;
    OrderBook orderBook;
    MatchingEngine engine(yard, orderBook);
 
    yard.addContainers(100);
 
    orderBook.addSellOrder(Order(1, 10, 50));
    orderBook.addBuyOrder(Order(2, 10, 55));
    orderBook.addBuyOrder(Order(3, 5, 52));
 
    engine.processTrades();
 
    return 0;
}
