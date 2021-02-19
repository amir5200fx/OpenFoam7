#include <actuationDiskSource.hxx>

#include <fvMesh.hxx>
#include <fvMatrix.hxx>
#include <geometricOneField.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace fv
	{
		defineTypeNameAndDebug(actuationDiskSource, 0);
		addToRunTimeSelectionTable
		(
			option,
			actuationDiskSource,
			dictionary
		);
	}
}


// * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::fv::actuationDiskSource::checkData() const
{
	if (magSqr(diskArea_) <= vSmall)
	{
		FatalErrorInFunction
			<< "diskArea is approximately zero"
			<< exit(FatalIOError);
	}
	if (Cp_ <= vSmall || Ct_ <= vSmall)
	{
		FatalErrorInFunction
			<< "Cp and Ct must be greater than zero"
			<< exit(FatalIOError);
	}
	if (mag(diskDir_) < vSmall)
	{
		FatalErrorInFunction
			<< "disk direction vector is approximately zero"
			<< exit(FatalIOError);
	}
	if (returnReduce(upstreamCellId_, maxOp<label>()) == -1)
	{
		FatalErrorInFunction
			<< "upstream location " << upstreamPoint_ << " not found in mesh"
			<< exit(FatalIOError);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::fv::actuationDiskSource::actuationDiskSource
(
	const word& name,
	const word& modelType,
	const dictionary& dict,
	const fvMesh& mesh
)
	:
	cellSetOption(name, modelType, dict, mesh),
	diskDir_(coeffs_.lookup("diskDir")),
	Cp_(readScalar(coeffs_.lookup("Cp"))),
	Ct_(readScalar(coeffs_.lookup("Ct"))),
	diskArea_(readScalar(coeffs_.lookup("diskArea"))),
	upstreamPoint_(coeffs_.lookup("upstreamPoint")),
	upstreamCellId_(-1)
{
	coeffs_.lookup("fields") >> fieldNames_;
	applied_.setSize(fieldNames_.size(), false);

	Info << "    - creating actuation disk zone: "
		<< this->name() << endl;

	upstreamCellId_ = mesh.findCell(upstreamPoint_);

	checkData();
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::fv::actuationDiskSource::addSup
(
	fvMatrix<vector>& eqn,
	const label fieldi
)
{
	const scalarField& cellsV = mesh_.V();
	vectorField& Usource = eqn.source();
	const vectorField& U = eqn.psi();

	if (V() > vSmall)
	{
		addActuationDiskAxialInertialResistance
		(
			Usource,
			cells_,
			cellsV,
			geometricOneField(),
			U
		);
	}
}


void tnbLib::fv::actuationDiskSource::addSup
(
	const volScalarField& rho,
	fvMatrix<vector>& eqn,
	const label fieldi
)
{
	const scalarField& cellsV = mesh_.V();
	vectorField& Usource = eqn.source();
	const vectorField& U = eqn.psi();

	if (V() > vSmall)
	{
		addActuationDiskAxialInertialResistance
		(
			Usource,
			cells_,
			cellsV,
			rho,
			U
		);
	}
}


bool tnbLib::fv::actuationDiskSource::read(const dictionary& dict)
{
	if (cellSetOption::read(dict))
	{
		coeffs_.readIfPresent("diskDir", diskDir_);
		coeffs_.readIfPresent("Cp", Cp_);
		coeffs_.readIfPresent("Ct", Ct_);
		coeffs_.readIfPresent("diskArea", diskArea_);

		checkData();

		return true;
	}
	else
	{
		return false;
	}
}


// ************************************************************************* //