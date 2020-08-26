#include <powerLaw.hxx>

#include <geometricOneField.hxx>
#include <fvMatrices.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace porosityModels
	{
		defineTypeNameAndDebug(powerLaw, 0);
		addToRunTimeSelectionTable(porosityModel, powerLaw, mesh);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::porosityModels::powerLaw::powerLaw
(
	const word& name,
	const word& modelType,
	const fvMesh& mesh,
	const dictionary& dict,
	const word& cellZoneName
)
	:
	porosityModel(name, modelType, mesh, dict, cellZoneName),
	C0_(readScalar(coeffs_.lookup("C0"))),
	C1_(readScalar(coeffs_.lookup("C1"))),
	rhoName_(coeffs_.lookupOrDefault<word>("rho", "rho"))
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::porosityModels::powerLaw::~powerLaw()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::porosityModels::powerLaw::calcTransformModelData()
{
	// nothing to be transformed
}


void tnbLib::porosityModels::powerLaw::calcForce
(
	const volVectorField& U,
	const volScalarField& rho,
	const volScalarField& mu,
	vectorField& force
) const
{
	scalarField Udiag(U.size(), 0.0);
	const scalarField& V = mesh_.V();

	apply(Udiag, V, rho, U);

	force = Udiag * U;
}


void tnbLib::porosityModels::powerLaw::correct
(
	fvVectorMatrix& UEqn
) const
{
	const volVectorField& U = UEqn.psi();
	const scalarField& V = mesh_.V();
	scalarField& Udiag = UEqn.diag();

	if (UEqn.dimensions() == dimForce)
	{
		const volScalarField& rho = mesh_.lookupObject<volScalarField>
			(
				IOobject::groupName(rhoName_, U.group())
				);

		apply(Udiag, V, rho, U);
	}
	else
	{
		apply(Udiag, V, geometricOneField(), U);
	}
}


void tnbLib::porosityModels::powerLaw::correct
(
	fvVectorMatrix& UEqn,
	const volScalarField& rho,
	const volScalarField& mu
) const
{
	const vectorField& U = UEqn.psi();
	const scalarField& V = mesh_.V();
	scalarField& Udiag = UEqn.diag();

	apply(Udiag, V, rho, U);
}


void tnbLib::porosityModels::powerLaw::correct
(
	const fvVectorMatrix& UEqn,
	volTensorField& AU
) const
{
	const volVectorField& U = UEqn.psi();

	if (UEqn.dimensions() == dimForce)
	{
		const volScalarField& rho = mesh_.lookupObject<volScalarField>
			(
				IOobject::groupName(rhoName_, U.group())
				);

		apply(AU, rho, U);
	}
	else
	{
		apply(AU, geometricOneField(), U);
	}
}


bool tnbLib::porosityModels::powerLaw::writeData(Ostream& os) const
{
	os << indent << name_ << endl;
	dict_.write(os);

	return true;
}


// ************************************************************************* //