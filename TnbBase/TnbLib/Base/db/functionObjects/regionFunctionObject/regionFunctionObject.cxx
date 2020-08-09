#include <regionFunctionObject.hxx>

#include <Time.hxx>
#include <polyMesh.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionObjects
	{
		defineTypeNameAndDebug(regionFunctionObject, 0);
	}
}


// * * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * //

//bool tnbLib::functionObjects::regionFunctionObject::writeObject
//(
//	const word& fieldName
//)
//{
//	if (obr_.foundObject<regIOobject>(fieldName))
//	{
//		const regIOobject& field = obr_.lookupObject<regIOobject>(fieldName);
//
//		Log << "    functionObjects::" << type() << " " << name()
//			<< " writing field: " << field.name() << endl;
//
//		field.write();
//
//		return true;
//	}
//	else
//	{
//		return false;
//	}
//}


bool tnbLib::functionObjects::regionFunctionObject::clearObject
(
	const word& fieldName
)
{
	if (foundObject<regIOobject>(fieldName))
	{
		regIOobject& resultObject = lookupObjectRef<regIOobject>(fieldName);

		if (resultObject.ownedByRegistry())
		{
			return resultObject.checkOut();
		}
		else
		{
			return false;
		}
	}
	else
	{
		return true;
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::functionObjects::regionFunctionObject::regionFunctionObject
(
	const word& name,
	const Time& runTime,
	const dictionary& dict
)
	:
	functionObject(name),
	time_(runTime),
	obr_
	(
		runTime.lookupObject<objectRegistry>
		(
			dict.lookupOrDefault("region", polyMesh::defaultRegion)
			)
	)
{}


tnbLib::functionObjects::regionFunctionObject::regionFunctionObject
(
	const word& name,
	const objectRegistry& obr,
	const dictionary& dict
)
	:
	functionObject(name),
	time_(obr.time()),
	obr_(obr)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::functionObjects::regionFunctionObject::~regionFunctionObject()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::functionObjects::regionFunctionObject::read(const dictionary& dict)
{
	return functionObject::read(dict);
}


// ************************************************************************* //