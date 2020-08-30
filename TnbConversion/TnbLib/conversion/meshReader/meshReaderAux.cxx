#include <meshReader.hxx>

#include <IOMap.hxx>
#include <OFstream.hxx>
#include <Time.hxx>

// * * * * * * * * * * * * * * * Static Functions  * * * * * * * * * * * * * //

void tnbLib::meshReader::warnDuplicates
(
	const word& context,
	const wordList& list
)
{
	HashTable<label> hashed(list.size());
	bool duplicates = false;

	forAll(list, listI)
	{
		// check duplicate name
		HashTable<label>::iterator iter = hashed.find(list[listI]);
		if (iter != hashed.end())
		{
			(*iter)++;
			duplicates = true;
		}
		else
		{
			hashed.insert(list[listI], 1);
		}
	}

	// warn about duplicate names
	if (duplicates)
	{
		Info << nl << "WARNING: " << context << " with identical names:";
		forAllConstIter(HashTable<label>, hashed, iter)
		{
			if (*iter > 1)
			{
				Info << "  " << iter.key();
			}
		}
		Info << nl << endl;
	}
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::meshReader::writeInterfaces(const objectRegistry& registry) const
{
	// write constant/polyMesh/interface
	IOList<labelList> ioObj
	(
		IOobject
		(
			"interfaces",
			registry.time().constant(),
			polyMesh::meshSubDir,
			registry,
			IOobject::NO_READ,
			IOobject::NO_WRITE,
			false
		)
	);

	ioObj.note() = "as yet unsupported interfaces (baffles)";

	Info << "Writing " << ioObj.name() << " to " << ioObj.objectPath() << endl;

	OFstream os(ioObj.objectPath());
	ioObj.writeHeader(os);

	os << interfaces_;
	ioObj.writeEndDivider(os);
}


void tnbLib::meshReader::writeMeshLabelList
(
	const objectRegistry& registry,
	const word& propertyName,
	const labelList& list,
	IOstream::streamFormat fmt
) const
{
	// write constant/polyMesh/propertyName
	IOList<label> ioObj
	(
		IOobject
		(
			propertyName,
			registry.time().constant(),
			polyMesh::meshSubDir,
			registry,
			IOobject::NO_READ,
			IOobject::AUTO_WRITE,
			false
		),
		list
	);


	ioObj.note() = "persistent data for star-cd <-> foam translation";
	Info << "Writing " << ioObj.name() << " to " << ioObj.objectPath() << endl;

	// NOTE:
	// the cellTableId is an integer and almost always < 1000, thus ASCII
	// will be compacter than binary and makes external scripting easier
	//
	ioObj.writeObject
	(
		fmt,
		IOstream::currentVersion,
		IOstream::UNCOMPRESSED,
		true
	);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::meshReader::writeAux(const objectRegistry& registry) const
{
	cellTable_.writeDict(registry);
	writeInterfaces(registry);

	// write origCellId as List<label>
	writeMeshLabelList
	(
		registry,
		"origCellId",
		origCellId_,
		IOstream::BINARY
	);

	// write cellTableId as List<label>
	// this is crucial for later conversion back to ccm/starcd
	writeMeshLabelList
	(
		registry,
		"cellTableId",
		cellTableId_,
		IOstream::ASCII
	);
}


// ************************************************************************* //