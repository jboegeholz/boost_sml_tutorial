#include <iostream>
#include "boost/sml.hpp"


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
        std::cout << "Start\n";
    }
};
struct stop_action {
    void operator()() const {
        std::cout << "Stop\n";
    }
};
struct error_action {
    void operator()() const {
        std::cout << "Error\n";
    }
};
struct reset_action {
    void operator()() const {
        std::cout << "Reset\n";
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