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


struct Robot
{
    auto operator()() const
    {
        using namespace sml;
        return make_transition_table(

        *state<Idle>+ event<Start>  / [] { std::cout << "Received <<Start>> Event\n";} = state<Driving>,
            state<Driving> + event<Error> / [] { std::cout << "Received <<Error>> Event\n";} = state<Fault>,
            state<Driving> + event<Stop> / [] { std::cout << "Received <<Stop>> Event\n";}  = state<Idle>,
            state<Fault> + event<Reset>  / [] { std::cout << "Received <<Reset>> Event\n";} = state<Idle>

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