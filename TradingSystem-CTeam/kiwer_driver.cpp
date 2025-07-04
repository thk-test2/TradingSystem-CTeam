#include "auto_trading_system.cpp"
#include "kiwer_api.cpp"

using namespace std;

class KiwerDriver : public StockBrokerDriverInterface {
public:
	void login(const string& ID, const string& password) override {
		kiwerAPI.login(ID, password);
	}
private:
	KiwerAPI kiwerAPI;
};