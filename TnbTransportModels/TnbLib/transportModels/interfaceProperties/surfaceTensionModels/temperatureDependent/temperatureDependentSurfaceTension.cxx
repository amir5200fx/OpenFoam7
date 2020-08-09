#include <temperatureDependentSurfaceTension.hxx>

#include <volFields.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace surfaceTensionModels
	{
		defineTypeNameAndDebug(temperatureDependent, 0);
		addToRunTimeSelectionTable
		(
			surfaceTensionModel,
			temperatureDependent,
			dictionary
		);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::surfaceTensionModels::temperatureDependent::temperatureDependent
(
	const dictionary& dict,
	const fvMesh& mesh
)
	:
	surfaceTensionModel(mesh),
	TName_(dict.lookupOrDefault<word>("T", "T")),
	sigma_(Function1<scalar>::New("sigma", dict))
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::surfaceTensionModels::temperatureDependent::~temperatureDependent()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::volScalarField>
tnbLib::surfaceTensionModels::temperatureDependent::sigma() const
{
	tmp<volScalarField> tsigma
	(
		volScalarField::New("sigma", mesh_, dimSigma)
	);
	volScalarField& sigma = tsigma.ref();

	const volScalarField& T = mesh_.lookupObject<volScalarField>(TName_);

	sigma.field() = sigma_->value(T.field());

	volScalarField::Boundary& sigmaBf = sigma.boundaryFieldRef();
	const volScalarField::Boundary& TBf = T.boundaryField();

	forAll(sigmaBf, patchi)
	{
		sigmaBf[patchi] = sigma_->value(TBf[patchi]);
	}

	return tsigma;
}


bool tnbLib::surfaceTensionModels::temperatureDependent::readDict
(
	const dictionary& dict
)
{
	const dictionary& sigmaDict = surfaceTensionModel::sigmaDict(dict);

	TName_ = sigmaDict.lookupOrDefault<word>("T", "T");
	sigma_ = Function1<scalar>::New("sigma", sigmaDict);

	return true;
}


bool tnbLib::surfaceTensionModels::temperatureDependent::writeData
(
	Ostream& os
) const
{
	if (surfaceTensionModel::writeData(os))
	{
		os << sigma_() << token::END_STATEMENT << nl;
		return os.good();
	}
	else
	{
		return false;
	}
}


// ************************************************************************* //