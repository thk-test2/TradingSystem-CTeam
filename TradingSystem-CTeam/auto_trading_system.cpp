#pragma once

#include <string>
#include <exception>
#include <thread>
#include <chrono>
#include <vector>
#include <windows.h>
#include "driver_interface.h"
#include "kiwer_driver.cpp"
#include "nemo_driver.cpp"

class DriverNullPointerException : public std::exception {
public:
    const char* what() const noexcept override {
        return "invalid DriverNullPointerException - NULL Pointer!";
    }
};

class ValidPriceException : public std::exception {
public:
    const char* what() const noexcept override {
        return "invalid ValidPriceException - Price Range should be 5000~6000 !";
    }
};

class AutoTradingSystem {
public:
    AutoTradingSystem(StockBrokerDriverInterface* driver) : m_driver{ driver } {}

    void selectStockBroker(std::string name) {
        if (name == "kiwer") {
            m_driver = new KiwerDriver();
        }
        else if (name == "nemo") {
            m_driver = new NemoDriver();
        }
        else {
            throw std::invalid_argument("Unknown broker");
        }
    }

    void login(const std::string& id, const std::string& password) {
        if (isDriverNullPointer()) throw DriverNullPointerException();
        m_driver->login(id, password);
    }

    void buy(const std::string& stockCode, int count, int price) {
        if (isDriverNullPointer()) throw DriverNullPointerException();
        m_driver->buy(stockCode, count, price);
    }

    void sell(const std::string& stockCode, int count, int price) {
        if (isDriverNullPointer()) throw DriverNullPointerException();
        m_driver->sell(stockCode, count, price);
    }

    int getPrice(const std::string& stockCode) {
        if (isDriverNullPointer()) throw DriverNullPointerException();

        int price = m_driver->currentPrice(stockCode);

        //if (isValidPrice(price)) throw ValidPriceException();

        return price;
    }

    bool buyNiceTiming(const std::string& stockCode, int price) {
		int currentPrice;

        if (isBuyTiming(&currentPrice, stockCode)) {
			fullBuy(stockCode, price, currentPrice);
			return true;
        }
        return false;
    }

    bool sellNiceTiming(const std::string& stockCode, int numOfStocks) {
        if (isDriverNullPointer()) throw std::exception();

        int order_price = 0;
        if (!isSellTimingAndGetOrderPrice(stockCode, order_price)) {
            return false;
        }
        this->sell(stockCode, numOfStocks, order_price);
        return true;
    }

private:
    StockBrokerDriverInterface* m_driver = nullptr;

    const int MAX_BUY_CHECK_COUNT = 3;
    const int MIN_STOCK_PRICE = 5000;
    const int MAX_STOCK_PRICE = 6000;

    bool isValidPrice(int price) {
        return (price >= MIN_STOCK_PRICE && price < MAX_STOCK_PRICE);
    }

    bool isDriverNullPointer() {
        return m_driver == nullptr;
    }

    bool isSellTimingAndGetOrderPrice(const std::string& stockCode, int& order_price) {
        int next_price = m_driver->currentPrice(stockCode);
        int prev_price;
        for (int i = 0; i < 2; i++) {
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            prev_price = next_price;
            next_price = m_driver->currentPrice(stockCode);
            if (prev_price <= next_price) return false;
        }
        order_price = next_price;
        return true;
    }

    bool isBuyTiming(int* currentPrice, const std::string& stockCode) {
        int previousPrice = 0;
        int increaseCount = 0;

        for (int checkCnt = 0; checkCnt < MAX_BUY_CHECK_COUNT; checkCnt++) {
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
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
        return true;
    }

    void fullBuy(const std::string& stockCode, int price, int currentPrice) {
        int count = price / currentPrice;
        m_driver->buy(stockCode, count, currentPrice);
    }
};
