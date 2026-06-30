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

int main()
{
    sml::sm<Robot> robot{};

    robot.visit_current_states([](auto state) {
        std::cout << "Current state is: "<< state.c_str() << '\n';
    });

    robot.process_event(Start{});

    robot.visit_current_states([](auto state) {
        std::cout << "Current state is: "<< state.c_str() << '\n';
    });

    robot.process_event(Stop{});

    robot.visit_current_states([](auto state) {
        std::cout << "Current state is: "<< state.c_str() << '\n';
    });

    robot.process_event(Start{});

    robot.visit_current_states([](auto state) {
        std::cout << "Current state is: "<< state.c_str() << '\n';
    });

    robot.process_event(Error{});

    robot.visit_current_states([](auto state) {
        std::cout << "Current state is: "<< state.c_str() << '\n';
    });


    robot.process_event(Reset{});

    robot.visit_current_states([](auto state) {
        std::cout << "Current state is: "<< state.c_str() << '\n';
    });
}