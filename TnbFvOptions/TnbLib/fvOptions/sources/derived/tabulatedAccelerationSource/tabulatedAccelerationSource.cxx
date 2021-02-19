#include <tabulatedAccelerationSource.hxx>

#include <fvMesh.hxx>
#include <fvMatrices.hxx>
#include <geometricOneField.hxx>
#include <addToRunTimeSelectionTable.hxx>

#include <uniformDimensionedFields.hxx>  // added by amir 

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace fv
	{
		defineTypeNameAndDebug(tabulatedAccelerationSource, 0);
		addToRunTimeSelectionTable
		(
			option,
			tabulatedAccelerationSource,
			dictionary
		);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::fv::tabulatedAccelerationSource::tabulatedAccelerationSource
(
	const word& name,
	const word& modelType,
	const dictionary& dict,
	const fvMesh& mesh
)
	:
	option(name, modelType, dict, mesh),
	motion_(coeffs_, mesh.time()),
	UName_(coeffs_.lookupOrDefault<word>("U", "U")),
	g0_("g0", dimAcceleration, Zero)
{
	fieldNames_.setSize(1, UName_);
	applied_.setSize(1, false);

	if (mesh.foundObject<uniformDimensionedVectorField>("g"))
	{
		g0_ = mesh.lookupObject<uniformDimensionedVectorField>("g");
	}
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::fv::tabulatedAccelerationSource::addSup
(
	fvMatrix<vector>& eqn,
	const label fieldi
)
{
	addSup<geometricOneField>(geometricOneField(), eqn, fieldi);
}


void tnbLib::fv::tabulatedAccelerationSource::addSup
(
	const volScalarField& rho,
	fvMatrix<vector>& eqn,
	const label fieldi
)
{
	addSup<volScalarField>(rho, eqn, fieldi);
}


bool tnbLib::fv::tabulatedAccelerationSource::read(const dictionary& dict)
{
	if (option::read(dict))
	{
		return motion_.read(coeffs_);
	}
	else
	{
		return false;
	}
}


// ************************************************************************* //