/**
| State  | Event          | New state |
| ------- | -------------- | ------------- |
| Idle    | Start          | Driving       |
| Idle    | Error          | Fault         |
| Driving | Stop           | Idle          |
| Driving | Error          | Fault         |
| Fault   | Reset          | Idle          |
**/


#include <iostream>
#include "boost/sml.hpp"
namespace sml = boost::sml;
using namespace sml;

inline constexpr auto start = "Start"_e;
inline constexpr auto stop = "Stop"_e;
inline constexpr auto error = "Error"_e;
inline constexpr auto reset = "Reset"_e;



struct Robot
{
    auto operator()() const
    {
        using namespace sml;
        return make_transition_table(

        *"Idle"_s    + start = "Driving"_s,
         "Driving"_s + stop  = "Idle"_s,
         "Driving"_s + error = "Fault"_s,
         "Fault"_s   + reset = "Idle"_s
        );
    }
};

int main()
{
    sml::sm<Robot> robot{};

    robot.visit_current_states([](auto state) {
        std::cout << "Current state is: "<< state.c_str() << '\n';
    });

    robot.process_event(start());

    robot.visit_current_states([](auto state) {
        std::cout << "Current state is: "<< state.c_str() << '\n';
    });

    robot.process_event(stop());

    robot.visit_current_states([](auto state) {
        std::cout << "Current state is: "<< state.c_str() << '\n';
    });

    robot.process_event(start());

    robot.visit_current_states([](auto state) {
        std::cout << "Current state is: "<< state.c_str() << '\n';
    });

    robot.process_event(error());

    robot.visit_current_states([](auto state) {
        std::cout << "Current state is: "<< state.c_str() << '\n';
    });

    robot.process_event(reset());

    robot.visit_current_states([](auto state) {
        std::cout << "Current state is: "<< state.c_str() << '\n';
    });
}