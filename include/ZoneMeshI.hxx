#pragma once
#include <entry.hxx>
#include <demandDrivenData.hxx>
#include <stringListOps.hxx>
#include <Pstream.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<class ZoneType, class MeshType>
void tnbLib::ZoneMesh<ZoneType, MeshType>::calcZoneMap() const
{
	// It is an error to attempt to recalculate cellEdges
	// if the pointer is already set
	if (zoneMapPtr_)
	{
		FatalErrorInFunction
			<< "zone map already calculated"
			<< abort(FatalError);
	}
	else
	{
		// Count number of objects in all zones
		label nObjects = 0;

		forAll(*this, zoneI)
		{
			nObjects += this->operator[](zoneI).size();
		}

		zoneMapPtr_ = new Map<label>(2 * nObjects);
		Map<label>& zm = *zoneMapPtr_;

		// Fill in objects of all zones into the map.  The key is the global
		// object index and the result is the zone index
		forAll(*this, zoneI)
		{
			const labelList& zoneObjects = this->operator[](zoneI);

			forAll(zoneObjects, objI)
			{
				zm.insert(zoneObjects[objI], zoneI);
			}
		}
	}
}


template<class ZoneType, class MeshType>
bool tnbLib::ZoneMesh<ZoneType, MeshType>::read()
{
	if
		(
			readOpt() == IOobject::MUST_READ
			|| readOpt() == IOobject::MUST_READ_IF_MODIFIED
			|| (readOpt() == IOobject::READ_IF_PRESENT && headerOk())
			)
	{
		if (readOpt() == IOobject::MUST_READ_IF_MODIFIED)
		{
			WarningInFunction
				<< "Specified IOobject::MUST_READ_IF_MODIFIED but class"
				<< " does not support automatic rereading."
				<< endl;
		}

		PtrList<ZoneType>& zones = *this;

		// Read zones
		Istream& is = readStream(typeName);

		PtrList<entry> patchEntries(is);
		zones.setSize(patchEntries.size());

		forAll(zones, zoneI)
		{
			zones.set
			(
				zoneI,
				ZoneType::New
				(
					patchEntries[zoneI].keyword(),
					patchEntries[zoneI].dict(),
					zoneI,
					*this
				)
			);
		}

		// Check state of IOstream
		is.check
		(
			"ZoneMesh::ZoneMesh"
			"(const IOobject&, const MeshType&)"
		);

		close();

		return true;
	}
	else
	{
		// Nothing read
		return false;
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class ZoneType, class MeshType>
tnbLib::ZoneMesh<ZoneType, MeshType>::ZoneMesh
(
	const IOobject& io,
	const MeshType& mesh
)
	:
	PtrList<ZoneType>(),
	regIOobject(io),
	mesh_(mesh),
	zoneMapPtr_(nullptr)
{
	read();
}


template<class ZoneType, class MeshType>
tnbLib::ZoneMesh<ZoneType, MeshType>::ZoneMesh
(
	const IOobject& io,
	const MeshType& mesh,
	const label size
)
	:
	PtrList<ZoneType>(size),
	regIOobject(io),
	mesh_(mesh),
	zoneMapPtr_(nullptr)
{
	// Optionally read contents, otherwise keep size
	read();
}


template<class ZoneType, class MeshType>
tnbLib::ZoneMesh<ZoneType, MeshType>::ZoneMesh
(
	const IOobject& io,
	const MeshType& mesh,
	const PtrList<ZoneType>& pzm
)
	:
	PtrList<ZoneType>(),
	regIOobject(io),
	mesh_(mesh),
	zoneMapPtr_(nullptr)
{
	if (!read())
	{
		// Nothing read. Use supplied zones
		PtrList<ZoneType>& zones = *this;
		zones.setSize(pzm.size());
		forAll(zones, zoneI)
		{
			zones.set(zoneI, pzm[zoneI].clone(*this).ptr());
		}
	}
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class ZoneType, class MeshType>
tnbLib::ZoneMesh<ZoneType, MeshType>::~ZoneMesh()
{
	clearAddressing();
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class ZoneType, class MeshType>
const tnbLib::Map<tnbLib::label>&
tnbLib::ZoneMesh<ZoneType, MeshType>::zoneMap() const
{
	if (!zoneMapPtr_)
	{
		calcZoneMap();
	}

	return *zoneMapPtr_;
}


template<class ZoneType, class MeshType>
tnbLib::label tnbLib::ZoneMesh<ZoneType, MeshType>::whichZone
(
	const label objectIndex
) const
{
	const Map<label>& zm = zoneMap();
	Map<label>::const_iterator zmIter = zm.find(objectIndex);

	if (zmIter == zm.end())
	{
		return -1;
	}
	else
	{
		return zmIter();
	}
}


template<class ZoneType, class MeshType>
tnbLib::wordList tnbLib::ZoneMesh<ZoneType, MeshType>::types() const
{
	const PtrList<ZoneType>& zones = *this;

	wordList lst(zones.size());

	forAll(zones, zoneI)
	{
		lst[zoneI] = zones[zoneI].type();
	}

	return lst;
}


template<class ZoneType, class MeshType>
tnbLib::wordList tnbLib::ZoneMesh<ZoneType, MeshType>::names() const
{
	const PtrList<ZoneType>& zones = *this;

	wordList lst(zones.size());

	forAll(zones, zoneI)
	{
		lst[zoneI] = zones[zoneI].name();
	}

	return lst;
}


template<class ZoneType, class MeshType>
tnbLib::labelList tnbLib::ZoneMesh<ZoneType, MeshType>::findIndices
(
	const keyType& key
) const
{
	labelList indices;

	if (!key.empty())
	{
		if (key.isPattern())
		{
			indices = findStrings(key, this->names());
		}
		else
		{
			indices.setSize(this->size());
			label nFound = 0;
			forAll(*this, i)
			{
				if (key == operator[](i).name())
				{
					indices[nFound++] = i;
				}
			}
			indices.setSize(nFound);
		}
	}

	return indices;
}


template<class ZoneType, class MeshType>
tnbLib::label tnbLib::ZoneMesh<ZoneType, MeshType>::findIndex
(
	const keyType& key
) const
{
	if (!key.empty())
	{
		if (key.isPattern())
		{
			labelList indices = this->findIndices(key);

			// return first element
			if (!indices.empty())
			{
				return indices[0];
			}
		}
		else
		{
			forAll(*this, i)
			{
				if (key == operator[](i).name())
				{
					return i;
				}
			}
		}
	}

	// not found
	return -1;
}


template<class ZoneType, class MeshType>
tnbLib::label tnbLib::ZoneMesh<ZoneType, MeshType>::findZoneID
(
	const word& zoneName
) const
{
	const PtrList<ZoneType>& zones = *this;

	forAll(zones, zoneI)
	{
		if (zones[zoneI].name() == zoneName)
		{
			return zoneI;
		}
	}

	// Zone not found
	if (debug)
	{
		InfoInFunction
			<< "Zone named " << zoneName << " not found.  "
			<< "List of available zone names: " << names() << endl;
	}

	// not found
	return -1;
}


template<class ZoneType, class MeshType>
tnbLib::PackedBoolList tnbLib::ZoneMesh<ZoneType, MeshType>::findMatching
(
	const keyType& key
) const
{
	PackedBoolList lst;

	const labelList indices = this->findIndices(key);
	forAll(indices, i)
	{
		lst |= static_cast<const labelList&>(this->operator[](indices[i]));
	}

	return lst;
}


template<class ZoneType, class MeshType>
void tnbLib::ZoneMesh<ZoneType, MeshType>::clearAddressing()
{
	deleteDemandDrivenData(zoneMapPtr_);

	PtrList<ZoneType>& zones = *this;

	forAll(zones, zoneI)
	{
		zones[zoneI].clearAddressing();
	}
}


template<class ZoneType, class MeshType>
void tnbLib::ZoneMesh<ZoneType, MeshType>::clear()
{
	clearAddressing();
	PtrList<ZoneType>::clear();
}


template<class ZoneType, class MeshType>
bool tnbLib::ZoneMesh<ZoneType, MeshType>::checkDefinition
(
	const bool report
) const
{
	bool inError = false;

	const PtrList<ZoneType>& zones = *this;

	forAll(zones, zoneI)
	{
		inError |= zones[zoneI].checkDefinition(report);
	}
	return inError;
}


template<class ZoneType, class MeshType>
bool tnbLib::ZoneMesh<ZoneType, MeshType>::checkParallelSync
(
	const bool report
) const
{
	if (!Pstream::parRun())
	{
		return false;
	}


	const PtrList<ZoneType>& zones = *this;

	bool hasError = false;

	// Collect all names
	List<wordList> allNames(Pstream::nProcs());
	allNames[Pstream::myProcNo()] = this->names();
	Pstream::gatherList(allNames);
	Pstream::scatterList(allNames);

	List<wordList> allTypes(Pstream::nProcs());
	allTypes[Pstream::myProcNo()] = this->types();
	Pstream::gatherList(allTypes);
	Pstream::scatterList(allTypes);

	// Have every processor check but only master print error.

	for (label proci = 1; proci < allNames.size(); proci++)
	{
		if
			(
			(allNames[proci] != allNames[0])
				|| (allTypes[proci] != allTypes[0])
				)
		{
			hasError = true;

			if (debug || (report && Pstream::master()))
			{
				Info << " ***Inconsistent zones across processors, "
					"processor 0 has zone names:" << allNames[0]
					<< " zone types:" << allTypes[0]
					<< " processor " << proci << " has zone names:"
					<< allNames[proci]
					<< " zone types:" << allTypes[proci]
					<< endl;
			}
		}
	}

	// Check contents
	if (!hasError)
	{
		forAll(zones, zoneI)
		{
			if (zones[zoneI].checkParallelSync(false))
			{
				hasError = true;

				if (debug || (report && Pstream::master()))
				{
					Info << " ***Zone " << zones[zoneI].name()
						<< " of type " << zones[zoneI].type()
						<< " is not correctly synchronised"
						<< " across coupled boundaries."
						<< " (coupled faces are either not both"
						<< " present in set or have same flipmap)" << endl;
				}
			}
		}
	}

	return hasError;
}


template<class ZoneType, class MeshType>
void tnbLib::ZoneMesh<ZoneType, MeshType>::movePoints(const pointField& p)
{
	PtrList<ZoneType>& zones = *this;

	forAll(zones, zoneI)
	{
		zones[zoneI].movePoints(p);
	}
}


template<class ZoneType, class MeshType>
bool tnbLib::ZoneMesh<ZoneType, MeshType>::writeData(Ostream& os) const
{
	os << *this;
	return os.good();
}


// * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * * //

template<class ZoneType, class MeshType>
const ZoneType& tnbLib::ZoneMesh<ZoneType, MeshType>::operator[]
(
	const word& zoneName
	) const
{
	const label zoneI = findZoneID(zoneName);

	if (zoneI < 0)
	{
		FatalErrorInFunction
			<< "Zone named " << zoneName << " not found." << nl
			<< "Available zone names: " << names() << endl
			<< abort(FatalError);
	}

	return operator[](zoneI);
}


template<class ZoneType, class MeshType>
ZoneType& tnbLib::ZoneMesh<ZoneType, MeshType>::operator[]
(
	const word& zoneName
	)
{
	const label zoneI = findZoneID(zoneName);

	if (zoneI < 0)
	{
		FatalErrorInFunction
			<< "Zone named " << zoneName << " not found." << nl
			<< "Available zone names: " << names() << endl
			<< abort(FatalError);
	}

	return operator[](zoneI);
}


// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

template<class ZoneType, class MeshType>
tnbLib::Ostream& tnbLib::operator<<
(
	Ostream& os,
	const ZoneMesh<ZoneType, MeshType>& zones
	)
{
	os << zones.size() << nl << token::BEGIN_LIST;

	forAll(zones, zoneI)
	{
		zones[zoneI].writeDict(os);
	}

	os << token::END_LIST;

	return os;
}


// ************************************************************************* //