#include <engineTime.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(engineTime, 0);
	defineRunTimeSelectionTable(engineTime, dictionary);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::engineTime::engineTime
(
	const word& name,
	const fileName& rootPath,
	const fileName& caseName,
	const fileName& systemName,
	const fileName& constantName,
	const fileName& dictName
)
	:
	Time
	(
		name,
		rootPath,
		caseName,
		systemName,
		constantName
	),
	dict_
	(
		tnbLib::IOobject
		(
			"engineGeometry",
			constant(),
			*this,
			tnbLib::IOobject::MUST_READ_IF_MODIFIED,
			tnbLib::IOobject::NO_WRITE,
			false
		)
	)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::engineTime::readDict()
{
	Time::readDict();
}


bool tnbLib::engineTime::read()
{
	if (Time::read())
	{
		return true;
	}
	else
	{
		return false;
	}
}


tnbLib::dimensionedScalar tnbLib::engineTime::pistonPosition() const
{
	return dimensionedScalar
	(
		"pistonPosition",
		dimLength,
		pistonPosition(theta())
	);
}


tnbLib::dimensionedScalar tnbLib::engineTime::pistonDisplacement() const
{
	return dimensionedScalar
	(
		"pistonDisplacement",
		dimLength,
		pistonPosition(theta() - deltaTheta()) - pistonPosition().value()
	);
}


tnbLib::dimensionedScalar tnbLib::engineTime::pistonSpeed() const
{
	return dimensionedScalar
	(
		"pistonSpeed",
		dimVelocity,
		pistonDisplacement().value() / (deltaTValue() + vSmall)
	);
}


// ************************************************************************* //