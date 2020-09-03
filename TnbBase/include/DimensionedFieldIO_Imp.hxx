#pragma once
#include <IOstreams.hxx>
#include <dictionary.hxx> // added by amir

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<class Type, class GeoMesh>
void tnbLib::DimensionedField<Type, GeoMesh>::readField
(
	const dictionary& fieldDict,
	const word& fieldDictEntry
)
{
	dimensions_.reset(dimensionSet(fieldDict.lookup("dimensions")));

	Field<Type> f(fieldDictEntry, fieldDict, GeoMesh::size(mesh_));
	this->transfer(f);
}


template<class Type, class GeoMesh>
void tnbLib::DimensionedField<Type, GeoMesh>::readIfPresent
(
	const word& fieldDictEntry
)
{
	if
		(
		(this->readOpt() == IOobject::READ_IF_PRESENT && this->headerOk())
			|| this->readOpt() == IOobject::MUST_READ
			|| this->readOpt() == IOobject::MUST_READ_IF_MODIFIED
			)
	{
		readField(dictionary(readStream(typeName)), fieldDictEntry);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type, class GeoMesh>
tnbLib::DimensionedField<Type, GeoMesh>::DimensionedField
(
	const IOobject& io,
	const Mesh& mesh,
	const word& fieldDictEntry
)
	:
	regIOobject(io),
	Field<Type>(0),
	mesh_(mesh),
	dimensions_(dimless)
{
	readField(dictionary(readStream(typeName)), fieldDictEntry);
}


template<class Type, class GeoMesh>
tnbLib::DimensionedField<Type, GeoMesh>::DimensionedField
(
	const IOobject& io,
	const Mesh& mesh,
	const dictionary& fieldDict,
	const word& fieldDictEntry
)
	:
	regIOobject(io),
	Field<Type>(0),
	mesh_(mesh),
	dimensions_(dimless)
{
	readField(fieldDict, fieldDictEntry);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type, class GeoMesh>
bool tnbLib::DimensionedField<Type, GeoMesh>::writeData
(
	Ostream& os,
	const word& fieldDictEntry
) const
{
	writeEntry(os, "dimensions", dimensions());
	os << nl;

	writeEntry(os, fieldDictEntry, static_cast<const Field<Type>&>(*this));

	// Check state of Ostream
	os.check
	(
		"bool DimensionedField<Type, GeoMesh>::writeData"
		"(Ostream& os, const word& fieldDictEntry) const"
	);

	return (os.good());
}


template<class Type, class GeoMesh>
bool tnbLib::DimensionedField<Type, GeoMesh>::writeData(Ostream& os) const
{
	return writeData(os, "value");
}


// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

template<class Type, class GeoMesh>
tnbLib::Ostream& tnbLib::operator<<
(
	Ostream& os,
	const DimensionedField<Type, GeoMesh>& df
	)
{
	df.writeData(os);

	return os;
}


template<class Type, class GeoMesh>
tnbLib::Ostream& tnbLib::operator<<
(
	Ostream& os,
	const tmp<DimensionedField<Type, GeoMesh>>& tdf
	)
{
	tdf().writeData(os);
	tdf.clear();

	return os;
}


// ************************************************************************* //