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

    bool sell(const std::string& stockCode, int count, int price) {
        return false;
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

        std::vector<int> nums;

        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        nums.push_back(m_driver->currentPrice(stockCode));

        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        nums.push_back(m_driver->currentPrice(stockCode));

        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        nums.push_back(m_driver->currentPrice(stockCode));

        if (nums[0] > nums[1]) {
            if (nums[1] > nums[2]) {
                this->sell(stockCode, numOfStocks, nums[2]);
                return true;
            }
        }

        return false;
    }

private:
    bool checkDriverIsSelected()
    {
        return m_driver != nullptr;
    }

    StockBrokerDriverInterface* m_driver;
};
