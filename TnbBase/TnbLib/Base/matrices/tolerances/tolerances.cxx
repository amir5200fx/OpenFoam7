#include <tolerances.hxx>

#include <Time.hxx> // added by amir

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::tolerances::tolerances(const Time& t, const fileName& dictName)
	:
	IOdictionary
	(
		IOobject
		(
			dictName,
			t.system(),
			t,
			IOobject::MUST_READ_IF_MODIFIED,
			IOobject::NO_WRITE
		)
	),
	relaxationFactors_(ITstream("relaxationFactors", tokenList())()),
	solverTolerances_(ITstream("solverTolerances", tokenList())()),
	solverRelativeTolerances_
	(
		ITstream("solverRelativeTolerances", tokenList())()
	)
{
	read();
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::tolerances::read()
{
	if (regIOobject::read())
	{
		const word toleranceSetName(lookup("toleranceSet"));
		const dictionary& toleranceSet(subDict(toleranceSetName));

		if (toleranceSet.found("relaxationFactors"))
		{
			relaxationFactors_ = toleranceSet.subDict("relaxationFactors");
		}

		if (toleranceSet.found("solverTolerances"))
		{
			solverTolerances_ = toleranceSet.subDict("solverTolerances");
		}

		if (toleranceSet.found("solverRelativeTolerances"))
		{
			solverRelativeTolerances_ =
				toleranceSet.subDict("solverRelativeTolerances");
		}

		return true;
	}
	else
	{
		return false;
	}
}


bool tnbLib::tolerances::relax(const word& name) const
{
	return relaxationFactors_.found(name);
}


tnbLib::scalar tnbLib::tolerances::relaxationFactor(const word& name) const
{
	return readScalar(relaxationFactors_.lookup(name));
}


tnbLib::scalar tnbLib::tolerances::solverTolerance(const word& name) const
{
	return readScalar(solverTolerances_.lookup(name));
}


bool tnbLib::tolerances::solverRelativeTolerances() const
{
	return solverRelativeTolerances_.size();
}


tnbLib::scalar tnbLib::tolerances::solverRelativeTolerance(const word& name) const
{
	return readScalar(solverRelativeTolerances_.lookup(name));
}


// ************************************************************************* //