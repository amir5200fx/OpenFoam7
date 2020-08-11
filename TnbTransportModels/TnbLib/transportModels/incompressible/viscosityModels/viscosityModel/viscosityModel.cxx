#include <viscosityModel.hxx>

#include <volFields.hxx>
#include <fvcGrad.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(viscosityModel, 0);
	defineRunTimeSelectionTable(viscosityModel, dictionary);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::viscosityModel::viscosityModel
(
	const word& name,
	const dictionary& viscosityProperties,
	const volVectorField& U,
	const surfaceScalarField& phi
)
	:
	name_(name),
	viscosityProperties_(viscosityProperties),
	U_(U),
	phi_(phi)
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::volScalarField> tnbLib::viscosityModel::strainRate() const
{
	return sqrt(2.0)*mag(symm(fvc::grad(U_)));
}


bool tnbLib::viscosityModel::read(const dictionary& viscosityProperties)
{
	viscosityProperties_ = viscosityProperties;

	return true;
}


// ************************************************************************* //