#include <solidification.hxx>

#include <geometricOneField.hxx>
#include <fvMatrices.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace porosityModels
	{
		defineTypeNameAndDebug(solidification, 0);
		addToRunTimeSelectionTable(porosityModel, solidification, mesh);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::porosityModels::solidification::solidification
(
	const word& name,
	const word& modelType,
	const fvMesh& mesh,
	const dictionary& dict,
	const word& cellZoneName
)
	:
	porosityModel(name, modelType, mesh, dict, cellZoneName),
	TName_(coeffs_.lookupOrDefault<word>("T", "T")),
	alphaName_(coeffs_.lookupOrDefault<word>("alpha", "none")),
	rhoName_(coeffs_.lookupOrDefault<word>("rho", "rho")),
	D_(Function1<scalar>::New("D", coeffs_))
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::porosityModels::solidification::~solidification()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::porosityModels::solidification::calcTransformModelData()
{}


void tnbLib::porosityModels::solidification::calcForce
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


void tnbLib::porosityModels::solidification::correct
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


void tnbLib::porosityModels::solidification::correct
(
	fvVectorMatrix& UEqn,
	const volScalarField& rho,
	const volScalarField& mu
) const
{
	const volVectorField& U = UEqn.psi();
	const scalarField& V = mesh_.V();
	scalarField& Udiag = UEqn.diag();

	apply(Udiag, V, rho, U);
}


void tnbLib::porosityModels::solidification::correct
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


bool tnbLib::porosityModels::solidification::writeData(Ostream& os) const
{
	os << indent << name_ << endl;
	dict_.write(os);

	return true;
}


// ************************************************************************* //