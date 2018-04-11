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

void solve_using_all_solvers(const LinearProblem& problem)
{
	LinearProgramSolver solver;
	LinearProgramSolver::SolverName s;

	//////////////////////////////////////////////////////////////////////////

	std::cout << "   - using GUROBI" << std::endl;
	s = LinearProgramSolver::GUROBI;
	if (solver.solve(&problem, s)) {
		const std::vector<double>& result = solver.get_result();
		std::cout << "      Objective: " << solver.get_objective_value() << std::endl;
		std::cout << "      Results:     ";
		for (std::size_t i = 0; i < result.size(); ++i) {
			std::cout << "x" << i + 1 << "=" << result[i] << "; ";
		}
		std::cout << std::endl << std::endl;
	}

	//////////////////////////////////////////////////////////////////////////

	std::cout << "   - using SCIP" << std::endl;
	s = LinearProgramSolver::SCIP;
	if (solver.solve(&problem, s)) {
		const std::vector<double>& result = solver.get_result();
		std::cout << "      Objective: " << solver.get_objective_value() << std::endl;
		std::cout << "      Results:     ";
		for (std::size_t i = 0; i < result.size(); ++i) {
			std::cout << "x" << i + 1 << "=" << result[i] << "; ";
		}
		std::cout << std::endl << std::endl;
	}

	//////////////////////////////////////////////////////////////////////////

	std::cout << "   - using GLPK" << std::endl;
	s = LinearProgramSolver::GLPK;
	if (solver.solve(&problem, s)) {
		const std::vector<double>& result = solver.get_result();
		std::cout << "      Objective: " << solver.get_objective_value() << std::endl;
		std::cout << "      Results:     ";
		for (std::size_t i = 0; i < result.size(); ++i) {
			std::cout << "x" << i + 1 << "=" << result[i] << "; ";
		}
		std::cout << std::endl << std::endl;
	}

	//////////////////////////////////////////////////////////////////////////

	std::cout << "   - using LPSOLVE" << std::endl;
	s = LinearProgramSolver::LPSOLVE;
	if (solver.solve(&problem, s)) {
		const std::vector<double>& result = solver.get_result();
		std::cout << "      Objective: " << solver.get_objective_value() << std::endl;
		std::cout << "      Results:     ";
		for (std::size_t i = 0; i < result.size(); ++i) {
			std::cout << "x" << i + 1 << "=" << result[i] << "; ";
		}
		std::cout << std::endl << std::endl;
	}
}

void print_problem_info(const LinearProblem& problem, const std::string& expected_result) {
	std::cout << "**************************************************************" << std::endl;
	if (problem.is_mix_integer_program())
		std::cout << "***  Mixed Integer Program" << std::endl;
	else if (problem.is_integer_program())
		std::cout << "***  Integer Program" << std::endl;
	else if (problem.is_binary_proram())
		std::cout << "***  Binary Program" << std::endl;
	else
		std::cout << "***  Continuous Program" << std::endl;
	std::cout << "***    # Variables: " << problem.num_continuous_variables() + problem.num_integer_variables() + problem.num_binary_variables() << std::endl;
	std::cout << "***      - Continuous variables: " << problem.num_continuous_variables() << std::endl;
	std::cout << "***      - Integer variables: " << problem.num_integer_variables() << std::endl;
	std::cout << "***      - Binary variables: " << problem.num_binary_variables() << std::endl;
	std::cout << "***    # Constraints: " << problem.num_constraints() << std::endl;
	std::cout << "***    Objective sense: " << ((problem.objective_sense() == LinearProblem::MINIMIZE) ? "Minimize" : "Maximize") << std::endl;
	std::cout << "***    Expected result: " << expected_result.data() << std::endl;
	std::cout << "**************************************************************" << std::endl;
}

std::string lp_problem(LinearProblem& problem);
std::string mip_problem(LinearProblem& problem);

int main()
{
	LinearProblem lp;
	const std::string& lp_result = lp_problem(lp);
	print_problem_info(lp, lp_result);
	solve_using_all_solvers(lp);

	std::cout << "\n" << "\n";


	LinearProblem mip;
	const std::string& mip_result = mip_problem(mip);
	print_problem_info(mip, mip_result);
	solve_using_all_solvers(mip);

	return 0;
}

