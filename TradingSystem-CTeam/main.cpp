
#include <string>
#include "gmock/gmock.h"

using namespace testing;

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

//TEST(StockBroker, SelectStockBrokerKiwer) {
//    StockBrocker sb;
//
//    sb.selectStockBrocker("kiwer");
//    std::string actual = sb.getStockBrocker();
//
//    EXPECT_EQ("kiwer", actual);
//}
//
//TEST(StockBroker, SelectStockBrokerNemo) {
//    StockBrocker sb;
//
//    sb.selectStockBrocker("nemo");
//    std::string actual = sb.getStockBrocker();
//
//    EXPECT_EQ("nemo", actual);
//}

TEST(StockBroker, LoginFailWithWrongPassword) {
    MockDriver driver;

    driver.login("FAKE_USER", "WRONG_PASSWORD");
}

TEST(StockBroker, LoginKiwerPASSWithCorrectPassword) {
    MockDriver driver;

    driver.login("FAKE_USER", "CORRECT_PASSWORD");
}

TEST(StockBroker, BuySuccess) {
    MockDriver driver;

    driver.buy("TSLA", 999, 100);
}

TEST(StockBroker, SellSuccess) {
    MockDriver driver;

    driver.sell("TSLA", 999, 50);
}

TEST(StockBroker, CurrentPrice) {
    MockDriver driver;

    EXPECT_CALL(driver, currentPrice("TSLA"))
        .WillRepeatedly(Return(999));

    int actual = driver.currentPrice("TSLA");

    EXPECT_EQ(999, actual);
}

int main() {
    ::testing::InitGoogleMock();
    return RUN_ALL_TESTS();
}
