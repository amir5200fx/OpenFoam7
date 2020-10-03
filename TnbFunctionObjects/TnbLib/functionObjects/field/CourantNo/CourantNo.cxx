#include <CourantNo.hxx>

#include <surfaceFields.hxx>
#include <fvcSurfaceIntegrate.hxx>
#include <zeroGradientFvPatchFields.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionObjects
	{
		defineTypeNameAndDebug(CourantNo, 0);

		addToRunTimeSelectionTable
		(
			functionObject,
			CourantNo,
			dictionary
		);
	}
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

tnbLib::tmp<tnbLib::volScalarField::Internal>
tnbLib::functionObjects::CourantNo::byRho
(
	const tmp<volScalarField::Internal>& Co
) const
{
	if (Co().dimensions() == dimDensity)
	{
		return Co / obr_.lookupObject<volScalarField>(rhoName_);
	}
	else
	{
		return Co;
	}
}


bool tnbLib::functionObjects::CourantNo::calc()
{
	if (foundObject<surfaceScalarField>(fieldName_))
	{
		const surfaceScalarField& phi =
			lookupObject<surfaceScalarField>(fieldName_);

		tmp<volScalarField> tCo
		(
			volScalarField::New
			(
				resultName_,
				mesh_,
				dimensionedScalar(dimless, 0),
				zeroGradientFvPatchScalarField::typeName
			)
		);

		tCo->ref() =
			byRho
			(
			(0.5*mesh_.time().deltaT())
				*fvc::surfaceSum(mag(phi))()()
				/ mesh_.V()
			);

		tCo->correctBoundaryConditions();

		return store(resultName_, tCo);
	}
	else
	{
		return false;
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::functionObjects::CourantNo::CourantNo
(
	const word& name,
	const Time& runTime,
	const dictionary& dict
)
	:
	fieldExpression(name, runTime, dict, "phi")
{
	setResultName("Co", "phi");
	read(dict);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::functionObjects::CourantNo::~CourantNo()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::functionObjects::CourantNo::read(const dictionary& dict)
{
	fieldExpression::read(dict);

	rhoName_ = dict.lookupOrDefault<word>("rho", "rho");

	return true;
}


// ************************************************************************* //