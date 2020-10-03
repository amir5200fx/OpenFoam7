#include <PecletNo.hxx>

#include <turbulenceModel.hxx>
#include <surfaceInterpolate.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionObjects
	{
		defineTypeNameAndDebug(PecletNo, 0);

		addToRunTimeSelectionTable
		(
			functionObject,
			PecletNo,
			dictionary
		);
	}
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

bool tnbLib::functionObjects::PecletNo::calc()
{
	if (foundObject<surfaceScalarField>(fieldName_))
	{
		tmp<volScalarField> nuEff
		(
			mesh_.lookupObject<turbulenceModel>
			(
				turbulenceModel::propertiesName
				).nuEff()
		);

		const surfaceScalarField& phi =
			mesh_.lookupObject<surfaceScalarField>(fieldName_);

		return store
		(
			resultName_,
			mag(phi)
			/ (
				mesh_.magSf()
				*mesh_.surfaceInterpolation::deltaCoeffs()
				*fvc::interpolate(nuEff)
				)
		);
	}
	else
	{
		return false;
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::functionObjects::PecletNo::PecletNo
(
	const word& name,
	const Time& runTime,
	const dictionary& dict
)
	:
	fieldExpression(name, runTime, dict, "phi")
{
	setResultName("Pe", "phi");
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::functionObjects::PecletNo::~PecletNo()
{}


// ************************************************************************* //