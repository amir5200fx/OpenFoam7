#pragma once
#include <Time.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class OutputFilter>
tnbLib::IOOutputFilter<OutputFilter>::IOOutputFilter
(
	const word& outputFilterName,
	const IOobject& ioDict,
	const bool readFromFiles
)
	:
	IOdictionary(ioDict),
	OutputFilter(outputFilterName, ioDict.db(), *this, readFromFiles)
{}


template<class OutputFilter>
tnbLib::IOOutputFilter<OutputFilter>::IOOutputFilter
(
	const word& outputFilterName,
	const objectRegistry& obr,
	const word& dictName,
	const IOobject::readOption rOpt,
	const bool readFromFiles
)
	:
	IOdictionary
	(
		IOobject
		(
			dictName,
			obr.time().system(),
			obr,
			rOpt,
			IOobject::NO_WRITE
		)
	),
	OutputFilter(outputFilterName, obr, *this, readFromFiles)
{}


template<class OutputFilter>
tnbLib::IOOutputFilter<OutputFilter>::IOOutputFilter
(
	const word& outputFilterName,
	const objectRegistry& obr,
	const fileName& dictName,
	const IOobject::readOption rOpt,
	const bool readFromFiles
)
	:
	IOdictionary
	(
		IOobject
		(
			dictName,
			obr,
			rOpt,
			IOobject::NO_WRITE
		)
	),
	OutputFilter(outputFilterName, obr, *this, readFromFiles)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class OutputFilter>
tnbLib::IOOutputFilter<OutputFilter>::~IOOutputFilter()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class OutputFilter>
const tnbLib::word& tnbLib::IOOutputFilter<OutputFilter>::name() const
{
	return IOdictionary::name();
}


template<class OutputFilter>
bool tnbLib::IOOutputFilter<OutputFilter>::read()
{
	if (regIOobject::read())
	{
		OutputFilter::read(*this);
		return true;
	}
	else
	{
		return false;
	}
}


template<class OutputFilter>
bool tnbLib::IOOutputFilter<OutputFilter>::write(const bool write)
{
	return OutputFilter::write(write);
}


template<class OutputFilter>
void tnbLib::IOOutputFilter<OutputFilter>::updateMesh(const mapPolyMesh& mpm)
{
	read();
	OutputFilter::updateMesh(mpm);
}


template<class OutputFilter>
void tnbLib::IOOutputFilter<OutputFilter>::movePoints(const polyMesh& mesh)
{
	read();
	OutputFilter::movePoints(mesh);
}


// ************************************************************************* //