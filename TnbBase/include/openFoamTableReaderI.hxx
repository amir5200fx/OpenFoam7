#pragma once
#include <fileOperation.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::openFoamTableReader<Type>::openFoamTableReader(const dictionary& dict)
	:
	tableReader<Type>(dict)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class Type>
tnbLib::openFoamTableReader<Type>::~openFoamTableReader()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
void tnbLib::openFoamTableReader<Type>::operator()
(
	const fileName& fName,
	List<Tuple2<scalar, Type>>& data
	)
{
	// Read data from file
	fileHandler().NewIFstream(fName)()() >> data;
}


template<class Type>
void tnbLib::openFoamTableReader<Type>::operator()
(
	const fileName& fName,
	List<Tuple2<scalar, List<Tuple2<scalar, Type>>>>& data
	)
{
	// Read data from file
	fileHandler().NewIFstream(fName)()() >> data;
}


// ************************************************************************* //