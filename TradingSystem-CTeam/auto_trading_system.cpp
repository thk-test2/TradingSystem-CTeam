#include <string>
#include <exception>

const int MIN_STOCK_PRICE = 5000;
const int MAX_STOCK_PRICE = 6000;

class DriverInterfacePointerException : public std::exception {
public:
    const char* what() const noexcept override {
        return "invalid DriverInterfacePointerException!";
    }
};

class PriceOutOfRangeException : public std::exception {
public:
    const char* what() const noexcept override {
        return "invalid PriceOutOfRangeException Price Range should be 5000~6000 !";
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
        if (!checkDriverIsSelected()) throw DriverInterfacePointerException();
        m_driver->login(id, password);
    }

    void buy(const std::string& stockCode, int count, int price) {
        if (!checkDriverIsSelected()) throw DriverInterfacePointerException();
        m_driver->buy(stockCode, count, price);
    }

    void sell(const std::string& stockCode, int count, int price) {
        if (!checkDriverIsSelected()) throw DriverInterfacePointerException();
        m_driver->sell(stockCode, count, price);
    }

    int getPrice(const std::string& stockCode) {
        if (!checkDriverIsSelected()) throw DriverInterfacePointerException();

        int price = m_driver->currentPrice(stockCode);

        //if (checkDriverIsValidPrice(price)) throw PriceOutOfRangeException();

        return price;
    }

    bool buyNiceTiming(const std::string& stockCode, int price) {
        return false;
    }

    bool sellNiceTiming(const std::string& stockCode, int price) {
        return false;
    }

private:
    bool checkDriverIsValidPrice(int price)
    {
        return (price >= MIN_STOCK_PRICE && price < MAX_STOCK_PRICE);
    }

    bool checkDriverIsSelected()
    {
        return m_driver != nullptr;
    }

    StockBrokerDriverInterface* m_driver;
};
