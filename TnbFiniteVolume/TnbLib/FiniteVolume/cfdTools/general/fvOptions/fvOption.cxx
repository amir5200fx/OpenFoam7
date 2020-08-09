#include <fvOption.hxx>

#include <volFields.hxx>

#include <Time.hxx>  // added by amir

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace fv
	{
		defineTypeNameAndDebug(option, 0);
		defineRunTimeSelectionTable(option, dictionary);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::fv::option::option
(
	const word& name,
	const word& modelType,
	const dictionary& dict,
	const fvMesh& mesh
)
	:
	name_(name),
	modelType_(modelType),
	mesh_(mesh),
	dict_(dict),
	coeffs_(dict.optionalSubDict(modelType + "Coeffs")),
	active_(dict_.lookupOrDefault<Switch>("active", true)),
	fieldNames_(),
	applied_()
{
	Info << incrIndent << indent << "Source: " << name_ << endl << decrIndent;
}


// * * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::fv::option> tnbLib::fv::option::New
(
	const word& name,
	const dictionary& coeffs,
	const fvMesh& mesh
)
{
	word modelType(coeffs.lookup("type"));

	Info << indent
		<< "Selecting finite volume options model type " << modelType << endl;

	const_cast<Time&>(mesh.time()).libs().open
	(
		coeffs,
		"libs",
		dictionaryConstructorTablePtr_
	);

	dictionaryConstructorTable::iterator cstrIter =
		dictionaryConstructorTablePtr_->find(modelType);

	if (cstrIter == dictionaryConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown Model type " << modelType << nl << nl
			<< "Valid model types are:" << nl
			<< dictionaryConstructorTablePtr_->sortedToc()
			<< exit(FatalError);
	}

	return autoPtr<option>(cstrIter()(name, modelType, coeffs, mesh));
}


tnbLib::fv::option::~option()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::fv::option::isActive()
{
	return active_;
}


tnbLib::label tnbLib::fv::option::applyToField(const word& fieldName) const
{
	return findIndex(fieldNames_, fieldName);
}


void tnbLib::fv::option::checkApplied() const
{
	forAll(applied_, i)
	{
		if (!applied_[i])
		{
			WarningInFunction
				<< "Source " << name_ << " defined for field "
				<< fieldNames_[i] << " but never used" << endl;
		}
	}
}


void tnbLib::fv::option::addSup
(
	fvMatrix<scalar>& eqn,
	const label fieldi
)
{}


void tnbLib::fv::option::addSup
(
	fvMatrix<vector>& eqn,
	const label fieldi
)
{}


void tnbLib::fv::option::addSup
(
	fvMatrix<sphericalTensor>& eqn,
	const label fieldi
)
{}


void tnbLib::fv::option::addSup
(
	fvMatrix<symmTensor>& eqn,
	const label fieldi
)
{}


void tnbLib::fv::option::addSup
(
	fvMatrix<tensor>& eqn,
	const label fieldi
)
{}


void tnbLib::fv::option::addSup
(
	const volScalarField& rho,
	fvMatrix<scalar>& eqn,
	const label fieldi
)
{}


void tnbLib::fv::option::addSup
(
	const volScalarField& rho,
	fvMatrix<vector>& eqn,
	const label fieldi
)
{}


void tnbLib::fv::option::addSup
(
	const volScalarField& rho,
	fvMatrix<sphericalTensor>& eqn,
	const label fieldi
)
{}


void tnbLib::fv::option::addSup
(
	const volScalarField& rho,
	fvMatrix<symmTensor>& eqn,
	const label fieldi
)
{}


void tnbLib::fv::option::addSup
(
	const volScalarField& rho,
	fvMatrix<tensor>& eqn,
	const label fieldi
)
{}


void tnbLib::fv::option::addSup
(
	const volScalarField& alpha,
	const volScalarField& rho,
	fvMatrix<scalar>& eqn,
	const label fieldi
)
{
	addSup(alpha*rho, eqn, fieldi);
}


void tnbLib::fv::option::addSup
(
	const volScalarField& alpha,
	const volScalarField& rho,
	fvMatrix<vector>& eqn,
	const label fieldi
)
{
	addSup(alpha*rho, eqn, fieldi);
}


void tnbLib::fv::option::addSup
(
	const volScalarField& alpha,
	const volScalarField& rho,
	fvMatrix<sphericalTensor>& eqn,
	const label fieldi
)
{
	addSup(alpha*rho, eqn, fieldi);
}


void tnbLib::fv::option::addSup
(
	const volScalarField& alpha,
	const volScalarField& rho,
	fvMatrix<symmTensor>& eqn,
	const label fieldi
)
{
	addSup(alpha*rho, eqn, fieldi);
}


void tnbLib::fv::option::addSup
(
	const volScalarField& alpha,
	const volScalarField& rho,
	fvMatrix<tensor>& eqn,
	const label fieldi
)
{
	addSup(alpha*rho, eqn, fieldi);
}


void tnbLib::fv::option::constrain(fvMatrix<scalar>& eqn, const label fieldi)
{}


void tnbLib::fv::option::constrain(fvMatrix<vector>& eqn, const label fieldi)
{}


void tnbLib::fv::option::constrain
(
	fvMatrix<sphericalTensor>& eqn,
	const label fieldi
)
{}


void tnbLib::fv::option::constrain
(
	fvMatrix<symmTensor>& eqn,
	const label fieldi
)
{}


void tnbLib::fv::option::constrain(fvMatrix<tensor>& eqn, const label fieldi)
{}


void tnbLib::fv::option::correct(volScalarField& field)
{}


void tnbLib::fv::option::correct(volVectorField& field)
{}


void tnbLib::fv::option::correct(volSphericalTensorField& field)
{}


void tnbLib::fv::option::correct(volSymmTensorField& field)
{}


void tnbLib::fv::option::correct(volTensorField& field)
{}


// ************************************************************************* //