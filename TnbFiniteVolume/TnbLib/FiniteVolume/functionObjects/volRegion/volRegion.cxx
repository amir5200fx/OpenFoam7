#define FoamNamedEnum_EXPORT_DEFINE
#include <volRegion.hxx>

#include <volMesh.hxx>
#include <globalMeshData.hxx>

#include <PstreamReduceOps.hxx>  // added by amir

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionObjects
	{
		defineTypeNameAndDebug(volRegion, 0);
	}
}

template<>
const char*
tnbLib::NamedEnum
<
	tnbLib::functionObjects::volRegion::regionTypes,
	2
>::names[] = { "cellZone", "all" };

const tnbLib::NamedEnum
<
	tnbLib::functionObjects::volRegion::regionTypes,
	2
> tnbLib::functionObjects::volRegion::regionTypeNames_;


// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

void tnbLib::functionObjects::volRegion::writeFileHeader
(
	const writeFile& wf,
	Ostream& file
)
{
	wf.writeCommented(file, "Region");
	file << setw(1) << ':' << setw(1) << ' '
		<< regionTypeNames_[regionType_] << " " << regionName_ << endl;
	wf.writeHeaderValue(file, "Cells", nCells_);
	wf.writeHeaderValue(file, "Volume", V_);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::functionObjects::volRegion::volRegion
(
	const fvMesh& mesh,
	const dictionary& dict
)
	:
	mesh_(mesh),
	regionType_
	(
		dict.found("regionType")
		? regionTypeNames_.read(dict.lookup("regionType"))
		: vrtAll
	),
	regionID_(-1)
{
	read(dict);

	// Cache integral properties of the region for writeFileHeader
	nCells_ = nCells();
	V_ = V();
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::functionObjects::volRegion::~volRegion()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::functionObjects::volRegion::read
(
	const dictionary& dict
)
{
	switch (regionType_)
	{
	case vrtCellZone:
	{
		dict.lookup("name") >> regionName_;

		regionID_ = mesh_.cellZones().findZoneID(regionName_);

		if (regionID_ < 0)
		{
			FatalIOErrorInFunction(dict)
				<< "Unknown cell zone name: " << regionName_
				<< ". Valid cell zones are: " << mesh_.cellZones().names()
				<< exit(FatalIOError);
		}

		if (nCells() == 0)
		{
			FatalIOErrorInFunction(dict)
				<< regionTypeNames_[regionType_]
				<< "(" << regionName_ << "):" << nl
				<< "    Region has no cells"
				<< exit(FatalIOError);
		}

		break;
	}

	case vrtAll:
	{
		break;
	}

	default:
	{
		FatalIOErrorInFunction(dict)
			<< "Unknown region type. Valid region types are:"
			<< regionTypeNames_
			<< exit(FatalIOError);
	}
	}

	return true;
}


const tnbLib::labelList& tnbLib::functionObjects::volRegion::cellIDs() const
{
	if (regionType_ == vrtAll)
	{
		return labelList::null();
	}
	else
	{
		return mesh_.cellZones()[regionID_];
	}
}


tnbLib::label tnbLib::functionObjects::volRegion::nCells() const
{
	if (regionType_ == vrtAll)
	{
		return mesh_.globalData().nTotalCells();
	}
	else
	{
		return returnReduce(cellIDs().size(), sumOp<label>());
	}
}


tnbLib::scalar tnbLib::functionObjects::volRegion::V() const
{
	if (regionType_ == vrtAll)
	{
		return gSum(mesh_.V());
	}
	else
	{
		return gSum(scalarField(mesh_.V(), cellIDs()));
	}
}


// ************************************************************************* //