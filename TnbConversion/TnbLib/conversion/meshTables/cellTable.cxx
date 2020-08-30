#include <cellTable.hxx>

#include <IOMap.hxx>
#include <OFstream.hxx>
#include <wordList.hxx>
#include <stringListOps.hxx>

#include <IStringStream.hxx>  // added by amir

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

const char* const tnbLib::cellTable::defaultMaterial_ = "fluid";

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

tnbLib::Map<tnbLib::label> tnbLib::cellTable::zoneMap() const
{
	Map<label> lookup;

	label zoneI = 0;
	forAllConstIter(Map<dictionary>, *this, iter)
	{
		lookup.insert(iter.key(), zoneI++);
	}

	return lookup;
}


tnbLib::wordList tnbLib::cellTable::namesList() const
{
	Map<word> lookup = names();
	wordList lst(lookup.size());

	label zoneI = 0;
	forAllConstIter(Map<word>, lookup, iter)
	{
		lst[zoneI++] = iter();
	}

	return lst;
}


void tnbLib::cellTable::addDefaults()
{
	forAllIter(Map<dictionary>, *this, iter)
	{
		if (!iter().found("MaterialType"))
		{
			iter().add("MaterialType", defaultMaterial_);
		}
	}
}


void tnbLib::cellTable::setEntry
(
	const label id,
	const word& keyWord,
	const word& value
)
{
	dictionary dict;
	dict.add(keyWord, value);

	iterator iter = find(id);
	if (iter != end())
	{
		iter().merge(dict);
	}
	else
	{
		insert(id, dict);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::cellTable::cellTable()
	:
	Map<dictionary>()
{}


tnbLib::cellTable::cellTable
(
	const objectRegistry& registry,
	const word& name,
	const fileName& instance
)
	:
	Map<dictionary>()
{
	readDict(registry, name, instance);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::cellTable::~cellTable()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

tnbLib::label tnbLib::cellTable::append(const dictionary& dict)
{
	label maxId = -1;
	forAllConstIter(Map<dictionary>, *this, iter)
	{
		if (maxId < iter.key())
		{
			maxId = iter.key();
		}
	}

	insert(++maxId, dict);
	return maxId;
}


tnbLib::Map<tnbLib::word> tnbLib::cellTable::names() const
{
	Map<word> lookup;

	forAllConstIter(Map<dictionary>, *this, iter)
	{
		lookup.insert
		(
			iter.key(),
			iter().lookupOrDefault<word>
			(
				"Label",
				"cellTable_" + tnbLib::name(iter.key())
				)
		);
	}

	return lookup;
}


tnbLib::Map<tnbLib::word> tnbLib::cellTable::names
(
	const UList<wordRe>& patterns
) const
{
	Map<word> lookup;

	forAllConstIter(Map<dictionary>, *this, iter)
	{
		word lookupName = iter().lookupOrDefault<word>
			(
				"Label",
				"cellTable_" + tnbLib::name(iter.key())
				);

		if (findStrings(patterns, lookupName))
		{
			lookup.insert(iter.key(), lookupName);
		}
	}

	return lookup;
}


tnbLib::word tnbLib::cellTable::name(const label id) const
{
	word theName("cellTable_" + tnbLib::name(id));

	const_iterator iter = find(id);
	if (iter != end())
	{
		iter().readIfPresent("Label", theName);
	}

	return theName;
}


tnbLib::label tnbLib::cellTable::findIndex(const word& name) const
{
	if (name.empty())
	{
		return -1;
	}

	forAllConstIter(Map<dictionary>, *this, iter)
	{
		if (iter().lookupOrDefault<word>("Label", word::null) == name)
		{
			return iter.key();
		}
	}

	return -1;
}


tnbLib::Map<tnbLib::word> tnbLib::cellTable::materialTypes() const
{
	Map<word> lookup;

	forAllConstIter(Map<dictionary>, *this, iter)
	{
		lookup.insert
		(
			iter.key(),
			iter().lookupOrDefault<word>("MaterialType", defaultMaterial_)
		);
	}

	return lookup;
}


tnbLib::Map<tnbLib::word> tnbLib::cellTable::selectType(const word& matl) const
{
	Map<word> lookup;

	forAllConstIter(Map<dictionary>, *this, iter)
	{
		if
			(
				matl
				== iter().lookupOrDefault<word>("MaterialType", defaultMaterial_)
				)
		{
			lookup.insert
			(
				iter.key(),
				iter().lookupOrDefault<word>
				(
					"Label",
					"cellTable_" + tnbLib::name(iter.key())
					)
			);
		}
	}

	return lookup;
}


tnbLib::Map<tnbLib::word> tnbLib::cellTable::fluids() const
{
	return selectType("fluid");
}


tnbLib::Map<tnbLib::word> tnbLib::cellTable::solids() const
{
	return selectType("solid");
}


tnbLib::Map<tnbLib::word> tnbLib::cellTable::shells() const
{
	return selectType("shell");
}



void tnbLib::cellTable::setMaterial(const label id, const word& matlType)
{
	setEntry(id, "MaterialType", matlType);
}


void tnbLib::cellTable::setName(const label id, const word& name)
{
	setEntry(id, "Label", name);
}


void tnbLib::cellTable::setName(const label id)
{
	iterator iter = find(id);

	if (iter == end() || !iter().found("Label"))
	{
		setName(id, "cellTable_" + tnbLib::name(id));
	}
}


void tnbLib::cellTable::readDict
(
	const objectRegistry& registry,
	const word& name,
	const fileName& instance
)
{
	clear();

	// read constant/dictName
	IOMap<dictionary> ioObj
	(
		IOobject
		(
			name,
			instance,
			registry,
			IOobject::READ_IF_PRESENT,
			IOobject::NO_WRITE,
			false
		)
	);

	if (ioObj.headerOk())
	{
		*this = ioObj;
		addDefaults();
	}
	else
	{
		Info << "no constant/cellTable information available" << endl;
	}
}


void tnbLib::cellTable::writeDict
(
	const objectRegistry& registry,
	const word& name,
	const fileName& instance
) const
{
	// write constant/dictName
	IOMap<dictionary> ioObj
	(
		IOobject
		(
			name,
			instance,
			registry,
			IOobject::NO_READ,
			IOobject::NO_WRITE,
			false
		)
	);

	ioObj.note() =
		"persistent data for thirdParty mesh <-> OpenFOAM translation";

	Info << "Writing " << ioObj.name() << " to " << ioObj.objectPath() << endl;

	OFstream os(ioObj.objectPath());
	ioObj.writeHeader(os);
	os << *this;
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

void tnbLib::cellTable::operator=(const cellTable& rhs)
{
	Map<dictionary>::operator=(rhs);
	addDefaults();
}


void tnbLib::cellTable::operator=(const Map<dictionary>& rhs)
{
	Map<dictionary>::operator=(rhs);
	addDefaults();
}


void tnbLib::cellTable::operator=(const polyMesh& mesh)
{
	Map<dictionary> zoneDict;

	// create cellTableId and cellTable based on cellZones
	label nZoneCells = 0;

	wordList zoneNames = mesh.cellZones().names();
	label unZonedType = zoneNames.size() + 1;

	// do cell zones
	forAll(mesh.cellZones(), zoneI)
	{
		const cellZone& cZone = mesh.cellZones()[zoneI];
		nZoneCells += cZone.size();

		dictionary dict;
		dict.add("Label", zoneNames[zoneI]);
		zoneDict.insert(zoneI + 1, dict);
	}

	// collect unzoned cells
	// special case: no zones at all - do entire mesh
	if (nZoneCells == 0)
	{
		zoneDict.clear();
		unZonedType = 1;
	}

	if (mesh.nCells() > nZoneCells)
	{
		zoneDict.insert
		(
			unZonedType,
			dictionary(IStringStream("Label cells;")())
		);
	}

	Map<dictionary>::operator=(zoneDict);
	addDefaults();
}


// * * * * * * * * * * * * * * * Friend Functions  * * * * * * * * * * * * * //

void tnbLib::cellTable::addCellZones
(
	polyMesh& mesh,
	const labelList& tableIds
) const
{
	Map<label> typeToZone = zoneMap();
	List<DynamicList<label>> zoneCells(size());

	forAll(tableIds, celli)
	{
		Map<label>::const_iterator iter = typeToZone.find(tableIds[celli]);
		if (iter != typeToZone.end())
		{
			zoneCells[iter()].append(celli);
		}
	}

	// track which zones were actually used
	labelList zoneUsed(zoneCells.size());
	wordList  zoneNames(namesList());

	label nZone = 0;
	forAll(zoneCells, zoneI)
	{
		zoneCells[zoneI].shrink();
		if (zoneCells[zoneI].size())
		{
			zoneUsed[nZone++] = zoneI;
		}
	}
	zoneUsed.setSize(nZone);

	cellZoneMesh& czMesh = mesh.cellZones();

	czMesh.clear();
	if (nZone <= 1)
	{
		Info << "cellZones not used" << endl;
		return;
	}
	czMesh.setSize(nZone);

	forAll(zoneUsed, zoneI)
	{
		const label origZoneI = zoneUsed[zoneI];

		Info << "cellZone " << zoneI
			<< " (size: " << zoneCells[origZoneI].size()
			<< ") name: " << zoneNames[origZoneI] << endl;

		czMesh.set
		(
			zoneI,
			new cellZone
			(
				zoneNames[origZoneI],
				zoneCells[origZoneI],
				zoneI,
				czMesh
			)
		);
	}
	czMesh.writeOpt() = IOobject::AUTO_WRITE;
}


void tnbLib::cellTable::combine(const dictionary& mapDict, labelList& tableIds)
{
	if (mapDict.empty())
	{
		return;
	}

	Map<word> origNames(names());
	labelList mapping(identity(max(origNames.toc()) + 1));

	bool remap = false;
	forAllConstIter(dictionary, mapDict, iter)
	{
		wordReList patterns(iter().stream());

		// find all matches
		Map<word> matches;
		forAllConstIter(Map<word>, origNames, namesIter)
		{
			if (findStrings(patterns, namesIter()))
			{
				matches.insert(namesIter.key(), namesIter());
			}
		}

		if (matches.size())
		{
			label targetId = this->findIndex(iter().keyword());

			Info << "combine cellTable: " << iter().keyword();
			if (targetId < 0)
			{
				// not found - reuse 1st element but with different name
				targetId = min(matches.toc());
				operator[](targetId).set("Label", iter().keyword());

				Info << " = (";
			}
			else
			{
				Info << " += (";
			}


			// the mapping and name for targetId is already okay
			matches.erase(targetId);
			origNames.erase(targetId);

			// remove matched names, leaving targetId on 'this'
			this->erase(matches);
			origNames.erase(matches);

			forAllConstIter(Map<word>, matches, matchIter)
			{
				mapping[matchIter.key()] = targetId;
				Info << " " << matchIter();
			}
			Info << " )" << endl;

			remap = true;
		}
	}

	if (remap)
	{
		inplaceRenumber(mapping, tableIds);
	}
}

// ************************************************************************* //