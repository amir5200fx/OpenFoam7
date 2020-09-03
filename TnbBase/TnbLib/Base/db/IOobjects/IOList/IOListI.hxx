#pragma once
// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

template<class T>
tnbLib::IOList<T>::IOList(const IOobject& io)
	:
	regIOobject(io)
{
	// Check for MUST_READ_IF_MODIFIED
	warnNoRereading<IOList<T>>();

	if
		(
		(
			io.readOpt() == IOobject::MUST_READ
			|| io.readOpt() == IOobject::MUST_READ_IF_MODIFIED
			)
			|| (io.readOpt() == IOobject::READ_IF_PRESENT && headerOk())
			)
	{
		readStream(typeName) >> *this;
		close();
	}
}


template<class T>
tnbLib::IOList<T>::IOList(const IOobject& io, const label size)
	:
	regIOobject(io)
{
	// Check for MUST_READ_IF_MODIFIED
	warnNoRereading<IOList<T>>();

	if
		(
		(
			io.readOpt() == IOobject::MUST_READ
			|| io.readOpt() == IOobject::MUST_READ_IF_MODIFIED
			)
			|| (io.readOpt() == IOobject::READ_IF_PRESENT && headerOk())
			)
	{
		readStream(typeName) >> *this;
		close();
	}
	else
	{
		List<T>::setSize(size);
	}
}


template<class T>
tnbLib::IOList<T>::IOList(const IOobject& io, const List<T>& list)
	:
	regIOobject(io)
{
	// Check for MUST_READ_IF_MODIFIED
	warnNoRereading<IOList<T>>();

	if
		(
		(
			io.readOpt() == IOobject::MUST_READ
			|| io.readOpt() == IOobject::MUST_READ_IF_MODIFIED
			)
			|| (io.readOpt() == IOobject::READ_IF_PRESENT && headerOk())
			)
	{
		readStream(typeName) >> *this;
		close();
	}
	else
	{
		List<T>::operator=(list);
	}
}


template<class T>
tnbLib::IOList<T>::IOList(const IOobject& io, List<T>&& list)
	:
	regIOobject(io),
	List<T>(move(list))
{
	// Check for MUST_READ_IF_MODIFIED
	warnNoRereading<IOList<T>>();

	if
		(
		(
			io.readOpt() == IOobject::MUST_READ
			|| io.readOpt() == IOobject::MUST_READ_IF_MODIFIED
			)
			|| (io.readOpt() == IOobject::READ_IF_PRESENT && headerOk())
			)
	{
		readStream(typeName) >> *this;
		close();
	}
}


//template<class T>
//tnbLib::IOList<T>::IOList(const IOList<T>& f)
//	:
//	regIOobject(f),
//	List<T>(f)
//{}


//template<class T>
//tnbLib::IOList<T>::IOList(IOList<T>&& f)
//	:
//	regIOobject(move(f)),
//	List<T>(move(f))
//{}


// * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * * //

template<class T>
tnbLib::IOList<T>::~IOList()
{}



// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class T>
bool tnbLib::IOList<T>::writeData(Ostream& os) const
{
	return (os << *this).good();
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

template<class T>
void tnbLib::IOList<T>::operator=(const IOList<T>& rhs)
{
	List<T>::operator=(rhs);
}


template<class T>
void tnbLib::IOList<T>::operator=(IOList<T>&& rhs)
{
	List<T>::operator=(move(rhs));
}


template<class T>
void tnbLib::IOList<T>::operator=(const List<T>& rhs)
{
	List<T>::operator=(rhs);
}


template<class T>
void tnbLib::IOList<T>::operator=(List<T>&& rhs)
{
	List<T>::operator=(move(rhs));
}


// ************************************************************************* //