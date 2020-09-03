#pragma once
#include <IOstreams.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<class Type>
bool tnbLib::SolverPerformance<Type>::checkSingularity
(
	const Type& wApA
)
{
	for (direction cmpt = 0; cmpt < pTraits<Type>::nComponents; cmpt++)
	{
		singular_[cmpt] =
			component(wApA, cmpt) < vsmall_;
	}

	return singular();
}


template<class Type>
bool tnbLib::SolverPerformance<Type>::singular() const
{
	for (direction cmpt = 0; cmpt < pTraits<Type>::nComponents; cmpt++)
	{
		if (!singular_[cmpt]) return false;
	}

	return true;
}


template<class Type>
bool tnbLib::SolverPerformance<Type>::checkConvergence
(
	const Type& Tolerance,
	const Type& RelTolerance
)
{
	if (debug >= 2)
	{
		Info << solverName_
			<< ":  Iteration " << nIterations_
			<< " residual = " << finalResidual_
			<< endl;
	}

	if
		(
			finalResidual_ < Tolerance
			|| (
				RelTolerance
			> small_*pTraits<Type>::one
				&& finalResidual_ < cmptMultiply(RelTolerance, initialResidual_)
				)
			)
	{
		converged_ = true;
	}
	else
	{
		converged_ = false;
	}

	return converged_;
}


template<class Type>
void tnbLib::SolverPerformance<Type>::print
(
	Ostream& os
) const
{
	for (direction cmpt = 0; cmpt < pTraits<Type>::nComponents; cmpt++)
	{
		if (pTraits<Type>::nComponents == 1)
		{
			os << solverName_ << ":  Solving for " << fieldName_;

		}
		else
		{
			os << solverName_ << ":  Solving for "
				<< word(fieldName_ + pTraits<Type>::componentNames[cmpt]);
		}

		if (singular_[cmpt])
		{
			os << ":  solution singularity" << endl;
		}
		else
		{
			os << ", Initial residual = " << component(initialResidual_, cmpt)
				<< ", Final residual = " << component(finalResidual_, cmpt)
				<< ", No Iterations " << nIterations_
				<< endl;
		}
	}
}


template<class Type>
void tnbLib::SolverPerformance<Type>::replace
(
	const tnbLib::label cmpt,
	const tnbLib::SolverPerformance<typename pTraits<Type>::cmptType>& sp
)
{
	initialResidual_.replace(cmpt, sp.initialResidual());
	finalResidual_.replace(cmpt, sp.finalResidual());
	nIterations_.replace(cmpt, sp.nIterations());
	singular_[cmpt] = sp.singular();
}


template<class Type>
tnbLib::SolverPerformance<typename tnbLib::pTraits<Type>::cmptType>
tnbLib::SolverPerformance<Type>::max()
{
	return SolverPerformance<typename pTraits<Type>::cmptType>
		(
			solverName_,
			fieldName_,
			cmptMax(initialResidual_),
			cmptMax(finalResidual_),
			cmptMax(nIterations_),
			converged_,
			singular()
			);
}


template<class Type>
bool tnbLib::SolverPerformance<Type>::operator!=
(
	const SolverPerformance<Type>& sp
	) const
{
	return
		(
			solverName() != sp.solverName()
			|| fieldName() != sp.fieldName()
			|| initialResidual() != sp.initialResidual()
			|| finalResidual() != sp.finalResidual()
			|| nIterations() != sp.nIterations()
			|| converged() != sp.converged()
			|| singular() != sp.singular()
			);
}


template<class Type>
typename tnbLib::SolverPerformance<Type> tnbLib::max
(
	const typename tnbLib::SolverPerformance<Type>& sp1,
	const typename tnbLib::SolverPerformance<Type>& sp2
)
{
	return SolverPerformance<Type>
		(
			sp1.solverName(),
			sp1.fieldName_,
			max(sp1.initialResidual(), sp2.initialResidual()),
			max(sp1.finalResidual(), sp2.finalResidual()),
			max(sp1.nIterations(), sp2.nIterations()),
			sp1.converged() && sp2.converged(),
			sp1.singular() || sp2.singular()
			);
}


template<class Type>
tnbLib::Istream& tnbLib::operator>>
(
	Istream& is,
	typename tnbLib::SolverPerformance<Type>& sp
	)
{
	is.readBeginList("SolverPerformance<Type>");
	is >> sp.solverName_
		>> sp.fieldName_
		>> sp.initialResidual_
		>> sp.finalResidual_
		>> sp.nIterations_
		>> sp.converged_
		>> sp.singular_;
	is.readEndList("SolverPerformance<Type>");

	return is;
}


template<class Type>
tnbLib::Ostream& tnbLib::operator<<
(
	Ostream& os,
	const typename tnbLib::SolverPerformance<Type>& sp
	)
{
	os << token::BEGIN_LIST
		<< sp.solverName_ << token::SPACE
		<< sp.fieldName_ << token::SPACE
		<< sp.initialResidual_ << token::SPACE
		<< sp.finalResidual_ << token::SPACE
		<< sp.nIterations_ << token::SPACE
		<< sp.converged_ << token::SPACE
		<< sp.singular_ << token::SPACE
		<< token::END_LIST;

	return os;
}


// ************************************************************************* //