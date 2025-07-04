#pragma once
#include "auto_trading_system.cpp"
#include "kiwer_api.cpp"

using namespace std;

class KiwerDriver : public StockBrokerDriverInterface {
public:
	void login(const string& ID, const string& password) override {
		kiwerAPI.login(ID, password);
	}
	void buy(const string& stockCode, int count, int price) override {
		kiwerAPI.buy(stockCode, count, price);
	}
	void sell(const string& stockCode, int count, int price) override {
		kiwerAPI.sell(stockCode, count, price);
	}
	int currentPrice(const string& stockCode) override {
		return kiwerAPI.currentPrice(stockCode);
	}
private:
	KiwerAPI kiwerAPI;
};