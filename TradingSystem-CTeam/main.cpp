
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

int main() {
    ::testing::InitGoogleMock();
    return RUN_ALL_TESTS();
}
