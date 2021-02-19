#include <radialActuationDiskSource.hxx>

#include <geometricOneField.hxx>
#include <addToRunTimeSelectionTable.hxx>

#include <fvMatrices.hxx>  // added by amir

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace fv
	{
		defineTypeNameAndDebug(radialActuationDiskSource, 0);
		addToRunTimeSelectionTable
		(
			option,
			radialActuationDiskSource,
			dictionary
		);
	}
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::fv::radialActuationDiskSource::radialActuationDiskSource
(
	const word& name,
	const word& modelType,
	const dictionary& dict,
	const fvMesh& mesh
)
	:
	actuationDiskSource(name, modelType, dict, mesh),
	radialCoeffs_(coeffs_.lookup("coeffs"))
{
	Info << "    - creating radial actuation disk zone: " << name_ << endl;
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::fv::radialActuationDiskSource::addSup
(
	fvMatrix<vector>& eqn,
	const label fieldi
)
{
	const scalarField& cellsV = mesh_.V();
	vectorField& Usource = eqn.source();
	const vectorField& U = eqn.psi();

	if (V_ > vSmall)
	{
		addRadialActuationDiskAxialInertialResistance
		(
			Usource,
			cells_,
			cellsV,
			geometricOneField(),
			U
		);
	}
}


void tnbLib::fv::radialActuationDiskSource::addSup
(
	const volScalarField& rho,
	fvMatrix<vector>& eqn,
	const label fieldi
)
{
	const scalarField& cellsV = mesh_.V();
	vectorField& Usource = eqn.source();
	const vectorField& U = eqn.psi();

	if (V_ > vSmall)
	{
		addRadialActuationDiskAxialInertialResistance
		(
			Usource,
			cells_,
			cellsV,
			rho,
			U
		);
	}
}


bool tnbLib::fv::radialActuationDiskSource::read(const dictionary& dict)
{
	if (actuationDiskSource::read(dict))
	{
		coeffs_.lookup("coeffs") >> radialCoeffs_;
		return true;
	}
	else
	{
		return false;
	}
}


// ************************************************************************* //