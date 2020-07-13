#include <targetVolumeToCell.hxx>

#include <polyMesh.hxx>
#include <globalMeshData.hxx>
#include <plane.hxx>
#include <cellSet.hxx>
#include <addToRunTimeSelectionTable.hxx>

#include <PstreamReduceOps.hxx> // added by amir

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(targetVolumeToCell, 0);
	addToRunTimeSelectionTable(topoSetSource, targetVolumeToCell, word);
	addToRunTimeSelectionTable(topoSetSource, targetVolumeToCell, istream);
}


tnbLib::topoSetSource::addToUsageTable tnbLib::targetVolumeToCell::usage_
(
	targetVolumeToCell::typeName,
	"\n    Usage: targetVolumeToCell (nx ny nz)\n\n"
	"    Adjust plane until obtained selected volume\n\n"
);


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

tnbLib::scalar tnbLib::targetVolumeToCell::volumeOfSet
(
	const PackedBoolList& selected
) const
{
	scalar sumVol = 0.0;
	forAll(selected, celli)
	{
		if (selected[celli])
		{
			sumVol += mesh_.cellVolumes()[celli];
		}
	}
	return returnReduce(sumVol, sumOp<scalar>());
}


tnbLib::label tnbLib::targetVolumeToCell::selectCells
(
	const scalar normalComp,
	const PackedBoolList& maskSet,
	PackedBoolList& selected
) const
{
	selected.setSize(mesh_.nCells());
	selected = false;

	label nSelected = 0;

	forAll(mesh_.cellCentres(), celli)
	{
		const point& cc = mesh_.cellCentres()[celli];

		if (maskSet[celli] && ((cc&n_) < normalComp))
		{
			selected[celli] = true;
			nSelected++;
		}
	}
	return returnReduce(nSelected, sumOp<label>());
}


void tnbLib::targetVolumeToCell::combine(topoSet& set, const bool add) const
{
	if (vol_ <= 0)
	{
		// Select no cells
		return;
	}


	PackedBoolList maskSet(mesh_.nCells(), 1);
	label nTotCells = mesh_.globalData().nTotalCells();
	if (maskSetName_.size())
	{
		// Read cellSet
		Info << "    Operating on subset defined by cellSet " << maskSetName_
			<< endl;

		maskSet = 0;
		cellSet subset(mesh_, maskSetName_);

		forAllConstIter(cellSet, subset, iter)
		{
			maskSet[iter.key()] = 1;
		}

		nTotCells = returnReduce(subset.size(), sumOp<label>());
	}


	// Get plane for min,max volume.
	// Planes all have base (0 0 0) and fixed normal so work only on normal
	// component.

	scalar maxComp = -great;
	label maxCells = 0;
	// scalar maxVol = 0;
	scalar minComp = great;
	{
		const boundBox& bb = mesh_.bounds();
		pointField points(bb.points());

		// label minPointi = -1;
		label maxPointi = -1;
		forAll(points, pointi)
		{
			scalar c = (points[pointi] & n_);
			if (c > maxComp)
			{
				maxComp = c;
				maxPointi = pointi;
			}
			else if (c < minComp)
			{
				minComp = c;
				// minPointi = pointi;
			}
		}

		PackedBoolList maxSelected(mesh_.nCells());
		maxCells = selectCells(maxComp, maskSet, maxSelected);
		// maxVol = volumeOfSet(maxSelected);

		// Check that maxPoint indeed selects all cells
		if (maxCells != nTotCells)
		{
			WarningInFunction
				<< "Plane " << plane(points[maxPointi], n_)
				<< " selects " << maxCells
				<< " cells instead of all " << nTotCells
				<< " cells. Results might be wrong." << endl;
		}
	}



	// Bisection
	// ~~~~~~~~~

	PackedBoolList selected(mesh_.nCells());
	label nSelected = -1;
	scalar selectedVol = 0.0;
	// scalar selectedComp = 0.0;


	scalar low = minComp;
	scalar high = maxComp;

	const scalar tolerance = small * 100 * (maxComp - minComp);

	while ((high - low) > tolerance)
	{
		scalar mid = 0.5*(low + high);

		nSelected = selectCells(mid, maskSet, selected);
		selectedVol = volumeOfSet(selected);

		// Pout<< "High:" << high << " low:" << low << " mid:" << mid << nl
		//    << "    nSelected:" << nSelected << nl
		//    << "    vol      :" << selectedVol << nl
		//    << endl;

		if (selectedVol < vol_)
		{
			low = mid;

			PackedBoolList highSelected(mesh_.nCells());
			label nHigh = selectCells(high, maskSet, selected);
			if (nSelected == nHigh)
			{
				break;
			}
		}
		else
		{
			high = mid;

			PackedBoolList lowSelected(mesh_.nCells());
			label nLow = selectCells(low, maskSet, selected);
			if (nSelected == nLow)
			{
				break;
			}
		}
	}

	nSelected = selectCells(high, maskSet, selected);
	selectedVol = volumeOfSet(selected);

	if (selectedVol < vol_)
	{
		// selectedComp = high;
	}
	else
	{
		nSelected = selectCells(low, maskSet, selected);
		selectedVol = volumeOfSet(selected);

		if (selectedVol < vol_)
		{
			// selectedComp = low;
		}
		else
		{
			WarningInFunction
				<< "Did not converge onto plane. " << nl
				<< "high plane:"
				<< plane(high*n_, n_)
				<< nl
				<< "low plane :"
				<< plane(low*n_, n_)
				<< endl;
		}
	}


	Info << "    Selected " << nSelected << " with actual volume " << selectedVol
		<< endl;

	forAll(selected, celli)
	{
		if (selected[celli])
		{
			addOrDelete(set, celli, add);
		}
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::targetVolumeToCell::targetVolumeToCell
(
	const polyMesh& mesh,
	const scalar vol,
	const vector& n
)
	:
	topoSetSource(mesh),
	vol_(vol),
	n_(n)
{}


tnbLib::targetVolumeToCell::targetVolumeToCell
(
	const polyMesh& mesh,
	const dictionary& dict
)
	:
	topoSetSource(mesh),
	vol_(readScalar(dict.lookup("volume"))),
	n_(dict.lookup("normal")),
	maskSetName_(dict.lookupOrDefault<word>("set", ""))
{}


tnbLib::targetVolumeToCell::targetVolumeToCell
(
	const polyMesh& mesh,
	Istream& is
)
	:
	topoSetSource(mesh),
	vol_(readScalar(checkIs(is))),
	n_(checkIs(is))
{}

// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::targetVolumeToCell::~targetVolumeToCell()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::targetVolumeToCell::applyToSet
(
	const topoSetSource::setAction action,
	topoSet& set
) const
{
	if ((action == topoSetSource::NEW) || (action == topoSetSource::ADD))
	{
		Info << "    Adding cells up to target volume " << vol_
			<< " out of total volume " << gSum(mesh_.cellVolumes()) << endl;

		combine(set, true);
	}
	else if (action == topoSetSource::DELETE)
	{
		Info << "    Removing cells up to target volume " << vol_
			<< " out of total volume " << gSum(mesh_.cellVolumes()) << endl;

		combine(set, false);
	}
}


// ************************************************************************* //