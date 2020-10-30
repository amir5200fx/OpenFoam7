#include <zone.hxx>

#include <IOstream.hxx>
#include <demandDrivenData.hxx>
#include <HashSet.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(zone, 0);
}


// * * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * //

const tnbLib::Map<tnbLib::label>& tnbLib::zone::lookupMap() const
{
	if (!lookupMapPtr_)
	{
		calcLookupMap();
	}

	return *lookupMapPtr_;
}


void tnbLib::zone::calcLookupMap() const
{
	if (debug)
	{
		InfoInFunction << "Calculating lookup map" << endl;
	}

	if (lookupMapPtr_)
	{
		FatalErrorInFunction
			<< "Lookup map already calculated" << nl
			<< abort(FatalError);
	}

	const labelList& addr = *this;

	lookupMapPtr_ = new Map<label>(2 * addr.size());
	Map<label>& lm = *lookupMapPtr_;

	forAll(addr, i)
	{
		lm.insert(addr[i], i);
	}

	if (debug)
	{
		InfoInFunction << "Finished calculating lookup map" << endl;
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::zone::zone
(
	const word& name,
	const labelUList& addr,
	const label index
)
	:
	labelList(addr),
	name_(name),
	index_(index),
	lookupMapPtr_(nullptr)
{}


tnbLib::zone::zone
(
	const word& name,
	labelList&& addr,
	const label index
)
	:
	labelList(move(addr)),
	name_(name),
	index_(index),
	lookupMapPtr_(nullptr)
{}


tnbLib::zone::zone
(
	const word& name,
	const dictionary& dict,
	const word& labelsName,
	const label index
)
	:
	labelList(dict.lookup(labelsName)),
	name_(name),
	index_(index),
	lookupMapPtr_(nullptr)
{}


tnbLib::zone::zone
(
	const zone& z,
	const labelUList& addr,
	const label index
)
	:
	labelList(addr),
	name_(z.name()),
	index_(index),
	lookupMapPtr_(nullptr)
{}


tnbLib::zone::zone
(
	const zone& z,
	labelList&& addr,
	const label index
)
	:
	labelList(move(addr)),
	name_(z.name()),
	index_(index),
	lookupMapPtr_(nullptr)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::zone::~zone()
{
	clearAddressing();
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::label tnbLib::zone::localID(const label globalCellID) const
{
	const Map<label>& lm = lookupMap();

	Map<label>::const_iterator lmIter = lm.find(globalCellID);

	if (lmIter == lm.end())
	{
		return -1;
	}
	else
	{
		return lmIter();
	}
}


void tnbLib::zone::clearAddressing()
{
	deleteDemandDrivenData(lookupMapPtr_);
}


bool tnbLib::zone::checkDefinition(const label maxSize, const bool report) const
{
	const labelList& addr = *this;

	bool hasError = false;

	// To check for duplicate entries
	labelHashSet elems(size());

	forAll(addr, i)
	{
		if (addr[i] < 0 || addr[i] >= maxSize)
		{
			hasError = true;

			if (report)
			{
				SeriousErrorInFunction
					<< "Zone " << name_
					<< " contains invalid index label " << addr[i] << nl
					<< "Valid index labels are 0.."
					<< maxSize - 1 << endl;
			}
			else
			{
				// w/o report - can stop checking now
				break;
			}
		}
		else if (!elems.insert(addr[i]))
		{
			if (report)
			{
				WarningInFunction
					<< "Zone " << name_
					<< " contains duplicate index label " << addr[i] << endl;
			}
		}
	}

	return hasError;
}


void tnbLib::zone::write(Ostream& os) const
{
	os << nl << name_
		<< nl << static_cast<const labelList&>(*this);
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

void tnbLib::zone::operator=(const zone& zn)
{
	labelList::operator=(zn);
}


void tnbLib::zone::operator=(zone&& zn)
{
	labelList::operator=(move(zn));
}


void tnbLib::zone::operator=(const labelUList& addr)
{
	labelList::operator=(addr);
}


void tnbLib::zone::operator=(labelList&& addr)
{
	labelList::operator=(move(addr));
}


// * * * * * * * * * * * * * * * Ostream Operator  * * * * * * * * * * * * * //

FoamBase_EXPORT tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const zone& z)
{
	z.write(os);
	os.check("Ostream& operator<<(Ostream& f, const zone& z");
	return os;
}


// ************************************************************************* //