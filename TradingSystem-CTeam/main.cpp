
#include <string>
#include "gmock/gmock.h"

#include "auto_trading_system.cpp"
#include "kiwer_driver.cpp"

using namespace testing;

//MockDirver
class MockDriver : public StockBrokerDriverInterface {
public:
    MOCK_METHOD(void, login, (const std::string& id, const std::string& password), (override));
    MOCK_METHOD(void, buy, (const std::string& stockCode, int count, int price), (override));
    MOCK_METHOD(void, sell, (const std::string& stockCode, int count, int price), (override));
    MOCK_METHOD(int, currentPrice, (const std::string& stockCode), (override));
};

class AutoTradingSystemTestFixture : public ::testing::Test {
public:
    NiceMock<MockDriver> mockDriver;
    NiceMock<KiwerDriver> kiwerDriver;
    AutoTradingSystem system{ &mockDriver };
};

TEST_F(AutoTradingSystemTestFixture, SelectStockBrockerKiwer) {
    system.selectStockBrocker(&kiwerDriver);
}

TEST_F(AutoTradingSystemTestFixture, LoginPASS) {
    EXPECT_CALL(mockDriver, login(_, _))
		.Times(1);

    system.login("FAKE_USER", "FAKE_PASSWORD");
}

TEST_F(AutoTradingSystemTestFixture, BuySuccess) {
    EXPECT_CALL(mockDriver, buy(_, _, _))
        .Times(1);

    system.buy("TSLA", 999, 100);
}

TEST_F(AutoTradingSystemTestFixture, SellSuccess) {
    EXPECT_CALL(mockDriver, sell("TSLA", 999, 100))
        .Times(1);

    system.sell("TSLA", 999, 100);
}

TEST_F(AutoTradingSystemTestFixture, GetPrice) {
    EXPECT_CALL(mockDriver, currentPrice("TSLA"))
        .WillRepeatedly(Return(999));

    int actual = system.getPrice("TSLA");

    EXPECT_EQ(999, actual);
}

TEST_F(AutoTradingSystemTestFixture, BuyNiceTimingFail) {
    EXPECT_CALL(mockDriver, currentPrice("TSLA"))
        .Times(3)
        .WillOnce(Return(100))
        .WillOnce(Return(200))
        .WillOnce(Return(100));

    bool result = system.buyNiceTiming("TSLA", 100000);

	EXPECT_EQ(false, result);
}

TEST_F(AutoTradingSystemTestFixture, BuyNiceTimingSuccess) {
    EXPECT_CALL(mockDriver, currentPrice("TSLA"))
        .Times(3)
        .WillOnce(Return(100))
        .WillOnce(Return(200))
        .WillOnce(Return(300));

    bool result = system.buyNiceTiming("TSLA", 100000);

    EXPECT_EQ(true, result);
}

TEST_F(AutoTradingSystemTestFixture, SellNiceTimingFail) {
    EXPECT_CALL(mockDriver, currentPrice("TSLA"))
        .Times(3)
        .WillOnce(Return(300))
        .WillOnce(Return(200))
        .WillOnce(Return(300));

    bool actual = system.sellNiceTiming("TSLA", 10);

    EXPECT_EQ(false, actual);
}

TEST_F(AutoTradingSystemTestFixture, SellNiceTimingSuccess) {
    EXPECT_CALL(mockDriver, currentPrice("TSLA"))
        .Times(3)
        .WillOnce(Return(300))
        .WillOnce(Return(200))
        .WillOnce(Return(100));

    EXPECT_CALL(mockDriver, sell("TSLA", 10, 100))
        .Times(1);

    bool result = system.sellNiceTiming("TSLA", 10);

    EXPECT_EQ(true, result);
}

int main() {
    ::testing::InitGoogleMock();
    return RUN_ALL_TESTS();
}
