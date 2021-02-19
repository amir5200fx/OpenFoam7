#include <fixedTrim.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <unitConversion.hxx>
#include <mathematicalConstants.hxx>

using namespace tnbLib::constant;

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(fixedTrim, 0);

	addToRunTimeSelectionTable(trimModel, fixedTrim, dictionary);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::fixedTrim::fixedTrim
(
	const fv::rotorDiskSource& rotor,
	const dictionary& dict
)
	:
	trimModel(rotor, dict, typeName),
	thetag_(rotor.cells().size(), 0.0)
{
	read(dict);
}


// * * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * //

tnbLib::fixedTrim::~fixedTrim()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::fixedTrim::read(const dictionary& dict)
{
	trimModel::read(dict);

	scalar theta0 = degToRad(readScalar(coeffs_.lookup("theta0")));
	scalar theta1c = degToRad(readScalar(coeffs_.lookup("theta1c")));
	scalar theta1s = degToRad(readScalar(coeffs_.lookup("theta1s")));

	const List<point>& x = rotor_.x();
	forAll(thetag_, i)
	{
		scalar psi = x[i].y();
		thetag_[i] = theta0 + theta1c * cos(psi) + theta1s * sin(psi);
	}
}


tnbLib::tmp<tnbLib::scalarField> tnbLib::fixedTrim::thetag() const
{
	return tmp<scalarField>(thetag_);
}


void tnbLib::fixedTrim::correct
(
	const vectorField& U,
	vectorField& force
)
{}


void tnbLib::fixedTrim::correct
(
	const volScalarField rho,
	const vectorField& U,
	vectorField& force)
{}


// ************************************************************************* //