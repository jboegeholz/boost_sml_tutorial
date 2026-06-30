#include <iostream>
#include <gtest/gtest.h>
#include "../boost/sml.hpp"


namespace sml = boost::sml;

// States
struct Idle {};
struct Driving {};
struct Fault{};

// Events
struct Start{};
struct Stop{};
struct Error{};
struct Reset{};

struct start_action {
    void operator()() const {
        std::cout << "Action: Start";
    }
};
struct stop_action {
    void operator()() const {
        std::cout << "Action: Stop";
    }
};
struct error_action {
    void operator()() const {
        std::cout << "Action: Error";
    }
};
struct reset_action {
    void operator()() const {
        std::cout << "Action: Reset";
    }
};
struct Robot
{
    auto operator()() const
    {
        using namespace sml;
        return make_transition_table(

        *state<Idle>+ event<Start>  / start_action{} = state<Driving>,
            state<Driving> + event<Error> / error_action{} = state<Fault>,
            state<Driving> + event<Stop> / stop_action{} = state<Idle>,
            state<Fault> + event<Reset>  / reset_action{} = state<Idle>

        );
    }
};

TEST(SMWithFunctorActions, TestTransition) {
    sml::sm<Robot> robot{};

    testing::internal::CaptureStdout();
    robot.process_event(Start{});
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "Action: Start");

    testing::internal::CaptureStdout();
    robot.process_event(Stop{});
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "Action: Stop");

    robot.process_event(Start{});

    testing::internal::CaptureStdout();
    robot.process_event(Error{});
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "Action: Error");

    testing::internal::CaptureStdout();
    robot.process_event(Reset{});
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "Action: Reset");
}