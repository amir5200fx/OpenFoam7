#define FoamNamedEnum_EXPORT_DEFINE

#include <cellSetOption.hxx>

#include <volFields.hxx>
#include <PstreamReduceOps.hxx>  // added by amir

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace fv
	{
		defineTypeNameAndDebug(cellSetOption, 0);
	}

	template<> const char* NamedEnum
		<
		fv::cellSetOption::selectionModeType,
		4
		>::names[] =
	{
		"points",
		"cellSet",
		"cellZone",
		"all"
	};

	const NamedEnum<fv::cellSetOption::selectionModeType, 4>
		fv::cellSetOption::selectionModeTypeNames_;
}


// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

void tnbLib::fv::cellSetOption::setSelection(const dictionary& dict)
{
	switch (selectionMode_)
	{
	case smPoints:
	{
		dict.lookup("points") >> points_;
		break;
	}
	case smCellSet:
	{
		dict.lookup("cellSet") >> cellSetName_;
		break;
	}
	case smCellZone:
	{
		dict.lookup("cellZone") >> cellSetName_;
		break;
	}
	case smAll:
	{
		break;
	}
	default:
	{
		FatalErrorInFunction
			<< "Unknown selectionMode "
			<< selectionModeTypeNames_[selectionMode_]
			<< ". Valid selectionMode types are" << selectionModeTypeNames_
			<< exit(FatalError);
	}
	}
}


void tnbLib::fv::cellSetOption::setCellSet()
{
	switch (selectionMode_)
	{
	case smPoints:
	{
		Info << indent << "- selecting cells using points" << endl;

		labelHashSet selectedCells;

		forAll(points_, i)
		{
			label celli = mesh_.findCell(points_[i]);
			if (celli >= 0)
			{
				selectedCells.insert(celli);
			}

			label globalCelli = returnReduce(celli, maxOp<label>());
			if (globalCelli < 0)
			{
				WarningInFunction
					<< "Unable to find owner cell for point " << points_[i]
					<< endl;
			}

		}

		cells_ = selectedCells.toc();

		break;
	}
	case smCellSet:
	{
		Info << indent
			<< "- selecting cells using cellSet " << cellSetName_ << endl;

		cellSet selectedCells(mesh_, cellSetName_);
		cells_ = selectedCells.toc();

		break;
	}
	case smCellZone:
	{
		Info << indent
			<< "- selecting cells using cellZone " << cellSetName_ << endl;

		label zoneID = mesh_.cellZones().findZoneID(cellSetName_);
		if (zoneID == -1)
		{
			FatalErrorInFunction
				<< "Cannot find cellZone " << cellSetName_ << endl
				<< "Valid cellZones are " << mesh_.cellZones().names()
				<< exit(FatalError);
		}
		cells_ = mesh_.cellZones()[zoneID];

		break;
	}
	case smAll:
	{
		Info << indent << "- selecting all cells" << endl;
		cells_ = identity(mesh_.nCells());

		break;
	}
	default:
	{
		FatalErrorInFunction
			<< "Unknown selectionMode "
			<< selectionModeTypeNames_[selectionMode_]
			<< ". Valid selectionMode types are" << selectionModeTypeNames_
			<< exit(FatalError);
	}
	}

	// Set volume information
	V_ = 0.0;
	forAll(cells_, i)
	{
		V_ += mesh_.V()[cells_[i]];
	}
	reduce(V_, sumOp<scalar>());

	Info << indent
		<< "- selected " << returnReduce(cells_.size(), sumOp<label>())
		<< " cell(s) with volume " << V_ << endl;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::fv::cellSetOption::cellSetOption
(
	const word& name,
	const word& modelType,
	const dictionary& dict,
	const fvMesh& mesh
)
	:
	option(name, modelType, dict, mesh),
	timeStart_(-1.0),
	duration_(0.0),
	selectionMode_
	(
		selectionModeTypeNames_.read(coeffs_.lookup("selectionMode"))
	),
	cellSetName_("none"),
	V_(0.0)
{
	Info << incrIndent;
	read(dict);
	setSelection(coeffs_);
	setCellSet();
	Info << decrIndent;
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::fv::cellSetOption::~cellSetOption()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::fv::cellSetOption::isActive()
{
	if (option::isActive() && inTimeLimits(mesh_.time().value()))
	{
		// Update the cell set if the mesh is changing
		if (mesh_.changing())
		{
			setCellSet();
		}

		return true;
	}
	else
	{
		return false;
	}
}


// ************************************************************************* //