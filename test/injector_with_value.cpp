#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <injector/injector.hpp>

using ::testing::SizeIs;

class Base
{
public:
    virtual int foo() = 0;

    virtual ~Base() = default;
};

class Derived : public Base
{
public:
    int foo() override
    {
        return 20;
    }
};

TEST(InjectorWithValue, AddValueAsDervivedFromBaseClassToInjector) {
    auto value = std::make_shared<Derived>();

    injector::Injector injector;
    injector.add<Base, Derived>(value);

    auto res = injector.get<Base>();

    EXPECT_EQ(res->foo(), 20);
    EXPECT_EQ(res, value);
}

TEST(InjectorWithValue, AddValueAsGivenTypeToInjector) {
    auto value = std::make_shared<Derived>();

    injector::Injector injector;
    injector.add<Derived>(value);

    auto res = injector.get<Derived>();

    EXPECT_EQ(res->foo(), 20);
    EXPECT_EQ(res, value);
}

TEST(InjectorWithValue, TryAddValueThatAlearyHasBeenAdded) {
    auto value = std::make_shared<Derived>();

    injector::Injector injector;
    injector.try_add<Base, Derived>(value);
    injector.try_add<Base, Derived>(value);

    auto registrations = injector.get<std::vector<std::shared_ptr<Base>>>();

    ASSERT_THAT(registrations, SizeIs(1));
}