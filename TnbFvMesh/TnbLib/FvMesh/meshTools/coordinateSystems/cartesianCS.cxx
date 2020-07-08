#include <cartesianCS.hxx>

#include <one.hxx>
#include <mathematicalConstants.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(cartesianCS, 0);
	addToRunTimeSelectionTable(coordinateSystem, cartesianCS, dictionary);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::cartesianCS::cartesianCS()
	:
	coordinateSystem()
{}


tnbLib::cartesianCS::cartesianCS
(
	const coordinateSystem& cs
)
	:
	coordinateSystem(cs)
{}


tnbLib::cartesianCS::cartesianCS
(
	const word& name,
	const coordinateSystem& cs
)
	:
	coordinateSystem(name, cs)
{}


tnbLib::cartesianCS::cartesianCS
(
	const word& name,
	const point& origin,
	const coordinateRotation& cr
)
	:
	coordinateSystem(name, origin, cr)
{}


tnbLib::cartesianCS::cartesianCS
(
	const word& name,
	const point& origin,
	const vector& axis,
	const vector& dirn
)
	:
	coordinateSystem(name, origin, axis, dirn)
{}


tnbLib::cartesianCS::cartesianCS
(
	const word& name,
	const dictionary& dict
)
	:
	coordinateSystem(name, dict)
{}


tnbLib::cartesianCS::cartesianCS
(
	const objectRegistry& obr,
	const dictionary& dict
)
	:
	coordinateSystem(obr, dict)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::cartesianCS::~cartesianCS()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //


tnbLib::vector tnbLib::cartesianCS::localToGlobal
(
	const vector& local,
	bool translate
) const
{
	return coordinateSystem::localToGlobal(local, translate);
}


tnbLib::tmp<tnbLib::vectorField> tnbLib::cartesianCS::localToGlobal
(
	const vectorField& local,
	bool translate
) const
{
	return coordinateSystem::localToGlobal(local, translate);
}


tnbLib::vector tnbLib::cartesianCS::globalToLocal
(
	const vector& global,
	bool translate
) const
{
	return coordinateSystem::globalToLocal(global, translate);
}


tnbLib::tmp<tnbLib::vectorField> tnbLib::cartesianCS::globalToLocal
(
	const vectorField& global,
	bool translate
) const
{
	return coordinateSystem::globalToLocal(global, translate);
}


// ************************************************************************* //