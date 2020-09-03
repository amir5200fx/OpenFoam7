#pragma once
#include <INew.hxx> // added by amir

// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

template<class T>
template<class INew>
tnbLib::IOPtrList<T>::IOPtrList(const IOobject& io, const INew& inewt)
	:
	regIOobject(io)
{
	if
		(
		(
			io.readOpt() == IOobject::MUST_READ
			|| io.readOpt() == IOobject::MUST_READ_IF_MODIFIED
			)
			|| (io.readOpt() == IOobject::READ_IF_PRESENT && headerOk())
			)
	{
		// For if MUST_READ_IF_MODIFIED
		addWatch();

		PtrList<T>::read(readStream(typeName), inewt);
		close();
	}
}


template<class T>
tnbLib::IOPtrList<T>::IOPtrList(const IOobject& io)
	:
	regIOobject(io)
{
	if
		(
		(
			io.readOpt() == IOobject::MUST_READ
			|| io.readOpt() == IOobject::MUST_READ_IF_MODIFIED
			)
			|| (io.readOpt() == IOobject::READ_IF_PRESENT && headerOk())
			)
	{
		// For if MUST_READ_IF_MODIFIED
		addWatch();

		PtrList<T>::read(readStream(typeName), INew<T>());
		close();
	}
}


template<class T>
tnbLib::IOPtrList<T>::IOPtrList(const IOobject& io, const label s)
	:
	regIOobject(io),
	PtrList<T>(s)
{
	if (io.readOpt() != IOobject::NO_READ)
	{
		FatalErrorInFunction
			<< "NO_READ must be set if specifying size" << nl
			<< exit(FatalError);
	}
}


template<class T>
tnbLib::IOPtrList<T>::IOPtrList(const IOobject& io, const PtrList<T>& list)
	:
	regIOobject(io)
{
	if
		(
		(
			io.readOpt() == IOobject::MUST_READ
			|| io.readOpt() == IOobject::MUST_READ_IF_MODIFIED
			)
			|| (io.readOpt() == IOobject::READ_IF_PRESENT && headerOk())
			)
	{
		// For if MUST_READ_IF_MODIFIED
		addWatch();

		PtrList<T>::read(readStream(typeName), INew<T>());
		close();
	}
	else
	{
		PtrList<T>::operator=(list);
	}
}


template<class T>
tnbLib::IOPtrList<T>::IOPtrList(const IOobject& io, PtrList<T>&& list)
	:
	regIOobject(io),
	PtrList<T>(move(list))
{
	if
		(
		(
			io.readOpt() == IOobject::MUST_READ
			|| io.readOpt() == IOobject::MUST_READ_IF_MODIFIED
			)
			|| (io.readOpt() == IOobject::READ_IF_PRESENT && headerOk())
			)
	{
		// For if MUST_READ_IF_MODIFIED
		addWatch();

		PtrList<T>::read(readStream(typeName), INew<T>());
		close();
	}
}


template<class T>
tnbLib::IOPtrList<T>::IOPtrList(IOPtrList<T>&& list)
	:
	regIOobject(move(list)),
	PtrList<T>(move(list))
{}


// * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * * //

template<class T>
tnbLib::IOPtrList<T>::~IOPtrList()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class T>
bool tnbLib::IOPtrList<T>::writeData(Ostream& os) const
{
	return (os << *this).good();
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

template<class T>
void tnbLib::IOPtrList<T>::operator=(const IOPtrList<T>& rhs)
{
	PtrList<T>::operator=(rhs);
}


template<class T>
void tnbLib::IOPtrList<T>::operator=(IOPtrList<T>&& rhs)
{
	PtrList<T>::operator=(move(rhs));
}


// ************************************************************************* //