#include <surfZoneIOList.hxx>

// added by amir
#include <entry.hxx>
#include <PtrList.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(surfZoneIOList, 0);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::surfZoneIOList::surfZoneIOList
(
	const IOobject& io
)
	:
	surfZoneList(),
	regIOobject(io)
{
	tnbLib::string functionName =
		"surfZoneIOList::surfZoneIOList"
		"(const IOobject& io)";


	if
		(
			readOpt() == IOobject::MUST_READ
			|| readOpt() == IOobject::MUST_READ_IF_MODIFIED
			)
	{
		surfZoneList& zones = *this;

		Istream& is = readStream(typeName);

		PtrList<entry> dictEntries(is);
		zones.setSize(dictEntries.size());

		label facei = 0;
		forAll(zones, zoneI)
		{
			const dictionary& dict = dictEntries[zoneI].dict();

			label zoneSize = readLabel(dict.lookup("nFaces"));
			label startFacei = readLabel(dict.lookup("startFace"));

			zones[zoneI] = surfZone
			(
				dictEntries[zoneI].keyword(),
				zoneSize,
				startFacei,
				zoneI
			);

			word geoType;
			if (dict.readIfPresent("geometricType", geoType))
			{
				zones[zoneI].geometricType() = geoType;
			}

			if (startFacei != facei)
			{
				FatalErrorInFunction
					<< "surfZones are not ordered. Start of zone " << zoneI
					<< " does not correspond to sum of preceding zones." << nl
					<< "while reading " << io.objectPath() << endl
					<< exit(FatalError);
			}

			facei += zoneSize;
		}

		// Check state of IOstream
		is.check(functionName.c_str());

		close();
	}
}


tnbLib::surfZoneIOList::surfZoneIOList
(
	const IOobject& io,
	const surfZoneList& zones
)
	:
	surfZoneList(zones),
	regIOobject(io)
{}


tnbLib::surfZoneIOList::surfZoneIOList
(
	const IOobject& io,
	surfZoneList&& zones
)
	:
	surfZoneList(move(zones)),
	regIOobject(io)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::surfZoneIOList::~surfZoneIOList()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //


// writeData member function required by regIOobject
bool tnbLib::surfZoneIOList::writeData(Ostream& os) const
{
	os << *this;
	return os.good();
}


// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

FoamFvMesh_EXPORT tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const surfZoneIOList& L)
{
	os << L.size() << nl << token::BEGIN_LIST << incrIndent << nl;

	forAll(L, i)
	{
		L[i].writeDict(os);
	}

	os << decrIndent << token::END_LIST;

	return os;
}


// ************************************************************************* //