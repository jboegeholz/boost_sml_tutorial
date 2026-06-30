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


struct Robot
{
    auto operator()() const
    {
        using namespace sml;
        return make_transition_table(

        *state<Idle>+ event<Start>  / [] { std::cout << "Received <<Start>> Event";} = state<Driving>,
            state<Driving> + event<Error> / [] { std::cout << "Received <<Error>> Event";} = state<Fault>,
            state<Driving> + event<Stop> / [] { std::cout << "Received <<Stop>> Event";}  = state<Idle>,
            state<Fault> + event<Reset>  / [] { std::cout << "Received <<Reset>> Event";} = state<Idle>

        );
    }
};


TEST(SimpleStateMachine, TestActions) {
    sml::sm<Robot> robot{};

    testing::internal::CaptureStdout();
    robot.process_event(Start{});
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "Received <<Start>> Event");

    testing::internal::CaptureStdout();
    robot.process_event(Stop{});
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "Received <<Stop>> Event");

    robot.process_event(Start{});

    testing::internal::CaptureStdout();
    robot.process_event(Error{});
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "Received <<Error>> Event");

    testing::internal::CaptureStdout();
    robot.process_event(Reset{});
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "Received <<Reset>> Event");
}