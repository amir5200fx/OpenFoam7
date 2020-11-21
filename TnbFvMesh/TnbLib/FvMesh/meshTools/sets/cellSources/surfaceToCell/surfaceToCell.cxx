#include <surfaceToCell.hxx>

#include <polyMesh.hxx>
#include <meshSearch.hxx>
#include <triSurface.hxx>
#include <triSurfaceSearch.hxx>
#include <cellClassification.hxx>
#include <cpuTime.hxx>
#include <demandDrivenData.hxx>
#include <addToRunTimeSelectionTable.hxx>


// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(surfaceToCell, 0);
	addToRunTimeSelectionTable(topoSetSource, surfaceToCell, word);
	addToRunTimeSelectionTable(topoSetSource, surfaceToCell, istream);
}


tnbLib::topoSetSource::addToUsageTable tnbLib::surfaceToCell::usage_
(
	surfaceToCell::typeName,
	"\n    Usage: surfaceToCell"
	"<surface> <outsidePoints> <cut> <inside> <outside> <near> <curvature>\n\n"
	"    <surface> name of triSurface\n"
	"    <outsidePoints> list of points that define outside\n"
	"    <cut> boolean whether to include cells cut by surface\n"
	"    <inside>   ,,                 ,,       inside surface\n"
	"    <outside>  ,,                 ,,       outside surface\n"
	"    <near> scalar; include cells with centre <= near to surface\n"
	"    <curvature> scalar; include cells close to strong curvature"
	" on surface\n"
	"    (curvature defined as difference in surface normal at nearest"
	" point on surface for each vertex of cell)\n\n"
);


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

tnbLib::label tnbLib::surfaceToCell::getNearest
(
	const triSurfaceSearch& querySurf,
	const label pointi,
	const point& pt,
	const vector& span,
	Map<label>& cache
)
{
	Map<label>::const_iterator iter = cache.find(pointi);

	if (iter != cache.end())
	{
		// Found cached answer
		return iter();
	}
	else
	{
		pointIndexHit inter = querySurf.nearest(pt, span);

		// Triangle label (can be -1)
		label triI = inter.index();

		// Store triangle on point
		cache.insert(pointi, triI);

		return triI;
	}
}


bool tnbLib::surfaceToCell::differingPointNormals
(
	const triSurfaceSearch& querySurf,

	const vector& span,         // Current search span
	const label celli,
	const label cellTriI,       // Nearest (to cell centre) surface triangle

	Map<label>& pointToNearest  // Cache for nearest triangle to point
) const
{
	const triSurface& surf = querySurf.surface();
	const vectorField& normals = surf.faceNormals();

	const faceList& faces = mesh().faces();
	const pointField& points = mesh().points();

	const labelList& cFaces = mesh().cells()[celli];

	forAll(cFaces, cFacei)
	{
		const face& f = faces[cFaces[cFacei]];

		forAll(f, fp)
		{
			label pointi = f[fp];

			label pointTriI =
				getNearest
				(
					querySurf,
					pointi,
					points[pointi],
					span,
					pointToNearest
				);

			if (pointTriI != -1 && pointTriI != cellTriI)
			{
				scalar cosAngle = normals[pointTriI] & normals[cellTriI];

				if (cosAngle < 0.9)
				{
					return true;
				}
			}
		}
	}
	return false;
}


void tnbLib::surfaceToCell::combine(topoSet& set, const bool add) const
{
	cpuTime timer;


	if (useSurfaceOrientation_ && (includeInside_ || includeOutside_))
	{
		const meshSearch queryMesh(mesh_);

		//- Calculate for each searchPoint inside/outside status.
		boolList isInside(querySurf().calcInside(mesh_.cellCentres()));

		Info << "    Marked inside/outside using surface orientation in = "
			<< timer.cpuTimeIncrement() << " s" << endl << endl;

		forAll(isInside, celli)
		{
			if (isInside[celli] && includeInside_)
			{
				addOrDelete(set, celli, add);
			}
			else if (!isInside[celli] && includeOutside_)
			{
				addOrDelete(set, celli, add);
			}
		}
	}
	else if (includeCut_ || includeInside_ || includeOutside_)
	{
		//
		// Cut cells with surface and classify cells
		//


		// Construct search engine on mesh

		const meshSearch queryMesh(mesh_);


		// Check all 'outside' points
		forAll(outsidePoints_, outsideI)
		{
			const point& outsidePoint = outsidePoints_[outsideI];

			// Find cell point is in. Linear search.
			label celli = queryMesh.findCell(outsidePoint, -1, false);
			if (returnReduce(celli, maxOp<label>()) == -1)
			{
				FatalErrorInFunction
					<< "outsidePoint " << outsidePoint
					<< " is not inside any cell"
					<< exit(FatalError);
			}
		}

		// Cut faces with surface and classify cells

		cellClassification cellType
		(
			mesh_,
			queryMesh,
			querySurf(),
			outsidePoints_
		);


		Info << "    Marked inside/outside using surface intersection in = "
			<< timer.cpuTimeIncrement() << " s" << endl << endl;

		//- Add/remove cells using set
		forAll(cellType, celli)
		{
			label cType = cellType[celli];

			if
				(
				(
					includeCut_
					&& (cType == cellClassification::CUT)
					)
					|| (
						includeInside_
						&& (cType == cellClassification::INSIDE)
						)
					|| (
						includeOutside_
						&& (cType == cellClassification::OUTSIDE)
						)
					)
			{
				addOrDelete(set, celli, add);
			}
		}
	}


	if (nearDist_ > 0)
	{
		//
		// Determine distance to surface
		//

		const pointField& ctrs = mesh_.cellCentres();

		// Box dimensions to search in octree.
		const vector span(nearDist_, nearDist_, nearDist_);


		if (curvature_ < -1)
		{
			Info << "    Selecting cells with cellCentre closer than "
				<< nearDist_ << " to surface" << endl;

			// No need to test curvature. Insert near cells into set.

			forAll(ctrs, celli)
			{
				const point& c = ctrs[celli];

				pointIndexHit inter = querySurf().nearest(c, span);

				if (inter.hit() && (mag(inter.hitPoint() - c) < nearDist_))
				{
					addOrDelete(set, celli, add);
				}
			}

			Info << "    Determined nearest surface point in = "
				<< timer.cpuTimeIncrement() << " s" << endl << endl;

		}
		else
		{
			// Test near cells for curvature

			Info << "    Selecting cells with cellCentre closer than "
				<< nearDist_ << " to surface and curvature factor"
				<< " less than " << curvature_ << endl;

			// Cache for nearest surface triangle for a point
			Map<label> pointToNearest(mesh_.nCells() / 10);

			forAll(ctrs, celli)
			{
				const point& c = ctrs[celli];

				pointIndexHit inter = querySurf().nearest(c, span);

				if (inter.hit() && (mag(inter.hitPoint() - c) < nearDist_))
				{
					if
						(
							differingPointNormals
							(
								querySurf(),
								span,
								celli,
								inter.index(),      // nearest surface triangle
								pointToNearest
							)
							)
					{
						addOrDelete(set, celli, add);
					}
				}
			}

			Info << "    Determined nearest surface point in = "
				<< timer.cpuTimeIncrement() << " s" << endl << endl;
		}
	}
}


void tnbLib::surfaceToCell::checkSettings() const
{
	if
		(
		(nearDist_ < 0)
			&& (curvature_ < -1)
			&& (
			(includeCut_ && includeInside_ && includeOutside_)
				|| (!includeCut_ && !includeInside_ && !includeOutside_)
				)
			)
	{
		FatalErrorInFunction
			<< "Illegal include cell specification."
			<< " Result would be either all or no cells." << endl
			<< "Please set one of includeCut, includeInside, includeOutside"
			<< " to true, set nearDistance to a value > 0"
			<< " or set curvature to a value -1 .. 1."
			<< exit(FatalError);
	}

	if (useSurfaceOrientation_ && includeCut_)
	{
		FatalErrorInFunction
			<< "Illegal include cell specification."
			<< " You cannot specify both 'useSurfaceOrientation'"
			<< " and 'includeCut'"
			<< " since 'includeCut' specifies a topological split"
			<< exit(FatalError);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::surfaceToCell::surfaceToCell
(
	const polyMesh& mesh,
	const fileName& surfName,
	const pointField& outsidePoints,
	const bool includeCut,
	const bool includeInside,
	const bool includeOutside,
	const bool useSurfaceOrientation,
	const scalar nearDist,
	const scalar curvature
)
	:
	topoSetSource(mesh),
	surfName_(surfName),
	outsidePoints_(outsidePoints),
	includeCut_(includeCut),
	includeInside_(includeInside),
	includeOutside_(includeOutside),
	useSurfaceOrientation_(useSurfaceOrientation),
	nearDist_(nearDist),
	curvature_(curvature),
	surfPtr_(new triSurface(surfName_)),
	querySurfPtr_(new triSurfaceSearch(*surfPtr_)),
	IOwnPtrs_(true)
{
	checkSettings();
}


tnbLib::surfaceToCell::surfaceToCell
(
	const polyMesh& mesh,
	const fileName& surfName,
	const triSurface& surf,
	const triSurfaceSearch& querySurf,
	const pointField& outsidePoints,
	const bool includeCut,
	const bool includeInside,
	const bool includeOutside,
	const bool useSurfaceOrientation,
	const scalar nearDist,
	const scalar curvature
)
	:
	topoSetSource(mesh),
	surfName_(surfName),
	outsidePoints_(outsidePoints),
	includeCut_(includeCut),
	includeInside_(includeInside),
	includeOutside_(includeOutside),
	useSurfaceOrientation_(useSurfaceOrientation),
	nearDist_(nearDist),
	curvature_(curvature),
	surfPtr_(&surf),
	querySurfPtr_(&querySurf),
	IOwnPtrs_(false)
{
	checkSettings();
}


tnbLib::surfaceToCell::surfaceToCell
(
	const polyMesh& mesh,
	const dictionary& dict
)
	:
	topoSetSource(mesh),
	surfName_(fileName(dict.lookup("file")).expand()),
	outsidePoints_(dict.lookup("outsidePoints")),
	includeCut_(readBool(dict.lookup("includeCut"))),
	includeInside_(readBool(dict.lookup("includeInside"))),
	includeOutside_(readBool(dict.lookup("includeOutside"))),
	useSurfaceOrientation_
	(
		dict.lookupOrDefault<bool>("useSurfaceOrientation", false)
	),
	nearDist_(readScalar(dict.lookup("nearDistance"))),
	curvature_(readScalar(dict.lookup("curvature"))),
	surfPtr_(new triSurface(surfName_)),
	querySurfPtr_(new triSurfaceSearch(*surfPtr_)),
	IOwnPtrs_(true)
{
	checkSettings();
}


tnbLib::surfaceToCell::surfaceToCell
(
	const polyMesh& mesh,
	Istream& is
)
	:
	topoSetSource(mesh),
	surfName_(checkIs(is)),
	outsidePoints_(checkIs(is)),
	includeCut_(readBool(checkIs(is))),
	includeInside_(readBool(checkIs(is))),
	includeOutside_(readBool(checkIs(is))),
	useSurfaceOrientation_(false),
	nearDist_(readScalar(checkIs(is))),
	curvature_(readScalar(checkIs(is))),
	surfPtr_(new triSurface(surfName_)),
	querySurfPtr_(new triSurfaceSearch(*surfPtr_)),
	IOwnPtrs_(true)
{
	checkSettings();
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::surfaceToCell::~surfaceToCell()
{
	if (IOwnPtrs_)
	{
		deleteDemandDrivenData(surfPtr_);
		deleteDemandDrivenData(querySurfPtr_);
	}
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::surfaceToCell::applyToSet
(
	const topoSetSource::setAction action,
	topoSet& set
) const
{
	if ((action == topoSetSource::NEW) || (action == topoSetSource::ADD))
	{
		Info << "    Adding cells in relation to surface " << surfName_
			<< " ..." << endl;

		combine(set, true);
	}
	else if (action == topoSetSource::DELETE)
	{
		Info << "    Removing cells in relation to surface " << surfName_
			<< " ..." << endl;

		combine(set, false);
	}
}


// ************************************************************************* //