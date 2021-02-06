#include <Qdot.hxx>

#include <combustionModel.hxx>
#include <volFields.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionObjects
	{
		defineTypeNameAndDebug(Qdot, 0);

		addToRunTimeSelectionTable
		(
			functionObject,
			Qdot,
			dictionary
		);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::functionObjects::Qdot::Qdot
(
	const word& name,
	const Time& runTime,
	const dictionary& dict
)
	:
	fvMeshFunctionObject(name, runTime, dict),
	writeLocalObjects(obr_, false),
	phaseName_(word::null)
{
	read(dict);
	resetLocalObjectName(IOobject::groupName(type(), phaseName_));
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::functionObjects::Qdot::~Qdot()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::functionObjects::Qdot::read
(
	const dictionary& dict
)
{
	fvMeshFunctionObject::read(dict);
	writeLocalObjects::read(dict);

	phaseName_ = dict.lookupOrDefault<word>("phase", word::null);

	return true;
}


bool tnbLib::functionObjects::Qdot::execute()
{
	word fieldName(IOobject::groupName(type(), phaseName_));

	const word modelName
	(
		IOobject::groupName
		(
			combustionModel::combustionPropertiesName,
			phaseName_
		)
	);

	return
		store
		(
			fieldName,
			mesh_.lookupObject<combustionModel>(modelName).Qdot()
		);
}


bool tnbLib::functionObjects::Qdot::write()
{
	return writeLocalObjects::write();
}


// ************************************************************************* //