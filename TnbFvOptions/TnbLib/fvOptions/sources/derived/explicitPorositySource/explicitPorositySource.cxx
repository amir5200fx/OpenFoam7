#include <explicitPorositySource.hxx>

#include <fvMesh.hxx>
#include <fvMatrices.hxx>
#include <porosityModel.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace fv
	{
		defineTypeNameAndDebug(explicitPorositySource, 0);
		addToRunTimeSelectionTable
		(
			option,
			explicitPorositySource,
			dictionary
		);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::fv::explicitPorositySource::explicitPorositySource
(
	const word& name,
	const word& modelType,
	const dictionary& dict,
	const fvMesh& mesh
)
	:
	cellSetOption(name, modelType, dict, mesh),
	porosityPtr_(nullptr)
{
	read(dict);

	porosityPtr_.reset
	(
		porosityModel::New
		(
			name_,
			mesh_,
			coeffs_,
			cellSetName_
		).ptr()
	);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::fv::explicitPorositySource::addSup
(
	fvMatrix<vector>& eqn,
	const label fieldi
)
{
	fvMatrix<vector> porosityEqn(eqn.psi(), eqn.dimensions());
	porosityPtr_->addResistance(porosityEqn);
	eqn -= porosityEqn;
}


void tnbLib::fv::explicitPorositySource::addSup
(
	const volScalarField& rho,
	fvMatrix<vector>& eqn,
	const label fieldi
)
{
	fvMatrix<vector> porosityEqn(eqn.psi(), eqn.dimensions());
	porosityPtr_->addResistance(porosityEqn);
	eqn -= porosityEqn;
}


void tnbLib::fv::explicitPorositySource::addSup
(
	const volScalarField& alpha,
	const volScalarField& rho,
	fvMatrix<vector>& eqn,
	const label fieldi
)
{
	fvMatrix<vector> porosityEqn(eqn.psi(), eqn.dimensions());
	porosityPtr_->addResistance(porosityEqn);
	eqn -= alpha * porosityEqn;
}


bool tnbLib::fv::explicitPorositySource::read(const dictionary& dict)
{
	if (cellSetOption::read(dict))
	{
		if (coeffs_.found("UNames"))
		{
			coeffs_.lookup("UNames") >> fieldNames_;
		}
		else if (coeffs_.found("U"))
		{
			word UName(coeffs_.lookup("U"));
			fieldNames_ = wordList(1, UName);
		}
		else
		{
			fieldNames_ = wordList(1, "U");
		}

		applied_.setSize(fieldNames_.size(), false);

		return true;
	}
	else
	{
		return false;
	}
}


// ************************************************************************* //