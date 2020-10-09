#include <flowType.hxx>

#include <fvcGrad.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionObjects
	{
		defineTypeNameAndDebug(flowType, 0);

		addToRunTimeSelectionTable
		(
			functionObject,
			flowType,
			dictionary
		);
	}
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

bool tnbLib::functionObjects::flowType::calc()
{
	if (foundObject<volVectorField>(fieldName_))
	{
		const volVectorField& U = lookupObject<volVectorField>(fieldName_);
		const tmp<volTensorField> tgradU(fvc::grad(U));
		const volTensorField& gradU = tgradU();

		volScalarField magD(mag(symm(gradU)));
		volScalarField magOmega(mag(skew(gradU)));
		dimensionedScalar smallMagD("smallMagD", magD.dimensions(), small);

		const volTensorField SSplusWW
		(
			(symm(gradU) & symm(gradU))
			+ (skew(gradU) & skew(gradU))
		);

		return store
		(
			resultName_,
			(magD - magOmega) / (magD + magOmega + smallMagD)
		);
	}
	else
	{
		return false;
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::functionObjects::flowType::flowType
(
	const word& name,
	const Time& runTime,
	const dictionary& dict
)
	:
	fieldExpression(name, runTime, dict, "U")
{
	setResultName(typeName, "U");
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::functionObjects::flowType::~flowType()
{}


// ************************************************************************* //