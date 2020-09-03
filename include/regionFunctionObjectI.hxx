#pragma once
#include <objectRegistry.hxx>

// * * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * //

template<class ObjectType>
bool tnbLib::functionObjects::regionFunctionObject::foundObject
(
	const word& fieldName
) const
{
	return obr_.foundObject<ObjectType>(fieldName);
}


template<class ObjectType>
const ObjectType& tnbLib::functionObjects::regionFunctionObject::lookupObject
(
	const word& fieldName
) const
{
	return obr_.lookupObject<ObjectType>(fieldName);
}


template<class ObjectType>
ObjectType& tnbLib::functionObjects::regionFunctionObject::lookupObjectRef
(
	const word& fieldName
)
{
	return obr_.lookupObjectRef<ObjectType>(fieldName);
}


template<class ObjectType>
bool tnbLib::functionObjects::regionFunctionObject::store
(
	word& fieldName,
	const tmp<ObjectType>& tfield,
	bool cacheable
)
{
	if (cacheable && fieldName == tfield().name())
	{
		WarningInFunction
			<< "Cannot store cache-able field with the name used in the cache."
			<< nl
			<< "    Either choose a different name or cache the field"
			<< "    and use the 'writeObjects' functionObject."
			<< endl;

		return false;
	}

	if
		(
			fieldName.size()
			&& obr_.foundObject<ObjectType>(fieldName)
			)
	{
		ObjectType& field = obr_.lookupObjectRef<ObjectType>(fieldName);

		// If there is a result field already registered assign to the new
		// result field otherwise transfer ownership of the new result field to
		// the object registry
		if (&field != &tfield())
		{
			field = tfield;
		}
		else
		{
			obr_.objectRegistry::store(tfield.ptr());
		}
	}
	else
	{
		if (fieldName.size() && fieldName != tfield().name())
		{
			tfield.ref().rename(fieldName);
		}
		else
		{
			fieldName = tfield().name();
		}

		obr_.objectRegistry::store(tfield.ptr());
	}

	return true;
}


// ************************************************************************* //