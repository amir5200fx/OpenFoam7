#pragma once
#include <IOmanip.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<class GeoField>
void tnbLib::addToFieldList
(
	PtrList<GeoField>& fieldList,
	const IOobject& obj,
	const label fieldi,
	const typename GeoField::Mesh& mesh
)
{
	if (obj.headerClassName() == GeoField::typeName)
	{
		fieldList.set
		(
			fieldi,
			new GeoField(obj, mesh)
		);
		Info << "    " << GeoField::typeName << tab << obj.name() << endl;
	}
}


template<class GeoField>
void tnbLib::outputFieldList
(
	const PtrList<GeoField>& fieldList,
	const label patchi
)
{
	forAll(fieldList, fieldi)
	{
		if (fieldList.set(fieldi))
		{
			Info << "    " << pTraits<typename GeoField::value_type>::typeName
				<< tab << tab
				<< fieldList[fieldi].name() << tab << tab
				<< fieldList[fieldi].boundaryField()[patchi].type() << nl;
		}
	}
}


template<class GeoField>
void tnbLib::collectFieldList
(
	const PtrList<GeoField>& fieldList,
	const label patchi,
	HashTable<word>& fieldToType
)
{
	forAll(fieldList, fieldi)
	{
		if (fieldList.set(fieldi))
		{
			fieldToType.insert
			(
				fieldList[fieldi].name(),
				fieldList[fieldi].boundaryField()[patchi].type()
			);
		}
	}
}


// ************************************************************************* //