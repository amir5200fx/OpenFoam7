#define FoamNamedEnum_EXPORT_DEFINE

#include <shellSurfaces.hxx>

#include <searchableSurface.hxx>
#include <boundBox.hxx>
#include <triSurfaceMesh.hxx>
#include <refinementSurfaces.hxx>
#include <searchableSurfaces.hxx>
#include <orientedSurface.hxx>
#include <pointIndexHit.hxx>
#include <volumeType.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //


namespace tnbLib
{

	template<>
	const char*
		NamedEnum<shellSurfaces::refineMode, 3>::
		names[] =
	{
		"inside",
		"outside",
		"distance"
	};

	const NamedEnum<shellSurfaces::refineMode, 3> shellSurfaces::refineModeNames_;

} // End namespace tnbLib



// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::shellSurfaces::setAndCheckLevels
(
	const label shellI,
	const List<Tuple2<scalar, label>>& distLevels
)
{
	if (modes_[shellI] != DISTANCE && distLevels.size() != 1)
	{
		FatalErrorInFunction
			<< "For refinement mode "
			<< refineModeNames_[modes_[shellI]]
			<< " specify only one distance+level."
			<< " (its distance gets discarded)"
			<< exit(FatalError);
	}
	// Extract information into separate distance and level
	distances_[shellI].setSize(distLevels.size());
	levels_[shellI].setSize(distLevels.size());

	forAll(distLevels, j)
	{
		distances_[shellI][j] = distLevels[j].first();
		levels_[shellI][j] = distLevels[j].second();

		// Check in incremental order
		if (j > 0)
		{
			if
				(
				(distances_[shellI][j] <= distances_[shellI][j - 1])
					|| (levels_[shellI][j] > levels_[shellI][j - 1])
					)
			{
				FatalErrorInFunction
					<< "For refinement mode "
					<< refineModeNames_[modes_[shellI]]
					<< " : Refinement should be specified in order"
					<< " of increasing distance"
					<< " (and decreasing refinement level)." << endl
					<< "Distance:" << distances_[shellI][j]
					<< " refinementLevel:" << levels_[shellI][j]
					<< exit(FatalError);
			}
		}
	}

	const searchableSurface& shell = allGeometry_[shells_[shellI]];

	if (modes_[shellI] == DISTANCE)
	{
		Info << "Refinement level according to distance to "
			<< shell.name() << endl;
		forAll(levels_[shellI], j)
		{
			Info << "    level " << levels_[shellI][j]
				<< " for all cells within " << distances_[shellI][j]
				<< " metre." << endl;
		}
	}
	else
	{
		if (!allGeometry_[shells_[shellI]].hasVolumeType())
		{
			FatalErrorInFunction
				<< "Shell " << shell.name()
				<< " does not support testing for "
				<< refineModeNames_[modes_[shellI]] << endl
				<< "Probably it is not closed."
				<< exit(FatalError);
		}

		if (modes_[shellI] == INSIDE)
		{
			Info << "Refinement level " << levels_[shellI][0]
				<< " for all cells inside " << shell.name() << endl;
		}
		else
		{
			Info << "Refinement level " << levels_[shellI][0]
				<< " for all cells outside " << shell.name() << endl;
		}
	}
}


// Specifically orient triSurfaces using a calculated point outside.
// Done since quite often triSurfaces not of consistent orientation which
// is (currently) necessary for sideness calculation
void tnbLib::shellSurfaces::orient()
{
	// Determine outside point.
	boundBox overallBb = boundBox::invertedBox;

	bool hasSurface = false;

	forAll(shells_, shellI)
	{
		const searchableSurface& s = allGeometry_[shells_[shellI]];

		if (modes_[shellI] != DISTANCE && isA<triSurfaceMesh>(s))
		{
			const triSurfaceMesh& shell = refCast<const triSurfaceMesh>(s);

			if (shell.triSurface::size())
			{
				const pointField& points = shell.points();

				hasSurface = true;

				boundBox shellBb(points[0], points[0]);
				// Assume surface is compact!
				forAll(points, i)
				{
					const point& pt = points[i];
					shellBb.min() = min(shellBb.min(), pt);
					shellBb.max() = max(shellBb.max(), pt);
				}

				overallBb.min() = min(overallBb.min(), shellBb.min());
				overallBb.max() = max(overallBb.max(), shellBb.max());
			}
		}
	}

	if (hasSurface)
	{
		const point outsidePt = overallBb.max() + overallBb.span();

		// Info<< "Using point " << outsidePt << " to orient shells" << endl;

		forAll(shells_, shellI)
		{
			const searchableSurface& s = allGeometry_[shells_[shellI]];

			if (modes_[shellI] != DISTANCE && isA<triSurfaceMesh>(s))
			{
				triSurfaceMesh& shell = const_cast<triSurfaceMesh&>
					(
						refCast<const triSurfaceMesh>(s)
						);

				// Flip surface so outsidePt is outside.
				bool anyFlipped = orientedSurface::orient
				(
					shell,
					outsidePt,
					true
				);

				if (anyFlipped)
				{
					// orientedSurface will have done a clearOut of the surface.
					// we could do a clearout of the triSurfaceMeshes::trees()
					// but these aren't affected by orientation
					// (except for cached
					// sideness which should not be set at this point.
					// !!Should check!)

					Info << "shellSurfaces : Flipped orientation of surface "
						<< s.name()
						<< " so point " << outsidePt << " is outside." << endl;
				}
			}
		}
	}
}


// Find maximum level of a shell.
void tnbLib::shellSurfaces::findHigherLevel
(
	const pointField& pt,
	const label shellI,
	labelList& maxLevel
) const
{
	const labelList& levels = levels_[shellI];

	if (modes_[shellI] == DISTANCE)
	{
		// Distance mode.

		const scalarField& distances = distances_[shellI];

		// Collect all those points that have a current maxLevel less than
		// (any of) the shell. Also collect the furthest distance allowable
		// to any shell with a higher level.

		pointField candidates(pt.size());
		labelList candidateMap(pt.size());
		scalarField candidateDistSqr(pt.size());
		label candidateI = 0;

		forAll(maxLevel, pointi)
		{
			forAllReverse(levels, levelI)
			{
				if (levels[levelI] > maxLevel[pointi])
				{
					candidates[candidateI] = pt[pointi];
					candidateMap[candidateI] = pointi;
					candidateDistSqr[candidateI] = sqr(distances[levelI]);
					candidateI++;
					break;
				}
			}
		}
		candidates.setSize(candidateI);
		candidateMap.setSize(candidateI);
		candidateDistSqr.setSize(candidateI);

		// Do the expensive nearest test only for the candidate points.
		List<pointIndexHit> nearInfo;
		allGeometry_[shells_[shellI]].findNearest
		(
			candidates,
			candidateDistSqr,
			nearInfo
		);

		// Update maxLevel
		forAll(nearInfo, candidateI)
		{
			if (nearInfo[candidateI].hit())
			{
				// Check which level it actually is in.
				label minDistI = findLower
				(
					distances,
					mag(nearInfo[candidateI].hitPoint() - candidates[candidateI])
				);

				label pointi = candidateMap[candidateI];

				// pt is in between shell[minDistI] and shell[minDistI+1]
				maxLevel[pointi] = levels[minDistI + 1];
			}
		}
	}
	else
	{
		// Inside/outside mode

		// Collect all those points that have a current maxLevel less than the
		// shell.

		pointField candidates(pt.size());
		labelList candidateMap(pt.size());
		label candidateI = 0;

		forAll(maxLevel, pointi)
		{
			if (levels[0] > maxLevel[pointi])
			{
				candidates[candidateI] = pt[pointi];
				candidateMap[candidateI] = pointi;
				candidateI++;
			}
		}
		candidates.setSize(candidateI);
		candidateMap.setSize(candidateI);

		// Do the expensive nearest test only for the candidate points.
		List<volumeType> volType;
		allGeometry_[shells_[shellI]].getVolumeType(candidates, volType);

		forAll(volType, i)
		{
			label pointi = candidateMap[i];

			if
				(
				(
					modes_[shellI] == INSIDE
					&& volType[i] == volumeType::inside
					)
					|| (
						modes_[shellI] == OUTSIDE
						&& volType[i] == volumeType::outside
						)
					)
			{
				maxLevel[pointi] = levels[0];
			}
		}
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::shellSurfaces::shellSurfaces
(
	const searchableSurfaces& allGeometry,
	const dictionary& shellsDict
)
	:
	allGeometry_(allGeometry)
{
	// Wildcard specification : loop over all surfaces and try to find a match.

	// Count number of shells.
	label shellI = 0;
	forAll(allGeometry.names(), geomI)
	{
		const word& geomName = allGeometry_.names()[geomI];

		if (shellsDict.found(geomName))
		{
			shellI++;
		}
	}


	// Size lists
	shells_.setSize(shellI);
	modes_.setSize(shellI);
	distances_.setSize(shellI);
	levels_.setSize(shellI);

	HashSet<word> unmatchedKeys(shellsDict.toc());
	shellI = 0;

	forAll(allGeometry_.names(), geomI)
	{
		const word& geomName = allGeometry_.names()[geomI];

		const entry* ePtr = shellsDict.lookupEntryPtr(geomName, false, true);

		if (ePtr)
		{
			const dictionary& dict = ePtr->dict();
			unmatchedKeys.erase(ePtr->keyword());

			shells_[shellI] = geomI;
			modes_[shellI] = refineModeNames_.read(dict.lookup("mode"));

			// Read pairs of distance+level
			setAndCheckLevels(shellI, dict.lookup("levels"));

			shellI++;
		}
	}

	if (unmatchedKeys.size() > 0)
	{
		IOWarningInFunction
		(
			shellsDict
		) << "Not all entries in refinementRegions dictionary were used."
			<< " The following entries were not used : "
			<< unmatchedKeys.sortedToc()
			<< endl;
	}

	// Orient shell surfaces before any searching is done. Note that this
	// only needs to be done for inside or outside. Orienting surfaces
	// constructs lots of addressing which we want to avoid.
	orient();
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

// Highest shell level
tnbLib::label tnbLib::shellSurfaces::maxLevel() const
{
	label overallMax = 0;
	forAll(levels_, shellI)
	{
		overallMax = max(overallMax, max(levels_[shellI]));
	}
	return overallMax;
}


void tnbLib::shellSurfaces::findHigherLevel
(
	const pointField& pt,
	const labelList& ptLevel,
	labelList& maxLevel
) const
{
	// Maximum level of any shell. Start off with level of point.
	maxLevel = ptLevel;

	forAll(shells_, shellI)
	{
		findHigherLevel(pt, shellI, maxLevel);
	}
}


// ************************************************************************* //