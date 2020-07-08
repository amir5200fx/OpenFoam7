#include <coordinateSystems.hxx>

#include <IOPtrList.hxx>
#include <Time.hxx>
#include <stringListOps.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(coordinateSystems, 0);
	defineTemplateTypeNameAndDebug(IOPtrList<coordinateSystem>, 0);
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::coordinateSystems::coordinateSystems(const IOobject& io)
	:
	IOPtrList<coordinateSystem>(io)
{}


tnbLib::coordinateSystems::coordinateSystems
(
	const IOobject& io,
	const PtrList<coordinateSystem>& lst
)
	:
	IOPtrList<coordinateSystem>(io, lst)
{}


tnbLib::coordinateSystems::coordinateSystems
(
	const IOobject& io,
	PtrList<coordinateSystem>&& lst
)
	:
	IOPtrList<coordinateSystem>(io, move(lst))
{}


// * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * * //

// Read construct from registry, or return previously registered
const tnbLib::coordinateSystems& tnbLib::coordinateSystems::New
(
	const objectRegistry& obr
)
{
	if (obr.foundObject<coordinateSystems>(typeName))
	{
		return obr.lookupObject<coordinateSystems>(typeName);
	}
	else
	{
		return obr.store
		(
			new coordinateSystems
			(
				IOobject
				(
					typeName,
					obr.time().constant(),
					obr,
					IOobject::READ_IF_PRESENT,
					IOobject::NO_WRITE
				)
			)
		);
	}
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::labelList tnbLib::coordinateSystems::findIndices(const keyType& key) const
{
	labelList indices;
	if (key.isPattern())
	{
		indices = findStrings(key, toc());
	}
	else
	{
		indices.setSize(size());
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

	return indices;
}


tnbLib::label tnbLib::coordinateSystems::findIndex(const keyType& key) const
{
	if (key.isPattern())
	{
		labelList indices = findIndices(key);
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

	return -1;
}


bool tnbLib::coordinateSystems::found(const keyType& key) const
{
	return findIndex(key) != -1;
}


tnbLib::wordList tnbLib::coordinateSystems::toc() const
{
	wordList keywords(size());

	forAll(*this, i)
	{
		keywords[i] = operator[](i).name();
	}

	return keywords;
}


bool tnbLib::coordinateSystems::writeData(Ostream& os) const
{
	os << nl << size() << nl << token::BEGIN_LIST;

	forAll(*this, i)
	{
		os << nl;
		operator[](i).writeDict(os, true);
	}

	os << token::END_LIST << nl;

	return os.good();
}


// ************************************************************************* //