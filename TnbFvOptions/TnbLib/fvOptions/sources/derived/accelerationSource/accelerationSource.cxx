#include <accelerationSource.hxx>

#include <fvMesh.hxx>
#include <fvMatrix.hxx>
#include <geometricOneField.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace fv
	{
		defineTypeNameAndDebug(accelerationSource, 0);
		addToRunTimeSelectionTable(option, accelerationSource, dictionary);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::fv::accelerationSource::accelerationSource
(
	const word& name,
	const word& modelType,
	const dictionary& dict,
	const fvMesh& mesh
)
	:
	cellSetOption(name, modelType, dict, mesh),
	velocity_(nullptr)
{
	read(dict);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::fv::accelerationSource::addSup
(
	fvMatrix<vector>& eqn,
	const label fieldi
)
{
	add(geometricOneField(), eqn, fieldi);
}


void tnbLib::fv::accelerationSource::addSup
(
	const volScalarField& rho,
	fvMatrix<vector>& eqn,
	const label fieldi
)
{
	add(rho, eqn, fieldi);
}


void tnbLib::fv::accelerationSource::addSup
(
	const volScalarField& alpha,
	const volScalarField& rho,
	fvMatrix<vector>& eqn,
	const label fieldi
)
{
	add((alpha*rho)(), eqn, fieldi);
}


bool tnbLib::fv::accelerationSource::read(const dictionary& dict)
{
	if (cellSetOption::read(dict))
	{
		fieldNames_ = wordList(1, coeffs_.lookupOrDefault<word>("U", "U"));

		applied_.setSize(1, false);

		velocity_ = Function1<vector>::New("velocity", dict);

		return true;
	}
	else
	{
		return false;
	}
}


// ************************************************************************* //