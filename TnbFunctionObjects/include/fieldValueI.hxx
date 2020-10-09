#pragma once
#include <fvMesh.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline const tnbLib::dictionary& tnbLib::functionObjects::fieldValue::dict() const
{
	return dict_;
}


inline const tnbLib::word& tnbLib::functionObjects::fieldValue::regionName() const
{
	return regionName_;
}


inline const tnbLib::wordList& tnbLib::functionObjects::fieldValue::fields() const
{
	return fields_;
}


inline const tnbLib::Switch&
tnbLib::functionObjects::fieldValue::writeFields() const
{
	return writeFields_;
}


inline const tnbLib::dictionary&
tnbLib::functionObjects::fieldValue::resultDict() const
{
	return resultDict_;
}


// ************************************************************************* //