#pragma once
#include <coordSet.hxx>
#include <fileName.hxx>
#include <OFstream.hxx>
#include <token.hxx>  // added by amir

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::csvSetWriter<Type>::csvSetWriter()
	:
	writer<Type>()
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class Type>
tnbLib::csvSetWriter<Type>::~csvSetWriter()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
tnbLib::fileName tnbLib::csvSetWriter<Type>::getFileName
(
	const coordSet& points,
	const wordList& valueSetNames
) const
{
	return this->getBaseName(points, valueSetNames) + ".csv";
}


template<class Type>
void tnbLib::csvSetWriter<Type>::write
(
	const coordSet& points,
	const wordList& valueSetNames,
	const List<const Field<Type>*>& valueSets,
	Ostream& os
) const
{
	writeHeader(points, valueSetNames, os);

	// Collect sets into columns
	List<const List<Type>*> columns(valueSets.size());

	forAll(valueSets, i)
	{
		columns[i] = valueSets[i];
	}

	this->writeTable(points, columns, os);
}


template<class Type>
void tnbLib::csvSetWriter<Type>::write
(
	const bool writeTracks,
	const PtrList<coordSet>& points,
	const wordList& valueSetNames,
	const List<List<Field<Type>>>& valueSets,
	Ostream& os
) const
{
	writeHeader(points[0], valueSetNames, os);

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


template<class Type>
void tnbLib::csvSetWriter<Type>::writeSeparator(Ostream& os) const
{
	os << token::COMMA;
}


namespace tnbLib
{
	// otherwise compiler complains about specialization
	template<>
	void csvSetWriter<scalar>::writeHeader
	(
		const coordSet& points,
		const wordList& valueSetNames,
		Ostream& os
	) const
	{
		writeCoordHeader(points, os);

		forAll(valueSetNames, i)
		{
			if (i > 0)
			{
				writeSeparator(os);
			}
			os << valueSetNames[i];
		}

		os << nl;
	}
}


template<class Type>
void tnbLib::csvSetWriter<Type>::writeHeader
(
	const coordSet& points,
	const wordList& valueSetNames,
	Ostream& os
) const
{
	writeCoordHeader(points, os);

	forAll(valueSetNames, i)
	{
		for (label j = 0; j < Type::nComponents; j++)
		{
			if (i > 0 || j > 0)
			{
				writeSeparator(os);
			}
			os << valueSetNames[i] << "_" << j;
		}
	}

	os << nl;
}


template<class Type>
void tnbLib::csvSetWriter<Type>::writeCoordHeader
(
	const coordSet& points,
	Ostream& os
) const
{
	const word axisName(points.axis());

	if (points.hasVectorAxis())
	{
		for
			(
				word::const_iterator iter = axisName.begin();
				iter != axisName.end();
				++iter
				)
		{
			os << *iter;
			writeSeparator(os);
		}
	}
	else
	{
		os << axisName;
		writeSeparator(os);
	}
}


// ************************************************************************* //