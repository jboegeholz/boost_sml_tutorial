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

        *state<Idle>+ event<Start>  = state<Driving>,
            state<Idle> + event<Error> = state<Fault>,
            state<Driving> + event<Error> = state<Fault>,
            state<Driving> + event<Stop>  = state<Idle>,
            state<Fault> + event<Reset>  = state<Idle>

        );
    }
};

TEST(SimpleStateMachine, TestStartState) {
    const sml::sm<Robot> robot{};

    robot.visit_current_states([](auto state) {
        EXPECT_STREQ(state.c_str(), "Idle");
    });
}