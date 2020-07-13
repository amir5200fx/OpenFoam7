#include <topoSet.hxx>

#include <mapPolyMesh.hxx>
#include <polyMesh.hxx>
#include <boundBox.hxx>
#include <Time.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(topoSet, 0);
	defineRunTimeSelectionTable(topoSet, word);
	defineRunTimeSelectionTable(topoSet, size);
	defineRunTimeSelectionTable(topoSet, set);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::topoSet> tnbLib::topoSet::New
(
	const word& setType,
	const polyMesh& mesh,
	const word& name,
	readOption r,
	writeOption w
)
{
	wordConstructorTable::iterator cstrIter =
		wordConstructorTablePtr_->find(setType);

	if (cstrIter == wordConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown set type " << setType
			<< endl << endl
			<< "Valid set types : " << endl
			<< wordConstructorTablePtr_->sortedToc()
			<< exit(FatalError);
	}

	return autoPtr<topoSet>(cstrIter()(mesh, name, r, w));
}


tnbLib::autoPtr<tnbLib::topoSet> tnbLib::topoSet::New
(
	const word& setType,
	const polyMesh& mesh,
	const word& name,
	const label size,
	writeOption w
)
{
	sizeConstructorTable::iterator cstrIter =
		sizeConstructorTablePtr_->find(setType);

	if (cstrIter == sizeConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown set type " << setType
			<< endl << endl
			<< "Valid set types : " << endl
			<< sizeConstructorTablePtr_->sortedToc()
			<< exit(FatalError);
	}

	return autoPtr<topoSet>(cstrIter()(mesh, name, size, w));
}


tnbLib::autoPtr<tnbLib::topoSet> tnbLib::topoSet::New
(
	const word& setType,
	const polyMesh& mesh,
	const word& name,
	const topoSet& set,
	writeOption w
)
{
	setConstructorTable::iterator cstrIter =
		setConstructorTablePtr_->find(setType);

	if (cstrIter == setConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown set type " << setType
			<< endl << endl
			<< "Valid set types : " << endl
			<< setConstructorTablePtr_->sortedToc()
			<< exit(FatalError);
	}

	return autoPtr<topoSet>(cstrIter()(mesh, name, set, w));
}


tnbLib::fileName tnbLib::topoSet::localPath
(
	const polyMesh& mesh,
	const word& name
)
{
	return mesh.facesInstance() / mesh.dbDir() / polyMesh::meshSubDir / "sets" / name;
}


// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

// Update stored cell numbers using map.
// Do in two passes to prevent allocation if nothing changed.
void tnbLib::topoSet::updateLabels(const labelList& map)
{
	// Iterate over map to see if anything changed
	bool changed = false;

	forAllConstIter(labelHashSet, *this, iter)
	{
		if ((iter.key() < 0) || (iter.key() > map.size()))
		{
			FatalErrorInFunction
				<< "Illegal content " << iter.key() << " of set:" << name()
				<< " of type " << type() << endl
				<< "Value should be between 0 and " << map.size() - 1
				<< abort(FatalError);
		}

		const label newCelli = map[iter.key()];

		if (newCelli != iter.key())
		{
			changed = true;

			break;
		}
	}

	// Relabel (use second Map to prevent overlapping)
	if (changed)
	{
		labelHashSet newSet(2 * size());

		forAllConstIter(labelHashSet, *this, iter)
		{
			const label newCelli = map[iter.key()];

			if (newCelli >= 0)
			{
				newSet.insert(newCelli);
			}
		}

		transfer(newSet);
	}
}


void tnbLib::topoSet::check(const label maxLabel)
{
	forAllConstIter(topoSet, *this, iter)
	{
		if ((iter.key() < 0) || (iter.key() > maxLabel))
		{
			FatalErrorInFunction
				<< "Illegal content " << iter.key() << " of set:" << name()
				<< " of type " << type() << endl
				<< "Value should be between 0 and " << maxLabel
				<< abort(FatalError);
		}
	}
}


// Write maxElem elements, starting at iter. Updates iter and elemI.
void tnbLib::topoSet::writeDebug
(
	Ostream& os,
	const label maxElem,
	topoSet::const_iterator& iter,
	label& elemI
) const
{
	label n = 0;

	for (; (iter != end()) && (n < maxElem); ++iter)
	{
		if ((n != 0) && ((n % 10) == 0))
		{
			os << endl;
		}
		os << iter.key() << ' ';

		n++;
		elemI++;
	}
}


// Write maxElem elements, starting at iter. Updates iter and elemI.
void tnbLib::topoSet::writeDebug
(
	Ostream& os,
	const pointField& coords,
	const label maxElem,
	topoSet::const_iterator& iter,
	label& elemI
) const
{
	label n = 0;

	for (; (iter != end()) && (n < maxElem); ++iter)
	{
		if ((n != 0) && ((n % 3) == 0))
		{
			os << endl;
		}
		os << iter.key() << coords[iter.key()] << ' ';

		n++;
		elemI++;
	}
}


void tnbLib::topoSet::writeDebug
(
	Ostream& os,
	const pointField& coords,
	const label maxLen
) const
{
	// Bounding box of contents.
	boundBox bb(pointField(coords, toc()), true);

	os << "Set bounding box: min = "
		<< bb.min() << "    max = " << bb.max() << " meters. " << endl << endl;

	label n = 0;

	topoSet::const_iterator iter = begin();

	if (size() <= maxLen)
	{
		writeDebug(os, coords, maxLen, iter, n);
	}
	else
	{
		label halfLen = maxLen / 2;

		os << "Size larger than " << maxLen << ". Printing first and last "
			<< halfLen << " elements:" << endl << endl;

		writeDebug(os, coords, halfLen, iter, n);

		os << nl << "  .." << nl << endl;

		for (; n < size() - halfLen; ++n)
		{
			++iter;
		}

		writeDebug(os, coords, halfLen, iter, n);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::topoSet::topoSet(const IOobject& obj, const word& wantedType)
	:
	regIOobject(obj)
{
	if
		(
			readOpt() == IOobject::MUST_READ
			|| readOpt() == IOobject::MUST_READ_IF_MODIFIED
			|| (
				readOpt() == IOobject::READ_IF_PRESENT
				&& headerOk()
				)
			)
	{
		if (readStream(wantedType).good())
		{
			readStream(wantedType) >> static_cast<labelHashSet&>(*this);

			close();
		}
	}
}


tnbLib::topoSet::topoSet
(
	const polyMesh& mesh,
	const word& wantedType,
	const word& name,
	readOption r,
	writeOption w
)
	:
	regIOobject
	(
		IOobject
		(
			name,
			mesh.time().findInstance
			(
				mesh.dbDir() / polyMesh::meshSubDir / "sets",
				word::null,
				r,  // IOobject::MUST_READ,
				mesh.facesInstance()
			),
			polyMesh::meshSubDir / "sets",
			mesh,
			r,
			w
		)
	)
{
	if
		(
			readOpt() == IOobject::MUST_READ
			|| readOpt() == IOobject::MUST_READ_IF_MODIFIED
			|| (
				readOpt() == IOobject::READ_IF_PRESENT
				&& headerOk()
				)
			)
	{
		if (readStream(wantedType).good())
		{
			readStream(wantedType) >> static_cast<labelHashSet&>(*this);

			close();
		}
	}
}


tnbLib::topoSet::topoSet
(
	const polyMesh& mesh,
	const word& name,
	const label size,
	writeOption w
)
	:
	regIOobject
	(
		IOobject
		(
			name,
			mesh.time().findInstance
			(
				mesh.dbDir() / polyMesh::meshSubDir / "sets",
				word::null,
				IOobject::NO_READ,
				mesh.facesInstance()
			),
			polyMesh::meshSubDir / "sets",
			mesh,
			IOobject::NO_READ,
			w
		)
	),
	labelHashSet(size)
{}


tnbLib::topoSet::topoSet
(
	const polyMesh& mesh,
	const word& name,
	const labelHashSet& set,
	writeOption w
)
	:
	regIOobject
	(
		IOobject
		(
			name,
			mesh.time().findInstance
			(
				mesh.dbDir() / polyMesh::meshSubDir / "sets",
				word::null,
				IOobject::NO_READ,
				mesh.facesInstance()
			),
			polyMesh::meshSubDir / "sets",
			mesh,
			IOobject::NO_READ,
			w
		)
	),
	labelHashSet(set)
{}


tnbLib::topoSet::topoSet(const IOobject& obj, const label size)
	:
	regIOobject(obj),
	labelHashSet(size)
{}


tnbLib::topoSet::topoSet(const IOobject& obj, const labelHashSet& set)
	:
	regIOobject(obj),
	labelHashSet(set)
{}



// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::topoSet::~topoSet()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::topoSet::invert(const label maxLen)
{
	// Keep copy of current set.
	labelHashSet currentSet(*this);

	clear();
	resize(2 * (maxLen - currentSet.size()));

	for (label celli = 0; celli < maxLen; celli++)
	{
		if (!currentSet.found(celli))
		{
			insert(celli);
		}
	}
}


void tnbLib::topoSet::subset(const topoSet& set)
{
	// Keep copy of current set.
	labelHashSet currentSet(*this);

	clear();
	resize(2 * min(currentSet.size(), set.size()));

	forAllConstIter(labelHashSet, currentSet, iter)
	{
		if (set.found(iter.key()))
		{
			// element present in both currentSet and set.
			insert(iter.key());
		}
	}
}


void tnbLib::topoSet::addSet(const topoSet& set)
{
	forAllConstIter(topoSet, set, iter)
	{
		insert(iter.key());
	}
}


void tnbLib::topoSet::deleteSet(const topoSet& set)
{
	forAllConstIter(topoSet, set, iter)
	{
		erase(iter.key());
	}
}


void tnbLib::topoSet::sync(const polyMesh&)
{
	NotImplemented;
}


void tnbLib::topoSet::writeDebug(Ostream& os, const label maxLen) const
{
	label n = 0;

	topoSet::const_iterator iter = begin();

	if (size() <= maxLen)
	{
		writeDebug(os, maxLen, iter, n);
	}
	else
	{
		label halfLen = maxLen / 2;

		os << "Size larger than " << maxLen << ". Printing first and last "
			<< halfLen << " elements:" << endl << endl;

		writeDebug(os, halfLen, iter, n);

		os << nl << "  .." << nl << endl;

		for (; n < size() - halfLen; ++n)
		{
			++iter;
		}

		writeDebug(os, halfLen, iter, n);
	}
}


bool tnbLib::topoSet::writeData(Ostream& os) const
{
	return (os << *this).good();
}


void tnbLib::topoSet::updateMesh(const mapPolyMesh&)
{
	NotImplemented;
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

void tnbLib::topoSet::operator=(const topoSet& rhs)
{
	labelHashSet::operator=(rhs);
}


// ************************************************************************* //