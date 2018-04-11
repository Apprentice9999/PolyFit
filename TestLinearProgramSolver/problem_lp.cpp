/*
Copyright (C) 2017  Liangliang Nan
http://web.siat.ac.cn/~liangliang/ - liangliang.nan@gmail.com

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include "../math/linear_program.h"
#include "../math/linear_program_solver.h"


typedef LinearProgram<double>		LinearProblem;

/*
* The problem to solve is
*	var x1, >=0, <= .5;
*	var x2, >=0, <= .5;
*	var x3, >=0, <= .5;
*
* minimize z : 1.0  - 0.5 * x1 + 0.5 * x2 - 1.0 * x3       ;
* s.t. c1    : 0.0 <= 1.0 * x1 - 0.5 * x2            <= 0.2;
* s.t. c2    :                 - 1.0 * x2 + 1.0 * x3 <= 0.4;

Expected results: x1=0.25; x2=0.1; x3=0.5;
*/

std::string lp_problem(LinearProblem& problem)
{
	typedef Bound<double>				Bound;
	typedef Variable<double>			Variable;
	typedef LinearExpression<double>	Objective;
	typedef LinearConstraint<double>	Constraint;

	Variable x1(Variable::CONTINUOUS);	x1.set_bounds(Variable::DOUBLE, 0.0, 0.5);	problem.add_variable(x1);
	Variable x2(Variable::CONTINUOUS);	x2.set_bounds(Variable::DOUBLE, 0.0, 0.5);	problem.add_variable(x2);
	Variable x3(Variable::CONTINUOUS);	x3.set_bounds(Variable::DOUBLE, 0.0, 0.5);	problem.add_variable(x3);

	Objective obj;
	obj.add_coefficient(0, -0.5);
	obj.add_coefficient(1,  0.5);
	obj.add_coefficient(2, -1.0);
	problem.set_objective(obj, LinearProblem::MINIMIZE);

	Constraint c1;	//  0.0 <= 1.0 * x1 - 0.5 * x2 <= 0.2;
	c1.add_coefficient(0, 1);
	c1.add_coefficient(1, -0.5);
	c1.set_bounds(Variable::DOUBLE, 0.0, 0.2);
	problem.add_constraint(c1);

	Constraint c2;	//   -1.0 * x2 + 1.0 * x3 <= 0.4;
	c2.add_coefficient(1, -1);
	c2.add_coefficient(2, 1);
	c2.set_bounds(Bound::UPPER, 0.0, 0.4);
	problem.add_constraint(c2);

	return "x1=0.25; x2=0.1; x3=0.5;";
}

