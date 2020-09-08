#pragma once
#include <polyMesh.hxx>
#include <Time.hxx>
#include <mapPolyMesh.hxx>
#include <IOobjectList.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
void tnbLib::setUpdater::updateSets(const mapPolyMesh& morphMap) const
{
	//
	// Update all sets in memory.
	//

	HashTable<const Type*> memSets =
		morphMap.mesh().objectRegistry::lookupClass<Type>();

	forAllIter(typename HashTable<const Type*>, memSets, iter)
	{
		Type& set = const_cast<Type&>(*iter());

		if (debug)
		{
			Pout << "Set:" << set.name() << " size:" << set.size()
				<< " updated in memory" << endl;
		}

		set.updateMesh(morphMap);

		// Write or not? Debatable.
		set.write();
	}


	//
	// Update all sets on disk
	//

	// Get last valid mesh (discard points-only change)
	IOobjectList Objects
	(
		morphMap.mesh().time(),
		morphMap.mesh().facesInstance(),
		"polyMesh/sets"
	);

	IOobjectList fileSets(Objects.lookupClass(Type::typeName));

	forAllConstIter(IOobjectList, fileSets, iter)
	{
		if (!memSets.found(iter.key()))
		{
			// Not in memory. Load it.
			Type set(*iter());

			if (debug)
			{
				Pout << "Set:" << set.name() << " size:" << set.size()
					<< " updated on disk" << endl;
			}

			set.updateMesh(morphMap);

			set.write();
		}
		else
		{
			if (debug)
			{
				Pout << "Set:" << iter.key() << " already updated from memory"
					<< endl;
			}
		}
	}
}


// ************************************************************************* //