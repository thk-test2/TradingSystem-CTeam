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

    void buyNiceTiming(string stockCode, int price) {
        // 200ms 주기로 3회 가격을 확인
        // 가격이 올라가는 추세라면, 총 금액을 최대한 사용하여 주식 구매
        // 마지막에 읽은 가격으로 매수
		int currentPrice = 0;
		int previousPrice = 0;
		int increaseCount = 0;
        for (int checkCnt = 0; checkCnt < MAX_BUY_CHECK_COUNT; checkCnt++)
        {
			currentPrice = m_driver->currentPrice(stockCode);
            if (checkCnt == 0) {
				previousPrice = currentPrice;
            }
            else if (previousPrice < currentPrice) {
				increaseCount++;
                previousPrice = currentPrice;
			}
			Sleep(200); // 200ms 대기

        }
        // 매수 로직
        if (increaseCount == MAX_BUY_CHECK_COUNT - 1) {
            // 가격이 계속 상승하는 추세라면
            int totalMoney = price; // 총 금액
            int count = totalMoney / currentPrice; // 구매 가능한 주식 수
            if (count > 0) {
                m_driver->buy(stockCode, count, currentPrice);
            }
        }
    }

    bool sellNiceTiming(const std::string& stockCode, int price) {
        return false;
    }

private:
    bool checkDriverIsSelected()
    {
        return m_driver != nullptr;
    }

    StockBrokerDriverInterface* m_driver;
	const int MAX_BUY_CHECK_COUNT = 3;
};
