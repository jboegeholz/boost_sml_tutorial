#include <gtest/gtest.h>
#include "../boost/sml.hpp"
namespace sml = boost::sml;
using namespace sml;

inline constexpr auto start_event = "Start"_e;
inline constexpr auto stop_event = "Stop"_e;
inline constexpr auto error_event = "Error"_e;
inline constexpr auto reset_event = "Reset"_e;

auto idle_state = "Idle"_s;
auto driving_state = "Driving"_s;
auto fault_state = "Fault"_s;


struct Robot
{
    auto operator()() const
    {
        using namespace sml;
        return make_transition_table(

        *idle_state    + start_event = driving_state,
         driving_state + stop_event  = idle_state,
         driving_state + error_event = fault_state,
         fault_state   + reset_event = idle_state
        );
    }
};

TEST(SMWithUDL, TestTransition) {
    sml::sm<Robot> robot{};

    robot.process_event(start_event());

    robot.visit_current_states([](auto state) {
        EXPECT_STREQ(state.c_str(), "Driving");
    });

    robot.process_event(stop_event());

    robot.visit_current_states([](auto state) {
        EXPECT_STREQ(state.c_str(), "Idle");
    });

    robot.process_event(start_event());

    robot.visit_current_states([](auto state) {
        EXPECT_STREQ(state.c_str(), "Driving");
    });
    robot.process_event(error_event());

    robot.visit_current_states([](auto state) {
        EXPECT_STREQ(state.c_str(), "Fault");
    });

    robot.process_event(reset_event());

    robot.visit_current_states([](auto state) {
        EXPECT_STREQ(state.c_str(), "Idle");
    });
}