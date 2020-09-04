#pragma once
// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

template<class Face>
void tnbLib::MeshedSurface<Face>::checkZones()
{
	// extra safety, ensure we have at some zones
	// and they cover all the faces - fix start silently
	surfZoneList& zones = this->storedZones();
	if (zones.size())
	{
		label count = 0;
		forAll(zones, zoneI)
		{
			zones[zoneI].start() = count;
			count += zones[zoneI].size();
		}

		if (count < this->size())
		{
			WarningInFunction
				<< "more faces " << this->size() << " than zones " << count
				<< " ... extending final zone"
				<< endl;

			zones.last().size() += count - this->size();
		}
		else if (count > this->size())
		{
			FatalErrorInFunction
				<< "more zones " << count << " than faces " << this->size()
				<< exit(FatalError);
		}
	}
}


template<class Face>
void tnbLib::MeshedSurface<Face>::sortFacesAndStore
(
	List<Face>&& unsortedFaces,
	List<label>&& zoneIds,
	const bool sorted
)
{
	List<Face>  oldFaces(unsortedFaces);
	List<label> zones(zoneIds);

	if (sorted)
	{
		// already sorted - simply transfer faces
		this->storedFaces().transfer(oldFaces);
	}
	else
	{
		// unsorted - determine the sorted order:
		// avoid SortableList since we discard the main list anyhow
		List<label> faceMap;
		sortedOrder(zones, faceMap);
		zones.clear();

		// sorted faces
		List<Face> newFaces(faceMap.size());
		forAll(faceMap, facei)
		{
			// use transfer to recover memory where possible
			newFaces[facei].transfer(oldFaces[faceMap[facei]]);
		}
		this->storedFaces().transfer(newFaces);
	}
	zones.clear();
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Face>
void tnbLib::MeshedSurface<Face>::addZones
(
	const UList<surfZone>& srfZones,
	const bool cullEmpty
)
{
	label nZone = 0;

	surfZoneList& zones = this->storedZones();
	zones.setSize(zones.size());
	forAll(zones, zoneI)
	{
		if (srfZones[zoneI].size() || !cullEmpty)
		{
			zones[nZone] = surfZone(srfZones[zoneI], nZone);
			nZone++;
		}
	}
	zones.setSize(nZone);
}


template<class Face>
void tnbLib::MeshedSurface<Face>::addZones
(
	const labelUList& sizes,
	const UList<word>& names,
	const bool cullEmpty
)
{
	label start = 0;
	label nZone = 0;

	surfZoneList& zones = this->storedZones();
	zones.setSize(sizes.size());
	forAll(zones, zoneI)
	{
		if (sizes[zoneI] || !cullEmpty)
		{
			zones[nZone] = surfZone
			(
				names[zoneI],
				sizes[zoneI],
				start,
				nZone
			);
			start += sizes[zoneI];
			nZone++;
		}
	}
	zones.setSize(nZone);
}


template<class Face>
void tnbLib::MeshedSurface<Face>::addZones
(
	const labelUList& sizes,
	const bool cullEmpty
)
{
	label start = 0;
	label nZone = 0;

	surfZoneList& zones = this->storedZones();
	zones.setSize(sizes.size());
	forAll(zones, zoneI)
	{
		if (sizes[zoneI] || !cullEmpty)
		{
			zones[nZone] = surfZone
			(
				word("zone") + ::tnbLib::name(nZone),
				sizes[zoneI],
				start,
				nZone
			);
			start += sizes[zoneI];
			nZone++;
		}
	}
	zones.setSize(nZone);
}


template<class Face>
void tnbLib::MeshedSurface<Face>::removeZones()
{
	this->storedZones().clear();
}


// ************************************************************************* //