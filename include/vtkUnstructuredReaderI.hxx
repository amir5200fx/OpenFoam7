#pragma once
#include <labelIOField.hxx>
#include <scalarIOField.hxx>
#include <stringIOList.hxx>
#include <cellModeller.hxx>
#include <vectorIOField.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<class T>
void tnbLib::vtkUnstructuredReader::readBlock
(
	Istream& inFile,
	const label n,
	List<T>& lst
) const
{
	lst.setSize(n);
	forAll(lst, i)
	{
		inFile >> lst[i];
	}
}


template<class Type>
void tnbLib::vtkUnstructuredReader::printFieldStats
(
	const objectRegistry& obj
) const
{
	wordList fieldNames(obj.names(Type::typeName));

	if (fieldNames.size() > 0)
	{
		Info << "Read " << fieldNames.size() << " " << Type::typeName
			<< " fields:" << endl;
		Info << "Size\tName" << nl
			<< "----\t----" << endl;
		forAll(fieldNames, i)
		{
			Info << obj.lookupObject<Type>(fieldNames[i]).size()
				<< "\t" << fieldNames[i]
				<< endl;
		}
		Info << endl;
	}
}


// ************************************************************************* //