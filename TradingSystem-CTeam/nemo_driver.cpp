#include "auto_trading_system.cpp"
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
private:
	NemoAPI nemoAPI;
};