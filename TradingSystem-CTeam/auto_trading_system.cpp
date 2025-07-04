#include <string>
#include <exception>
#include <thread>
#include <chrono>
#include <vector>

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

    void login(const std::string& id, const std::string& password) {
        m_driver->login(id, password);
    }

    void buy(const std::string& stockCode, int count, int price) {
        m_driver->buy(stockCode, count, price);
    }

    void sell(const std::string& stockCode, int count, int price) {
        m_driver->sell(stockCode, count, price);
    }

    int getPrice(const std::string& stockCode) {
        if (!checkDriverIsSelected()) throw std::exception();

        return m_driver->currentPrice(stockCode);
    }

    bool buyNiceTiming(const std::string& stockCode, int price) {
        return false;
    }

    bool sellNiceTiming(const std::string& stockCode, int numOfStocks) {
        if (!checkDriverIsSelected()) throw std::exception();

        std::vector<int> prices = getPrice3Times(stockCode);

        if (isSellTiming(prices)) {
            this->sell(stockCode, numOfStocks, prices[2]);
            return true;
        }

        return false;
    }

private:
    bool checkDriverIsSelected()
    {
        return m_driver != nullptr;
    }

    std::vector<int> getPrice3Times(const std::string& stockCode)
    {
        std::vector<int> result;
        for (int i = 0; i < 3; i++) {
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            result.push_back(m_driver->currentPrice(stockCode));
        }
        return result;
    }

    bool isSellTiming(const std::vector<int>& prices) {
        if (prices[0] > prices[1]) {
            if (prices[1] > prices[2]) {
                return true;
            }
        }
        return false;
    }

    StockBrokerDriverInterface* m_driver;
};
