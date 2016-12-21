#include "StoermerVerletSolver.hpp"

StoermerVerletSolver::StoermerVerletSolver( ODEInterface& an_ODESystem,
                                            const Vector& initial_state,
                                            const Vector& initial_velocity,
                                            const double initial_time,
                                            const double final_time,
                                            const double step_size,
                                            const std::string output_file_name,
                                            const int save_gap,
                                            const int print_gap){
    // Set things for AbstractODE object.
    setStepSize(step_size);
    setTimeInterval(initial_time, final_time);
    _ODEObject = &an_ODESystem;

    // Set things for this object.
    _output_file_name = output_file_name;
    _initial_state = new Vector(initial_state);
    _initial_velocity = new Vector(initial_velocity);

    if (save_gap <= 0) _save_gap = 1;
    else if (save_gap >= final_time/step_size) _save_gap = final_time;
    else _save_gap = save_gap;

    if (print_gap <= 0) _print_gap = 1;
    else if (print_gap >= final_time/step_size) _print_gap = final_time;
    else _print_gap = print_gap;


}

StoermerVerletSolver::~StoermerVerletSolver(){
    delete _initial_state;
    delete _initial_velocity;
}

// A solver that writes the solution on an Output file at
// each time step (no need of arrays to store solution).
void StoermerVerletSolver::solve(){

    printHeader("Stoermer-Verlet");
    double h = getStepSize();

    openOutputFile(_output_file_name);
    int iteration = 1;

    Vector current_state = *_initial_state;
    Vector next_state(current_state);
    Vector current_vel = *_initial_velocity;
    Vector next_vel(current_vel);

    double current_t = getInitialTime();

    while(current_t < getFinalTime()){

        if( (iteration % _save_gap) == 0){
            writeData(current_t, current_state);
        }

        if( (iteration % _print_gap) == 0){
            printData(current_t, current_state);
        }

        double next_t = current_t + h;

        // Evaluate right hand side function at the
        // current time and current state,
        // store the result in next state.
        _ODEObject->ComputeF(current_t, current_state, next_state);

        next_vel = current_vel + next_state*h; // Fwd Euler formula.
        next_state = current_state + next_vel*h;

        current_t = next_t; // Take one step in time.
        current_vel = next_vel;
        current_state = next_state; // Take one step in the state.

        iteration++;

    }

    closeOutputFile();

}

double StoermerVerletSolver::computeError(){

}
