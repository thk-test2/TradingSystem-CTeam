
#include <string>
#include "gmock/gmock.h"

#include "auto_trading_system.cpp"

using namespace testing;

//MockDirver
class MockDriver : public StockBrokerDriverInterface {
public:
    MOCK_METHOD(void, login, (const std::string& id, const std::string& password), (override));
    MOCK_METHOD(void, buy, (const std::string& stockCode, int count, int price), (override));
    MOCK_METHOD(void, sell, (const std::string& stockCode, int count, int price), (override));
    MOCK_METHOD(int, currentPrice, (const std::string& stockCode), (override));
};

TEST(AutoTradingSystem, LoginFailWithWrongPassword) {
    MockDriver driver;
    AutoTradingSystem system{ &driver };

    bool actual = system.login("FAKE_USER", "WRONG_PASSWORD");

    EXPECT_EQ(false, actual);
}

TEST(AutoTradingSystem, LoginPASSWithCorrectPassword) {
    MockDriver driver;
    AutoTradingSystem system{ &driver };

    bool actual = system.login("FAKE_USER", "CORRECT_PASSWORD");

    EXPECT_EQ(true, actual);
}

TEST(AutoTradingSystem, BuySuccess) {
    MockDriver driver;
    AutoTradingSystem system{ &driver };

    bool actual = system.buy("TSLA", 999, 100);

    EXPECT_EQ(true, actual);
}

TEST(AutoTradingSystem, SellSuccess) {
    MockDriver driver;
    AutoTradingSystem system{ &driver };

    bool actual = system.sell("TSLA", 999, 100);

    EXPECT_EQ(true, actual);
}

TEST(AutoTradingSystem, GetPrice) {
    MockDriver driver;
    AutoTradingSystem system{ &driver };

    EXPECT_CALL(driver, currentPrice("TSLA"))
        .WillRepeatedly(Return(999));

    int actual = system.getPrice("TSLA");

    EXPECT_EQ(999, actual);
}

TEST(AutoTradingSystem, BuyNiceTimingFail) {
    MockDriver driver;
    AutoTradingSystem system{ &driver };

    EXPECT_CALL(driver, currentPrice("TSLA"))
        .Times(3)
        .WillOnce(Return(100))
        .WillOnce(Return(200))
        .WillOnce(Return(100));

    bool actual = system.buyNiceTiming("TSLA", 100000);

    EXPECT_EQ(false, actual);
}

TEST(AutoTradingSystem, BuyNiceTimingSuccess) {
    MockDriver driver;
    AutoTradingSystem system{ &driver };

    EXPECT_CALL(driver, currentPrice("TSLA"))
        .Times(3)
        .WillOnce(Return(100))
        .WillOnce(Return(200))
        .WillOnce(Return(300));

    bool actual = system.buyNiceTiming("TSLA", 100000);

    EXPECT_EQ(true, actual);
}

int main() {
    ::testing::InitGoogleMock();
    return RUN_ALL_TESTS();
}
