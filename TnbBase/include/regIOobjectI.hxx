#pragma once
// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline bool tnbLib::regIOobject::ownedByRegistry() const
{
	return ownedByRegistry_;
}


inline void tnbLib::regIOobject::store()
{
	checkIn();
	ownedByRegistry_ = true;
}


template<class Type>
inline Type& tnbLib::regIOobject::store(Type* tPtr)
{
	if (!tPtr)
	{
		FatalErrorInFunction
			<< "object deallocated"
			<< abort(FatalError);
	}

	tPtr->regIOobject::checkIn();
	tPtr->regIOobject::ownedByRegistry_ = true;

	return *tPtr;
}


template<class Type>
inline Type& tnbLib::regIOobject::store(autoPtr<Type>& atPtr)
{
	Type* tPtr = atPtr.ptr();

	if (!tPtr)
	{
		FatalErrorInFunction
			<< "object deallocated"
			<< abort(FatalError);
	}

	tPtr->regIOobject::checkIn();
	tPtr->regIOobject::ownedByRegistry_ = true;

	return *tPtr;
}


inline void tnbLib::regIOobject::release()
{
	ownedByRegistry_ = false;
}


inline tnbLib::label tnbLib::regIOobject::eventNo() const
{
	return eventNo_;
}

inline tnbLib::label& tnbLib::regIOobject::eventNo()
{
	return eventNo_;
}


inline const tnbLib::labelList& tnbLib::regIOobject::watchIndices() const
{
	return watchIndices_;
}


inline tnbLib::labelList& tnbLib::regIOobject::watchIndices()
{
	return watchIndices_;
}


// ************************************************************************* //