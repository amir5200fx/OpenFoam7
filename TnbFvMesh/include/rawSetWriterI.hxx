#pragma once
#include <coordSet.hxx>
#include <fileName.hxx>
#include <OFstream.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::rawSetWriter<Type>::rawSetWriter()
	:
	writer<Type>()
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class Type>
tnbLib::rawSetWriter<Type>::~rawSetWriter()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
tnbLib::fileName tnbLib::rawSetWriter<Type>::getFileName
(
	const coordSet& points,
	const wordList& valueSetNames
) const
{
	return this->getBaseName(points, valueSetNames) + ".xy";
}


template<class Type>
void tnbLib::rawSetWriter<Type>::write
(
	const coordSet& points,
	const wordList& valueSetNames,
	const List<const Field<Type>*>& valueSets,
	Ostream& os
) const
{
	// Collect sets into columns
	List<const List<Type>*> columns(valueSets.size());

	forAll(valueSets, i)
	{
		columns[i] = valueSets[i];
	}

	this->writeTable(points, columns, os);
}


template<class Type>
void tnbLib::rawSetWriter<Type>::write
(
	const bool writeTracks,
	const PtrList<coordSet>& points,
	const wordList& valueSetNames,
	const List<List<Field<Type>>>& valueSets,
	Ostream& os
) const
{
	if (valueSets.size() != valueSetNames.size())
	{
		FatalErrorInFunction
			<< "Number of variables:" << valueSetNames.size() << endl
			<< "Number of valueSets:" << valueSets.size()
			<< exit(FatalError);
	}

	List<const List<Type>*> columns(valueSets.size());

	forAll(points, trackI)
	{
		// Collect sets into columns
		forAll(valueSets, i)
		{
			columns[i] = &valueSets[i][trackI];
		}

		this->writeTable(points[trackI], columns, os);
		os << nl << nl;
	}
}


// ************************************************************************* //