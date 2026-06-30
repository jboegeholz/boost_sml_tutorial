#include <iostream>
#include <gtest/gtest.h>
#include "../boost/sml.hpp"

namespace sml = boost::sml;


struct Idle {};
struct Driving {};
struct Fault{};

// Events
struct Start{};
struct Stop{};
struct Error{};
struct Reset{};


auto battery_ok = [] { return true; };


struct Robot
{
    auto operator()() const
    {
        using namespace sml;
        return make_transition_table(
        *state<Idle>+ event<Start>[battery_ok] = state<Driving>,
            state<Driving> + event<Error> = state<Fault>,
            state<Driving> + event<Stop>  = state<Idle>,
            state<Fault> + event<Reset>  = state<Idle>
        );
    }
};

TEST(Guards, TestGuards) {

    sml::sm<Robot> robot{};
    robot.process_event(Start{});

    robot.visit_current_states([](auto state) {
        EXPECT_STREQ(state.c_str(), "Driving");
    });
}