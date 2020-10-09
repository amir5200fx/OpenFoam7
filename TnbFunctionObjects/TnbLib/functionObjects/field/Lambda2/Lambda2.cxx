#include <Lambda2.hxx>

#include <fvcGrad.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionObjects
	{
		defineTypeNameAndDebug(Lambda2, 0);

		addToRunTimeSelectionTable
		(
			functionObject,
			Lambda2,
			dictionary
		);
	}
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

bool tnbLib::functionObjects::Lambda2::calc()
{
	if (foundObject<volVectorField>(fieldName_))
	{
		const volVectorField& U = lookupObject<volVectorField>(fieldName_);
		const tmp<volTensorField> tgradU(fvc::grad(U));
		const volTensorField& gradU = tgradU();

		const volTensorField SSplusWW
		(
			(symm(gradU) & symm(gradU))
			+ (skew(gradU) & skew(gradU))
		);

		return store
		(
			resultName_,
			-eigenValues(SSplusWW)().component(vector::Y)
		);
	}
	else
	{
		return false;
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::functionObjects::Lambda2::Lambda2
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

tnbLib::functionObjects::Lambda2::~Lambda2()
{}


// ************************************************************************* //