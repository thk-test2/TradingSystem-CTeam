#pragma once
#include "auto_trading_system.cpp"
#include "nemo_api.cpp"

using namespace std;

class NemoDriver : public StockBrokerDriverInterface {
public:
	void login(const string& ID, const string& password) override {
		nemoAPI.certification(ID, password);
	}
	void buy(const string& stockCode, int count, int price) override {
		nemoAPI.purchasingStock(stockCode, price, count);
	}
	void sell(const string& stockCode, int count, int price) override {
		nemoAPI.sellingStock(stockCode, price, count);
	}
	int currentPrice(const string& stockCode) override {
		return nemoAPI.getMarketPrice(stockCode, 1);
	}
private:
	NemoAPI nemoAPI;
};