#include <viscosityModelNewtonian.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <surfaceFields.hxx>

#include <Time.hxx>  // added by amir

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace viscosityModels
	{
		defineTypeNameAndDebug(Newtonian, 0);
		addToRunTimeSelectionTable(viscosityModel, Newtonian, dictionary);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::viscosityModels::Newtonian::Newtonian
(
	const word& name,
	const dictionary& viscosityProperties,
	const volVectorField& U,
	const surfaceScalarField& phi
)
	:
	viscosityModel(name, viscosityProperties, U, phi),
	nu0_("nu", dimViscosity, viscosityProperties_),
	nu_
	(
		IOobject
		(
			name,
			U_.time().timeName(),
			U_.db(),
			IOobject::NO_READ,
			IOobject::NO_WRITE
		),
		U_.mesh(),
		nu0_
	)
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

bool tnbLib::viscosityModels::Newtonian::read
(
	const dictionary& viscosityProperties
)
{
	viscosityModel::read(viscosityProperties);

	viscosityProperties_.lookup("nu") >> nu0_;
	nu_ = nu0_;

	return true;
}


// ************************************************************************* //