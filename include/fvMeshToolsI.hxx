#pragma once
#include <volFields.hxx>
#include <surfaceFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<class GeoField>
void tnbLib::fvMeshTools::setPatchFields
(
	typename GeoField::Mesh& mesh,
	const label patchi,
	const dictionary& patchFieldDict
)
{
	objectRegistry& obr = const_cast<objectRegistry&>(mesh.thisDb());

	HashTable<GeoField*> flds(obr.lookupClass<GeoField>());

	forAllIter(typename HashTable<GeoField*>, flds, iter)
	{
		GeoField& fld = *iter();

		typename GeoField::Boundary& bfld =
			fld.boundaryFieldRef();

		if (patchFieldDict.found(fld.name()))
		{
			bfld.set
			(
				patchi,
				GeoField::Patch::New
				(
					mesh.boundary()[patchi],
					fld(),
					patchFieldDict.subDict(fld.name())
				)
			);
		}
	}
}


template<class GeoField>
void tnbLib::fvMeshTools::setPatchFields
(
	typename GeoField::Mesh& mesh,
	const label patchi,
	const typename GeoField::value_type& value
)
{
	objectRegistry& obr = const_cast<objectRegistry&>(mesh.thisDb());

	HashTable<GeoField*> flds(obr.lookupClass<GeoField>());

	forAllIter(typename HashTable<GeoField*>, flds, iter)
	{
		GeoField& fld = *iter();

		typename GeoField::Boundary& bfld =
			fld.boundaryFieldRef();

		bfld[patchi] == value;
	}
}


// ************************************************************************* //