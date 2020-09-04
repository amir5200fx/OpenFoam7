#pragma once
#include <coordSet.hxx>
#include <OFstream.hxx>
#include <OSspecific.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

template<class Type>
tnbLib::autoPtr<tnbLib::writer<Type>> tnbLib::writer<Type>::New
(
	const word& writeType
)
{
	typename wordConstructorTable::iterator cstrIter =
		wordConstructorTablePtr_->find(writeType);

	if (cstrIter == wordConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown write type "
			<< writeType << nl << nl
			<< "Valid write types : " << endl
			<< wordConstructorTablePtr_->sortedToc()
			<< exit(FatalError);
	}

	return autoPtr<writer<Type>>(cstrIter()());
}


// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

template<class Type>
tnbLib::fileName tnbLib::writer<Type>::getBaseName
(
	const coordSet& points,
	const wordList& valueSets
) const
{
	fileName fName(points.name());

	forAll(valueSets, i)
	{
		fName += '_' + valueSets[i];
	}

	return fName;
}


template<class Type>
void tnbLib::writer<Type>::writeCoord
(
	const coordSet& points,
	const label pointi,
	Ostream& os
) const
{
	if (points.hasVectorAxis())
	{
		write(points.vectorCoord(pointi), os);
	}
	else
	{
		write(points.scalarCoord(pointi), os);
	}
}


template<class Type>
void tnbLib::writer<Type>::writeTable
(
	const coordSet& points,
	const List<Type>& values,
	Ostream& os
) const
{
	forAll(points, pointi)
	{
		writeCoord(points, pointi, os);
		writeSeparator(os);
		write(values[pointi], os);
		os << nl;
	}
}


template<class Type>
void tnbLib::writer<Type>::writeTable
(
	const coordSet& points,
	const List<const List<Type>*>& valuesPtrList,
	Ostream& os
) const
{
	forAll(points, pointi)
	{
		writeCoord(points, pointi, os);

		forAll(valuesPtrList, i)
		{
			writeSeparator(os);

			const List<Type>& values = *valuesPtrList[i];
			write(values[pointi], os);
		}
		os << nl;
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::writer<Type>::writer()
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class Type>
tnbLib::writer<Type>::~writer()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
void tnbLib::writer<Type>::write
(
	const coordSet& points,
	const wordList& valueSetNames,
	const List<Field<Type>>& valueSets,
	Ostream& os
) const
{
	List<const Field<Type>*> valueSetPtrs(valueSets.size());
	forAll(valueSetPtrs, i)
	{
		valueSetPtrs[i] = &valueSets[i];
	}
	write(points, valueSetNames, valueSetPtrs, os);
}


template<class Type>
tnbLib::Ostream& tnbLib::writer<Type>::write
(
	const scalar value,
	Ostream& os
) const
{
	return os << value;
}


template<class Type>
template<class VSType>
tnbLib::Ostream& tnbLib::writer<Type>::writeVS
(
	const VSType& value,
	Ostream& os
) const
{
	for (direction d = 0; d < VSType::nComponents; d++)
	{
		if (d > 0)
		{
			writeSeparator(os);
		}

		os << value.component(d);
	}
	return os;
}


template<class Type>
void tnbLib::writer<Type>::writeSeparator
(
	Ostream& os
) const
{
	os << token::SPACE << token::TAB;
}


template<class Type>
tnbLib::Ostream& tnbLib::writer<Type>::write
(
	const vector& value,
	Ostream& os
) const
{
	return writeVS(value, os);
}


template<class Type>
tnbLib::Ostream& tnbLib::writer<Type>::write
(
	const sphericalTensor& value,
	Ostream& os
) const
{
	return writeVS(value, os);
}


template<class Type>
tnbLib::Ostream& tnbLib::writer<Type>::write
(
	const symmTensor& value,
	Ostream& os
) const
{
	return writeVS(value, os);
}


template<class Type>
tnbLib::Ostream& tnbLib::writer<Type>::write
(
	const tensor& value,
	Ostream& os
) const
{
	return writeVS(value, os);
}


// ************************************************************************* //