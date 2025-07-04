
#include <string>
#include "gmock/gmock.h"

//Interface Class
class StockBrokerDriverInterface {
public:
    virtual void login(const std::string& id, const std::string& password) = 0;
    virtual void buy(const std::string& stockCode, int count, int price) = 0;
    virtual void sell(const std::string& stockCode, int count, int price) = 0;
    virtual int currentPrice(const std::string& stockCode) = 0;
};

//MockDirver
class MockDriver : public StockBrokerDriverInterface {
public:
    MOCK_METHOD(void, login, (const std::string& id, const std::string& password), (override));
    MOCK_METHOD(void, buy, (const std::string& stockCode, int count, int price), (override));
    MOCK_METHOD(void, sell, (const std::string& stockCode, int count, int price), (override));
    MOCK_METHOD(int, currentPrice, (const std::string& stockCode), (override));
};

TEST(StockBroker, SelectStockBrokerKiwer) {
    StockBrocker sb;

    sb.selectStockBrocker("kiwer");
    std::string actual = sb.getStockBrocker();

    EXPECT_EQ("kiwer", actual);
}

TEST(StockBroker, SelectStockBrokerNemo) {
    StockBrocker sb;

    sb.selectStockBrocker("nemo");
    std::string actual = sb.getStockBrocker();

    EXPECT_EQ("nemo", actual);
}

TEST(StockBroker, LoginFailWithWrongPassword) {
    StockBrocker sb;

    bool actual = sb.login("FAKE_USER", "WRONG_PASSWORD");

    EXPECT_EQ(false, actual);
}

TEST(StockBroker, LoginPASSWithCorrectPassword) {
    StockBrocker sb;

    bool actual = sb.login("FAKE_USER", "CORRECT_PASSWORD");

    EXPECT_EQ(true, actual);
}

TEST(StockBroker, BuySuccess) {
    StockBrocker sb;

    bool actual = sb.buy("TSLA", 999, 100);

    EXPECT_EQ(true, actual);
}

TEST(StockBroker, SellSuccess) {
    StockBrocker sb;

    bool actual = sb.sell("TSLA", 9999, 50);

    EXPECT_EQ(true, actual);
}

int main() {
    ::testing::InitGoogleMock();
    return RUN_ALL_TESTS();
}
