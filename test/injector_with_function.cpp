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

TEST(InjectorWithFunction, CreatingDerivedObjectFromFunctionFactory) {
    int call_count = 0;

    auto factory = [&] {
        call_count += 1;
        return std::make_shared<Derived>();
    };

    injector::Injector injector;
    injector.add<Base, Derived>(factory);

    auto res1 = injector.get<Base>();
    auto res2 = injector.get<Base>();
    auto res3 = injector.get<Base>();

    EXPECT_EQ(res1->foo(), 20);
    EXPECT_NE(res1, res2);
    EXPECT_NE(res1, res3);
    EXPECT_NE(res2, res3);
    EXPECT_EQ(call_count, 3);
}

TEST(InjectorWithFunction, CreatingDerivedObjectWithSingletonFunctionFactory) {
    int call_count = 0;

    auto factory = [&] {
        call_count += 1;
        return std::make_shared<Derived>();
    };

    injector::Injector injector;
    injector.add_singleton<Base, Derived>(factory);

    auto res1 = injector.get<Base>();
    auto res2 = injector.get<Base>();
    auto res3 = injector.get<Base>();

    EXPECT_EQ(res1->foo(), 20);
    EXPECT_EQ(res1, res2);
    EXPECT_EQ(res1, res3);
    EXPECT_EQ(res2, res3);
    EXPECT_EQ(call_count, 1);
}

TEST(InjectorWithFunction, ObjectCreationThatReturnsNull) {
    auto factory = [] {
        return nullptr;
    };

    injector::Injector injector;
    injector.add<Base, Derived>(factory);

    ASSERT_THROW(injector.get<Base>(), injector::ComponentCreationException);
}

TEST(InjectorWithFunction, TryAddingExistingFactoryFunction) {
    auto factory = [] {
        return std::make_shared<Derived>();
    };

    injector::Injector injector;
    injector.try_add<Base, Derived>(factory);
    injector.try_add<Base, Derived>(factory);

    auto registrations = injector.get<std::vector<std::shared_ptr<Base>>>();

    ASSERT_THAT(registrations, SizeIs(1));
}