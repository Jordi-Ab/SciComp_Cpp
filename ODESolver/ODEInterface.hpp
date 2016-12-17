﻿/**************************************************************
Interface class for ODE problems of the type

    du/dt = f(t,u)

    where: t is a real number,
    and u is a vector of state variables.

    The function f(t,u) is provided by the user wrapped as a
    Functor class

***************************************************************/
#ifndef ODEINTERFACE_HPP
#define ODEINTERFACE_HPP

#include "Vector.hpp"
#include "MyFunctor.hpp"

class ODEInterface{

public:

    /* Constructor: ODEInterface
     * --------------------------
    */

    ODEInterface(MyFunctor& a_righthandside);

    void addTrueSolutionFunction(void (*function) (const double, Vector& ));

    // Compute right-hand side
    void ComputeF( const double t, const Vector& u, Vector& f  ) const;

    // Compute analytical solution
    void ComputeAnalyticSolution( const double t, Vector& u ) const;

    /*
     * Function: getDerivatives
     * ------------------------
     * Returns the vector of derivatives
     * dudt contained in MyFunctor.
    */
    Vector& getDerivatives();

private:

    // Dimension of the system.
    //int _dimension;

    // Right Hand Side Function
    //(Encapsulated as a MyFunctor object).
    MyFunctor* _rhs;

    // Function True Solution:
    void (*_true_sol) (const double, Vector& );

    // States Vector

};

#endif // ODEINTERFACE_HPP
