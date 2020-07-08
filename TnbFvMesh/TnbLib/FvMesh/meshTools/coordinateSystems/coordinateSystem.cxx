#include <coordinateSystem.hxx>

#include <IOstreams.hxx>
#include <axesRotation.hxx>
#include <coordinateSystems.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(coordinateSystem, 0);
	defineRunTimeSelectionTable(coordinateSystem, dictionary);
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::coordinateSystem::coordinateSystem()
	:
	name_(),
	note_(),
	origin_(point::zero),
	R_(new axesRotation(sphericalTensor::I))
{}


tnbLib::coordinateSystem::coordinateSystem
(
	const word& name,
	const coordinateSystem& cs
)
	:
	name_(name),
	note_(),
	origin_(cs.origin_),
	R_(const_cast<coordinateRotation*>(&cs.R()))
{}


tnbLib::coordinateSystem::coordinateSystem
(
	const word& name,
	const point& origin,
	const coordinateRotation& cr
)
	:
	name_(name),
	note_(),
	origin_(origin),
	R_(const_cast<coordinateRotation*>(&cr))
{}


tnbLib::coordinateSystem::coordinateSystem
(
	const word& name,
	const point& origin,
	const vector& axis,
	const vector& dirn
)
	:
	name_(name),
	note_(),
	origin_(origin),
	R_(new axesRotation(axis, dirn))
{}


tnbLib::coordinateSystem::coordinateSystem
(
	const word& name,
	const dictionary& dict
)
	:
	name_(name),
	note_(),
	origin_(point::zero),
	R_()
{
	init(dict);
}


tnbLib::coordinateSystem::coordinateSystem(const dictionary& dict)
	:
	name_(),
	note_(),
	origin_(point::zero),
	R_()
{
	init(dict);
}


tnbLib::coordinateSystem::coordinateSystem
(
	const objectRegistry& obr,
	const dictionary& dict
)
	:
	name_(),
	note_(),
	origin_(point::zero),
	R_()
{
	const entry* entryPtr = dict.lookupEntryPtr(typeName_(), false, false);

	// non-dictionary entry is a lookup into global coordinateSystems
	if (entryPtr && !entryPtr->isDict())
	{
		keyType key(entryPtr->stream());

		const coordinateSystems& lst = coordinateSystems::New(obr);
		const label index = lst.findIndex(key);

		if (debug)
		{
			InfoInFunction
				<< "Using global coordinate system: "
				<< key << "=" << index << endl;
		}

		if (index < 0)
		{
			FatalErrorInFunction
				<< "could not find coordinate system: " << key << nl
				<< "available coordinate systems: " << lst.toc() << nl << nl
				<< exit(FatalError);
		}

		// copy coordinateSystem, but assign the name as the typeName
		// to avoid strange things in writeDict()
		operator=(lst[index]);
		name_ = typeName_();
	}
	else
	{
		init(dict, obr);
	}
}


tnbLib::coordinateSystem::coordinateSystem(Istream& is)
	:
	name_(is),
	note_(),
	origin_(point::zero),
	R_()
{
	dictionary dict(is);
	init(dict);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::coordinateSystem::~coordinateSystem()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::dictionary tnbLib::coordinateSystem::dict(bool ignoreType) const
{
	dictionary dict;

	dict.add("name", name_);

	// only write type for derived types
	if (!ignoreType && type() != typeName_())
	{
		dict.add("type", type());
	}

	// The note entry is optional
	if (note_.size())
	{
		dict.add("note", note_);
	}

	dict.add("origin", origin_);
	dict.add("e1", R_->e1());
	dict.add("e3", R_->e3());

	return dict;
}


tnbLib::vector tnbLib::coordinateSystem::localToGlobal
(
	const vector& local,
	bool translate
) const
{
	if (translate)
	{
		return (R_->transform(local)) + origin_;
	}
	else
	{
		return R_->transform(local);
	}
}


tnbLib::tmp<tnbLib::vectorField> tnbLib::coordinateSystem::localToGlobal
(
	const vectorField& local,
	bool translate
) const
{
	if (translate)
	{
		return (R_->transform(local)) + origin_;
	}
	else
	{
		return R_->transform(local);
	}
}


tnbLib::vector tnbLib::coordinateSystem::globalToLocal
(
	const vector& global,
	bool translate
) const
{
	if (translate)
	{
		return R_->invTransform(global - origin_);
	}
	else
	{
		return R_->invTransform(global);
	}
}


tnbLib::tmp<tnbLib::vectorField> tnbLib::coordinateSystem::globalToLocal
(
	const vectorField& global,
	bool translate
) const
{
	if (translate)
	{
		return R_->invTransform(global - origin_);
	}
	else
	{
		return R_->invTransform(global);
	}
}


void tnbLib::coordinateSystem::clear()
{
	note_.clear();
	origin_ = Zero;
	R_->clear();
}


void tnbLib::coordinateSystem::write(Ostream& os) const
{
	os << type() << " origin: " << origin() << nl;
	R_->write(os);
}


void tnbLib::coordinateSystem::writeDict(Ostream& os, bool subDict) const
{
	if (subDict)
	{
		os << indent << name_ << nl
			<< indent << token::BEGIN_BLOCK << incrIndent << nl;
	}

	writeEntry(os, "type", type());


	// The note entry is optional
	if (note_.size())
	{
		writeEntry(os, "note", note_);
	}

	writeEntry(os, "origin", origin_);
	R_->write(os);

	if (subDict)
	{
		os << decrIndent << indent << token::END_BLOCK << endl;
	}
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

void tnbLib::coordinateSystem::init(const dictionary& rhs)
{
	rhs.lookup("origin") >> origin_;
	note_.clear();
	rhs.readIfPresent("note", note_);
	R_.reset(coordinateRotation::New(rhs.subDict("coordinateRotation")).ptr());
}


void tnbLib::coordinateSystem::init
(
	const dictionary& rhs,
	const objectRegistry& obr
)
{
	if (debug)
	{
		Pout << "coordinateSystem::operator="
			"("
			"const dictionary&, "
			"const objectRegistry&"
			") : "
			<< "assign from " << rhs << endl;
	}

	rhs.lookup("origin") >> origin_;

	// The note entry is optional
	note_.clear();
	rhs.readIfPresent("note", note_);

	R_.reset
	(
		coordinateRotation::New(rhs.subDict("coordinateRotation"), obr).ptr()
	);
}


// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

bool tnbLib::operator!=(const coordinateSystem& a, const coordinateSystem& b)
{
	return
		(
			a.origin() != b.origin()
			|| a.R().R() != b.R().R()
			|| a.type() != b.type()
			);
}


// * * * * * * * * * * * * * * * Friend Functions  * * * * * * * * * * * * * //

tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const coordinateSystem& cs)
{
	cs.write(os);
	os.check("Ostream& operator<<(Ostream&, const coordinateSystem&");
	return os;
}


// ************************************************************************* //