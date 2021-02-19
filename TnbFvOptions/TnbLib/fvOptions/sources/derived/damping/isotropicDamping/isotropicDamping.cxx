#include <isotropicDamping.hxx>

#include <fvMatrix.hxx>
#include <fvmSup.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace fv
	{
		defineTypeNameAndDebug(isotropicDamping, 0);
		addToRunTimeSelectionTable(option, isotropicDamping, dictionary);
	}
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::fv::isotropicDamping::add
(
	const volScalarField::Internal& forceCoeff,
	fvMatrix<vector>& eqn
)
{
	eqn -= fvm::Sp(forceCoeff, eqn.psi());
	eqn += forceCoeff * value_;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::fv::isotropicDamping::isotropicDamping
(
	const word& name,
	const word& modelType,
	const dictionary& dict,
	const fvMesh& mesh
)
	:
	damping(name, modelType, dict, mesh),
	value_("value", dimVelocity, coeffs_.lookup("value"))
{
	read(dict);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::fv::isotropicDamping::addSup
(
	fvMatrix<vector>& eqn,
	const label fieldi
)
{
	add(this->forceCoeff(), eqn);
}


void tnbLib::fv::isotropicDamping::addSup
(
	const volScalarField& rho,
	fvMatrix<vector>& eqn,
	const label fieldi
)
{
	add(rho*forceCoeff(), eqn);
}


void tnbLib::fv::isotropicDamping::addSup
(
	const volScalarField& alpha,
	const volScalarField& rho,
	fvMatrix<vector>& eqn,
	const label fieldi
)
{
	add(alpha()*rho()*this->forceCoeff(), eqn);
}


bool tnbLib::fv::isotropicDamping::read(const dictionary& dict)
{
	if (damping::read(dict))
	{
		value_ =
			dimensionedVector
			(
				value_.name(),
				value_.dimensions(),
				coeffs_.lookup(value_.name())
			);

		return true;
	}
	else
	{
		return false;
	}
}


// ************************************************************************* //