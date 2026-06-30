#include <iostream>
#include <gtest/gtest.h>
#include "../boost/sml.hpp"

namespace sml = boost::sml;
using namespace sml;

struct Idle {};
struct Driving {};
struct Fault{};

// Events
struct Start{};
struct Stop{};
struct Error{};
struct Reset{};

constexpr auto StartEvent = event<Start>;
constexpr auto StopEvent = event<Stop>;
constexpr auto ErrorEvent = event<Error>;
constexpr auto ResetEvent = event<Reset>;


struct RobotContext {
    bool battery_ok = true;
};

struct Robot
{
    auto operator()() const
    {
        using namespace sml;
        return make_transition_table(
        *state<Idle>+ (StartEvent)[([](const RobotContext& ctx) {return ctx.battery_ok;})] = state<Driving>,
            state<Driving> + ErrorEvent = state<Fault>,
            state<Driving> + StopEvent  = state<Idle>,
            state<Fault> + ResetEvent  = state<Idle>
        );
    }
};

TEST(GuardsWithDependencyInjection, TestGuardTrue) {
    RobotContext ctx;
    sml::sm<Robot> robot{ctx};
    robot.process_event(Start{});

    robot.visit_current_states([](auto state) {
        EXPECT_STREQ(state.c_str(), "Driving");
    });
}
TEST(GuardsWithDependencyInjection, TestGuardFalse) {
    RobotContext ctx;
    ctx.battery_ok = false;
    sml::sm<Robot> robot{ctx};
    robot.process_event(Start{});

    robot.visit_current_states([](auto state) {
        EXPECT_STREQ(state.c_str(), "Idle");
    });
}