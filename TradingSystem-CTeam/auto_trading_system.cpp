#include <iostream>
#include <string>

//Interface Class
class StockBrokerDriverInterface {
public:
    virtual void login(const std::string& id, const std::string& password) = 0;
    virtual void buy(const std::string& stockCode, int count, int price) = 0;
    virtual void sell(const std::string& stockCode, int count, int price) = 0;
    virtual int currentPrice(const std::string& stockCode) = 0;
};

class AutoTradingSystem {
public:
    AutoTradingSystem(StockBrokerDriverInterface* driver) : m_driver{ driver } {}

    void selectStockBrocker(std::string name) {}

    bool login(const std::string& id, const std::string& password) {
        return false;
    }

    void buy(const std::string& stockCode, int count, int price) {
        m_driver->buy(stockCode, count, price);
    }

    bool sell(const std::string& stockCode, int count, int price) {
        return false;
    }

    int getPrice(const std::string& stockCode) {
        return 0;
    }

    bool buyNiceTiming(const std::string& stockCode, int price) {
        return false;
    }

    bool sellNiceTiming(const std::string& stockCode, int price) {
        return false;
    }

private:
    StockBrokerDriverInterface* m_driver;
};
