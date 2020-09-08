#pragma once
#include <polyMesh.hxx>
#include <mapPolyMesh.hxx>
#include <IOobjectList.hxx>

// * * * * * * * * * * * * * Public Member Functions * * * * * * * * * * * * //

template<class SetType>
void tnbLib::polyMeshFilter::updateSets(const mapPolyMesh& map)
{
	HashTable<const SetType*> sets =
		map.mesh().objectRegistry::lookupClass<const SetType>();

	forAllIter(typename HashTable<const SetType*>, sets, iter)
	{
		SetType& set = const_cast<SetType&>(*iter());
		set.updateMesh(map);
		set.sync(map.mesh());
	}

	IOobjectList Objects
	(
		map.mesh().time(),
		map.mesh().facesInstance(),
		"polyMesh/sets"
	);

	IOobjectList fileSets(Objects.lookupClass(SetType::typeName));

	forAllConstIter(IOobjectList, fileSets, iter)
	{
		if (!sets.found(iter.key()))
		{
			// Not in memory. Load it.
			SetType set(*iter());
			set.updateMesh(map);

			set.write();
		}
	}
}


template<class SetType>
void tnbLib::polyMeshFilter::copySets
(
	const polyMesh& oldMesh,
	const polyMesh& newMesh
)
{
	HashTable<const SetType*> sets =
		oldMesh.objectRegistry::lookupClass<const SetType>();

	forAllConstIter(typename HashTable<const SetType*>, sets, iter)
	{
		const SetType& set = *iter();

		if (newMesh.objectRegistry::foundObject<SetType>(set.name()))
		{
			const SetType& origSet =
				newMesh.objectRegistry::lookupObject<SetType>(set.name());

			const_cast<SetType&>(origSet) = set;
			const_cast<SetType&>(origSet).sync(newMesh);
		}
		else
		{
			SetType* newSet
			(
				new SetType(newMesh, set.name(), set, set.writeOpt())
			);

			newSet->store();
			newSet->sync(newMesh);
		}
	}
}


// ************************************************************************* //