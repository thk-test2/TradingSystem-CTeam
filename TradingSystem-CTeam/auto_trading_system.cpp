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
        // 200ms �ֱ�� 3ȸ ������ Ȯ��
        // ������ �ö󰡴� �߼����, �� �ݾ��� �ִ��� ����Ͽ� �ֽ� ����
        // �������� ���� �������� �ż�
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
			Sleep(200); // 200ms ���

        }
        // �ż� ����
        if (increaseCount == MAX_BUY_CHECK_COUNT - 1) {
            // ������ ��� ����ϴ� �߼����
            int totalMoney = price; // �� �ݾ�
            int count = totalMoney / currentPrice; // ���� ������ �ֽ� ��
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
