#include <cellZoneSet.hxx>

#include <mapPolyMesh.hxx>
#include <polyMesh.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

	defineTypeNameAndDebug(cellZoneSet, 0);

	addToRunTimeSelectionTable(topoSet, cellZoneSet, word);
	addToRunTimeSelectionTable(topoSet, cellZoneSet, size);
	addToRunTimeSelectionTable(topoSet, cellZoneSet, set);


	// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

	void cellZoneSet::updateSet()
	{
		labelList order;
		sortedOrder(addressing_, order);
		inplaceReorder(order, addressing_);

		cellSet::clearStorage();
		cellSet::resize(2 * addressing_.size());
		forAll(addressing_, i)
		{
			cellSet::insert(addressing_[i]);
		}
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	cellZoneSet::cellZoneSet
	(
		const polyMesh& mesh,
		const word& name,
		readOption r,
		writeOption w
	)
		:
		cellSet(mesh, name, 1000),  // do not read cellSet
		mesh_(mesh),
		addressing_(0)
	{
		const cellZoneMesh& cellZones = mesh.cellZones();
		label zoneID = cellZones.findZoneID(name);

		if
			(
			(r == IOobject::MUST_READ)
				|| (r == IOobject::MUST_READ_IF_MODIFIED)
				|| (r == IOobject::READ_IF_PRESENT && zoneID != -1)
				)
		{
			const cellZone& fz = cellZones[zoneID];
			addressing_ = fz;
		}

		updateSet();

		check(mesh.nCells());
	}


	cellZoneSet::cellZoneSet
	(
		const polyMesh& mesh,
		const word& name,
		const label size,
		writeOption w
	)
		:
		cellSet(mesh, name, size, w),
		mesh_(mesh),
		addressing_(0)
	{
		updateSet();
	}


	cellZoneSet::cellZoneSet
	(
		const polyMesh& mesh,
		const word& name,
		const topoSet& set,
		writeOption w
	)
		:
		cellSet(mesh, name, set.size(), w),
		mesh_(mesh),
		addressing_(refCast<const cellZoneSet>(set).addressing())
	{
		updateSet();
	}


	// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

	cellZoneSet::~cellZoneSet()
	{}


	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	void cellZoneSet::invert(const label maxLen)
	{
		// Count
		label n = 0;

		for (label celli = 0; celli < maxLen; celli++)
		{
			if (!found(celli))
			{
				n++;
			}
		}

		// Fill
		addressing_.setSize(n);
		n = 0;

		for (label celli = 0; celli < maxLen; celli++)
		{
			if (!found(celli))
			{
				addressing_[n] = celli;
				n++;
			}
		}

		updateSet();
	}


	void cellZoneSet::subset(const topoSet& set)
	{
		DynamicList<label> newAddressing(addressing_.size());

		const cellZoneSet& fSet = refCast<const cellZoneSet>(set);

		forAll(fSet.addressing(), i)
		{
			label celli = fSet.addressing()[i];

			if (found(celli))
			{
				newAddressing.append(celli);
			}
		}

		addressing_.transfer(newAddressing);
		updateSet();
	}


	void cellZoneSet::addSet(const topoSet& set)
	{
		DynamicList<label> newAddressing(addressing_);

		const cellZoneSet& fSet = refCast<const cellZoneSet>(set);

		forAll(fSet.addressing(), i)
		{
			label celli = fSet.addressing()[i];

			if (!found(celli))
			{
				newAddressing.append(celli);
			}
		}

		addressing_.transfer(newAddressing);
		updateSet();
	}


	void cellZoneSet::deleteSet(const topoSet& set)
	{
		DynamicList<label> newAddressing(addressing_.size());

		const cellZoneSet& fSet = refCast<const cellZoneSet>(set);

		forAll(addressing_, i)
		{
			label celli = addressing_[i];

			if (!fSet.found(celli))
			{
				// Not found in fSet so add
				newAddressing.append(celli);
			}
		}

		addressing_.transfer(newAddressing);
		updateSet();
	}


	void cellZoneSet::sync(const polyMesh& mesh)
	{
		cellSet::sync(mesh);

		// Take over contents of cellSet into addressing.
		addressing_ = sortedToc();
		updateSet();
	}


	label cellZoneSet::maxSize(const polyMesh& mesh) const
	{
		return mesh.nCells();
	}


	bool cellZoneSet::writeObject
	(
		IOstream::streamFormat s,
		IOstream::versionNumber v,
		IOstream::compressionType c,
		const bool write
	) const
	{
		// Write shadow cellSet
		word oldTypeName = typeName;
		const_cast<word&>(type()) = cellSet::typeName;
		bool ok = cellSet::writeObject(s, v, c, write);
		const_cast<word&>(type()) = oldTypeName;

		// Modify cellZone
		cellZoneMesh& cellZones = const_cast<polyMesh&>(mesh_).cellZones();
		label zoneID = cellZones.findZoneID(name());

		if (zoneID == -1)
		{
			zoneID = cellZones.size();

			cellZones.setSize(zoneID + 1);
			cellZones.set
			(
				zoneID,
				new cellZone
				(
					name(),
					addressing_,
					zoneID,
					cellZones
				)
			);
		}
		else
		{
			cellZones[zoneID] = addressing_;
		}
		cellZones.clearAddressing();

		return ok && cellZones.write(write);
	}


	void cellZoneSet::updateMesh(const mapPolyMesh& morphMap)
	{
		// cellZone
		labelList newAddressing(addressing_.size());

		label n = 0;
		forAll(addressing_, i)
		{
			label celli = addressing_[i];
			label newCelli = morphMap.reverseCellMap()[celli];
			if (newCelli >= 0)
			{
				newAddressing[n] = newCelli;
				n++;
			}
		}
		newAddressing.setSize(n);

		addressing_.transfer(newAddressing);

		updateSet();
	}


	void cellZoneSet::writeDebug
	(
		Ostream& os,
		const primitiveMesh& mesh,
		const label maxLen
	) const
	{
		cellSet::writeDebug(os, mesh, maxLen);
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //