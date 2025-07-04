#include "driver_interface.h"
#include "kiwer_api.cpp"

using namespace std;

class KiwerDriver : public StockBrokerDriverInterface {
public:
	void login(const string& ID, const string& password) override {
		kiwerAPI.login(ID, password);
	}
	void buy(const std::string& stockCode, int count, int price) {
		kiwerAPI.buy(stockCode, count, price);
	}
	void sell(const std::string& stockCode, int count, int price) {
		kiwerAPI.sell(stockCode, count, price);
	}
	int currentPrice(const std::string& stockCode) {
		return kiwerAPI.currentPrice(stockCode);
	};
private:
	KiwerAPI kiwerAPI;
};