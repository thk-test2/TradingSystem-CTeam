#include "driver_interface.h"
#include "nemo_api.cpp"

using namespace std;

class NemoDriver : public StockBrokerDriverInterface {
public:
	void login(const string& ID, const string& password) override {
		nemoAPI.certification(ID, password);
	}
	void buy(const std::string& stockCode, int count, int price) {
		nemoAPI.purchasingStock(stockCode, price, count);
	}
	void sell(const std::string& stockCode, int count, int price) {
		nemoAPI.sellingStock(stockCode, count, price);
	}
	int currentPrice(const std::string& stockCode) {
		return nemoAPI.getMarketPrice(stockCode, 0);
	};

private:
	NemoAPI nemoAPI;
};