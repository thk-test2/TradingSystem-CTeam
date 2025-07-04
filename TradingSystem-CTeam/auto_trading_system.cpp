#include <string>
#include <exception>
#include <windows.h>

using std::string;

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
		int currentPrice;

        if (isBuyTiming(&currentPrice, stockCode)) {
			fullBuy(stockCode, price, currentPrice);
			return true;
        }
        return false;
    }

    bool sellNiceTiming(const std::string& stockCode, int price) {
        return false;
    }

private:
    bool checkDriverIsSelected()
    {
        return m_driver != nullptr;
    }

    bool isBuyTiming(int* currentPrice, const std::string& stockCode)
    {
        int previousPrice = 0;
        int increaseCount = 0;

        for (int checkCnt = 0; checkCnt < MAX_BUY_CHECK_COUNT; checkCnt++)
        {
            *currentPrice = m_driver->currentPrice(stockCode);
            if (checkCnt == 0) {
                previousPrice = *currentPrice;
            }
            else if (previousPrice < *currentPrice) {
                increaseCount++;
                previousPrice = *currentPrice;
            }
            else {
                return false;
            }
            Sleep(200);
        }
        return true;
    }

    void fullBuy(const std::string& stockCode, int price, int currentPrice) {
        int count = price / currentPrice;
        m_driver->buy(stockCode, count, currentPrice);
    }

    StockBrokerDriverInterface* m_driver;
	const int MAX_BUY_CHECK_COUNT = 3;
};
