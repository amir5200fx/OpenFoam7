#include <removeRegisteredObject.hxx>

#include <Time.hxx>
#include <polyMesh.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionObjects
	{
		defineTypeNameAndDebug(removeRegisteredObject, 0);

		addToRunTimeSelectionTable
		(
			functionObject,
			removeRegisteredObject,
			dictionary
		);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::functionObjects::removeRegisteredObject::removeRegisteredObject
(
	const word& name,
	const Time& runTime,
	const dictionary& dict
)
	:
	functionObject(name),
	obr_
	(
		runTime.lookupObject<objectRegistry>
		(
			dict.lookupOrDefault("region", polyMesh::defaultRegion)
			)
	),
	objectNames_()
{
	read(dict);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::functionObjects::removeRegisteredObject::~removeRegisteredObject()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::functionObjects::removeRegisteredObject::read(const dictionary& dict)
{
	dict.lookup("objects") >> objectNames_;

	return true;
}


bool tnbLib::functionObjects::removeRegisteredObject::execute()
{
	forAll(objectNames_, i)
	{
		if (obr_.foundObject<regIOobject>(objectNames_[i]))
		{
			regIOobject& obj =
				obr_.lookupObjectRef<regIOobject>(objectNames_[i]);

			if (obj.ownedByRegistry())
			{
				Info << type() << " " << name() << " write:" << nl
					<< "    removing object " << obj.name() << nl
					<< endl;

				obj.release();
				delete &obj;
			}
		}
	}

	return true;
}


bool tnbLib::functionObjects::removeRegisteredObject::write()
{
	return true;
}


// ************************************************************************* //