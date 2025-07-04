#include <string>
#include <exception>
#include <thread>
#include <chrono>
#include <vector>

const int MIN_STOCK_PRICE = 5000;
const int MAX_STOCK_PRICE = 6000;

class DriverNullPointerException : public std::exception {
public:
    const char* what() const noexcept override {
        return "invalid DriverNullPointerException - NULL Pointer!";
    }
};

class ValidPriceException : public std::exception {
public:
    const char* what() const noexcept override {
        return "invalid ValidPriceException - Price Range should be 5000~6000 !";
    }
};

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
        if (isDriverNullPointer()) throw DriverNullPointerException();
        m_driver->login(id, password);
    }

    void buy(const std::string& stockCode, int count, int price) {
        if (isDriverNullPointer()) throw DriverNullPointerException();
        m_driver->buy(stockCode, count, price);
    }

    void sell(const std::string& stockCode, int count, int price) {
        if (isDriverNullPointer()) throw DriverNullPointerException();
        m_driver->sell(stockCode, count, price);
    }

    int getPrice(const std::string& stockCode) {
        if (isDriverNullPointer()) throw DriverNullPointerException();

        int price = m_driver->currentPrice(stockCode);

        //if (isValidPrice(price)) throw ValidPriceException();

        return price;
    }

    bool buyNiceTiming(const std::string& stockCode, int price) {
        return false;
    }

    bool sellNiceTiming(const std::string& stockCode, int numOfStocks) {
        if (isDriverNullPointer()) throw std::exception();

        int order_price= 0 ;
        if (! isSellTimingAndGetOrderPrice(stockCode, order_price)) {
            return false;
        }
        this->sell(stockCode, numOfStocks, order_price);
        return true;
    }

private:
    bool isValidPrice(int price)
    {
        return (price >= MIN_STOCK_PRICE && price < MAX_STOCK_PRICE);
    }

    bool isDriverNullPointer()
    {
        return m_driver == nullptr;
    }

    bool isSellTimingAndGetOrderPrice(const std::string& stockCode, int& order_price) {
        int next_price = m_driver->currentPrice(stockCode);
        int prev_price;
        for (int i = 0; i < 2; i++) {
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            prev_price = next_price;
            next_price = m_driver->currentPrice(stockCode);
            if (prev_price <= next_price) return false;
        }
        order_price = next_price;
        return true;
    }

    StockBrokerDriverInterface* m_driver;
};
