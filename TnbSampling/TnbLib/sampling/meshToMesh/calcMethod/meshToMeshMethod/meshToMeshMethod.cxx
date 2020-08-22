#include <meshToMeshMethod.hxx>

#include <tetOverlapVolume.hxx>
#include <OFstream.hxx>
#include <Time.hxx>
#include <treeBoundBox.hxx>

#include <Pstream.hxx>  // added by amir

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(meshToMeshMethod, 0);
	defineRunTimeSelectionTable(meshToMeshMethod, components);
}

tnbLib::scalar tnbLib::meshToMeshMethod::tolerance_ = 1e-6;

// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

tnbLib::labelList tnbLib::meshToMeshMethod::maskCells() const
{
	boundBox intersectBb
	(
		max(src_.bounds().min(), tgt_.bounds().min()),
		min(src_.bounds().max(), tgt_.bounds().max())
	);

	intersectBb.inflate(0.01);

	const cellList& srcCells = src_.cells();
	const faceList& srcFaces = src_.faces();
	const pointField& srcPts = src_.points();

	DynamicList<label> cells(src_.nCells());
	forAll(srcCells, srcI)
	{
		boundBox cellBb(srcCells[srcI].points(srcFaces, srcPts), false);
		if (intersectBb.overlaps(cellBb))
		{
			cells.append(srcI);
		}
	}

	if (debug)
	{
		Pout << "participating source mesh cells: " << cells.size() << endl;
	}

	return move(cells);
}


bool tnbLib::meshToMeshMethod::intersect
(
	const label srcCelli,
	const label tgtCelli
) const
{
	scalar threshold = tolerance_ * src_.cellVolumes()[srcCelli];

	tetOverlapVolume overlapEngine;

	treeBoundBox bbTgtCell(tgt_.points(), tgt_.cellPoints()[tgtCelli]);

	return overlapEngine.cellCellOverlapMinDecomp
	(
		src_,
		srcCelli,
		tgt_,
		tgtCelli,
		bbTgtCell,
		threshold
	);
}


tnbLib::scalar tnbLib::meshToMeshMethod::interVol
(
	const label srcCelli,
	const label tgtCelli
) const
{
	tetOverlapVolume overlapEngine;

	treeBoundBox bbTgtCell(tgt_.points(), tgt_.cellPoints()[tgtCelli]);

	scalar vol = overlapEngine.cellCellOverlapVolumeMinDecomp
	(
		src_,
		srcCelli,
		tgt_,
		tgtCelli,
		bbTgtCell
	);

	return vol;
}


void tnbLib::meshToMeshMethod::appendNbrCells
(
	const label celli,
	const polyMesh& mesh,
	const DynamicList<label>& visitedCells,
	DynamicList<label>& nbrCellIDs
) const
{
	const labelList& nbrCells = mesh.cellCells()[celli];

	// filter out cells already visited from cell neighbours
	forAll(nbrCells, i)
	{
		label nbrCelli = nbrCells[i];

		if
			(
			(findIndex(visitedCells, nbrCelli) == -1)
				&& (findIndex(nbrCellIDs, nbrCelli) == -1)
				)
		{
			nbrCellIDs.append(nbrCelli);
		}
	}
}


bool tnbLib::meshToMeshMethod::initialise
(
	labelListList& srcToTgtAddr,
	scalarListList& srcToTgtWght,
	labelListList& tgtToSrcAddr,
	scalarListList& tgtToSrcWght
) const
{
	srcToTgtAddr.setSize(src_.nCells());
	srcToTgtWght.setSize(src_.nCells());
	tgtToSrcAddr.setSize(tgt_.nCells());
	tgtToSrcWght.setSize(tgt_.nCells());

	if (!src_.nCells())
	{
		return false;
	}
	else if (!tgt_.nCells())
	{
		if (debug)
		{
			Pout << "mesh interpolation: hhave " << src_.nCells() << " source "
				<< " cells but no target cells" << endl;
		}

		return false;
	}

	return true;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::meshToMeshMethod::meshToMeshMethod
(
	const polyMesh& src,
	const polyMesh& tgt
)
	:
	src_(src),
	tgt_(tgt),
	V_(0.0)
{
	if (!src_.nCells() || !tgt_.nCells())
	{
		if (debug)
		{
			Pout << "mesh interpolation: cells not on processor: Source cells = "
				<< src_.nCells() << ", target cells = " << tgt_.nCells()
				<< endl;
		}
	}
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::meshToMeshMethod::~meshToMeshMethod()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::meshToMeshMethod::writeConnectivity
(
	const polyMesh& mesh1,
	const polyMesh& mesh2,
	const labelListList& mesh1ToMesh2Addr
) const
{
	Pout << "Source size = " << mesh1.nCells() << endl;
	Pout << "Target size = " << mesh2.nCells() << endl;

	word fName("addressing_" + mesh1.name() + "_to_" + mesh2.name());

	if (Pstream::parRun())
	{
		fName = fName + "_proc" + tnbLib::name(Pstream::myProcNo());
	}

	OFstream os(src_.time().path() / fName + ".obj");

	label vertI = 0;
	forAll(mesh1ToMesh2Addr, i)
	{
		const labelList& addr = mesh1ToMesh2Addr[i];
		forAll(addr, j)
		{
			label celli = addr[j];
			const vector& c0 = mesh1.cellCentres()[i];

			const cell& c = mesh2.cells()[celli];
			const pointField pts(c.points(mesh2.faces(), mesh2.points()));
			forAll(pts, j)
			{
				const point& p = pts[j];
				os << "v " << p.x() << ' ' << p.y() << ' ' << p.z() << nl;
				vertI++;
				os << "v " << c0.x() << ' ' << c0.y() << ' ' << c0.z()
					<< nl;
				vertI++;
				os << "l " << vertI - 1 << ' ' << vertI << nl;
			}
		}
	}
}


// ************************************************************************* //