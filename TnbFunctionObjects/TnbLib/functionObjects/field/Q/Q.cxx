#include <Q.hxx>

#include <fvcGrad.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionObjects
	{
		defineTypeNameAndDebug(Q, 0);

		addToRunTimeSelectionTable
		(
			functionObject,
			Q,
			dictionary
		);
	}
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

bool tnbLib::functionObjects::Q::calc()
{
	if (foundObject<volVectorField>(fieldName_))
	{
		const volVectorField& U = lookupObject<volVectorField>(fieldName_);
		const tmp<volTensorField> tgradU(fvc::grad(U));
		const volTensorField& gradU = tgradU();

		return store
		(
			resultName_,
			0.5*(sqr(tr(gradU)) - tr(((gradU) & (gradU))))
		);
	}
	else
	{
		return false;
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::functionObjects::Q::Q
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

tnbLib::functionObjects::Q::~Q()
{}


// ************************************************************************* //