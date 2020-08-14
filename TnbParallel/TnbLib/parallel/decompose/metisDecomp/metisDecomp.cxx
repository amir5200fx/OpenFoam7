#include <metisDecomp.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <Time.hxx>

extern "C"
{
#define OMPI_SKIP_MPICXX
#include <metis.h>
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(metisDecomp, 0);
	addToRunTimeSelectionTable(decompositionMethod, metisDecomp, dictionary);
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

tnbLib::label tnbLib::metisDecomp::decompose
(
	const List<label>& adjncy,
	const List<label>& xadj,
	const scalarField& cWeights,

	List<label>& finalDecomp
)
{
	// Method of decomposition
	// recursive: multi-level recursive bisection (default)
	// k-way: multi-level k-way
	word method("recursive");

	label numCells = xadj.size() - 1;

	// Decomposition options
	List<label> options(METIS_NOPTIONS);
	METIS_SetDefaultOptions(options.begin());

	// Processor weights initialised with no size, only used if specified in
	// a file
	Field<real_t> processorWeights;

	// Cell weights (so on the vertices of the dual)
	List<label> cellWeights;

	// Face weights (so on the edges of the dual)
	List<label> faceWeights;


	// Check for externally provided cellweights and if so initialise weights
	scalar minWeights = gMin(cWeights);
	if (cWeights.size() > 0)
	{
		if (minWeights <= 0)
		{
			WarningInFunction
				<< "Illegal minimum weight " << minWeights
				<< endl;
		}

		if (cWeights.size() != numCells)
		{
			FatalErrorInFunction
				<< "Number of cell weights " << cWeights.size()
				<< " does not equal number of cells " << numCells
				<< exit(FatalError);
		}

		// Convert to integers.
		cellWeights.setSize(cWeights.size());
		forAll(cellWeights, i)
		{
			cellWeights[i] = int(cWeights[i] / minWeights);
		}
	}


	// Check for user supplied weights and decomp options
	if (decompositionDict_.found("metisCoeffs"))
	{
		const dictionary& metisCoeffs =
			decompositionDict_.subDict("metisCoeffs");

		word weightsFile;

		if (metisCoeffs.readIfPresent("method", method))
		{
			if (method != "recursive" && method != "k-way")
			{
				FatalErrorInFunction
					<< "Method " << method << " in metisCoeffs in dictionary : "
					<< decompositionDict_.name()
					<< " should be 'recursive' or 'k-way'"
					<< exit(FatalError);
			}

			Info << "metisDecomp : Using Metis method     " << method
				<< nl << endl;
		}

		if (metisCoeffs.readIfPresent("options", options))
		{
			if (options.size() != METIS_NOPTIONS)
			{
				FatalErrorInFunction
					<< "Number of options in metisCoeffs in dictionary : "
					<< decompositionDict_.name()
					<< " should be " << METIS_NOPTIONS
					<< exit(FatalError);
			}

			Info << "metisDecomp : Using Metis options     " << options
				<< nl << endl;
		}

		if (metisCoeffs.readIfPresent("processorWeights", processorWeights))
		{
			processorWeights /= sum(processorWeights);

			if (processorWeights.size() != nProcessors_)
			{
				FatalErrorInFunction
					<< "Number of processor weights "
					<< processorWeights.size()
					<< " does not equal number of domains " << nProcessors_
					<< exit(FatalError);
			}
		}
	}

	label ncon = 1;
	label nProcs = nProcessors_;

	// Output: cell -> processor addressing
	finalDecomp.setSize(numCells);

	// Output: number of cut edges
	label edgeCut = 0;

	if (method == "recursive")
	{
		METIS_PartGraphRecursive
		(
			&numCells,          // num vertices in graph
			&ncon,              // num balancing constraints
			const_cast<List<label>&>(xadj).begin(),   // indexing into adjncy
			const_cast<List<label>&>(adjncy).begin(), // neighbour info
			cellWeights.begin(),// vertexweights
			nullptr,               // vsize: total communication vol
			faceWeights.begin(),// edgeweights
			&nProcs,            // nParts
			processorWeights.begin(),   // tpwgts
			nullptr,               // ubvec: processor imbalance (default)
			options.begin(),
			&edgeCut,
			finalDecomp.begin()
		);
	}
	else
	{
		METIS_PartGraphKway
		(
			&numCells,          // num vertices in graph
			&ncon,              // num balancing constraints
			const_cast<List<label>&>(xadj).begin(),   // indexing into adjncy
			const_cast<List<label>&>(adjncy).begin(), // neighbour info
			cellWeights.begin(),// vertexweights
			nullptr,               // vsize: total communication vol
			faceWeights.begin(),// edgeweights
			&nProcs,            // nParts
			processorWeights.begin(),   // tpwgts
			nullptr,               // ubvec: processor imbalance (default)
			options.begin(),
			&edgeCut,
			finalDecomp.begin()
		);
	}

	return edgeCut;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::metisDecomp::metisDecomp(const dictionary& decompositionDict)
	:
	decompositionMethod(decompositionDict)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::labelList tnbLib::metisDecomp::decompose
(
	const polyMesh& mesh,
	const pointField& points,
	const scalarField& pointWeights
)
{
	if (points.size() != mesh.nCells())
	{
		FatalErrorInFunction
			<< "Can use this decomposition method only for the whole mesh"
			<< endl
			<< "and supply one coordinate (cellCentre) for every cell." << endl
			<< "The number of coordinates " << points.size() << endl
			<< "The number of cells in the mesh " << mesh.nCells()
			<< exit(FatalError);
	}

	CompactListList<label> cellCells;
	calcCellCells
	(
		mesh,
		identity(mesh.nCells()),
		mesh.nCells(),
		false,
		cellCells
	);

	// Decompose using default weights
	labelList decomp;
	decompose(cellCells.m(), cellCells.offsets(), pointWeights, decomp);

	return decomp;
}


tnbLib::labelList tnbLib::metisDecomp::decompose
(
	const polyMesh& mesh,
	const labelList& agglom,
	const pointField& agglomPoints,
	const scalarField& agglomWeights
)
{
	if (agglom.size() != mesh.nCells())
	{
		FatalErrorInFunction
			<< "Size of cell-to-coarse map " << agglom.size()
			<< " differs from number of cells in mesh " << mesh.nCells()
			<< exit(FatalError);
	}

	// Make Metis CSR (Compressed Storage Format) storage
	//   adjncy      : contains neighbours (= edges in graph)
	//   xadj(celli) : start of information in adjncy for celli

	CompactListList<label> cellCells;
	calcCellCells(mesh, agglom, agglomPoints.size(), false, cellCells);

	// Decompose using default weights
	labelList finalDecomp;
	decompose(cellCells.m(), cellCells.offsets(), agglomWeights, finalDecomp);


	// Rework back into decomposition for original mesh
	labelList fineDistribution(agglom.size());

	forAll(fineDistribution, i)
	{
		fineDistribution[i] = finalDecomp[agglom[i]];
	}

	return fineDistribution;
}


tnbLib::labelList tnbLib::metisDecomp::decompose
(
	const labelListList& globalCellCells,
	const pointField& cellCentres,
	const scalarField& cellWeights
)
{
	if (cellCentres.size() != globalCellCells.size())
	{
		FatalErrorInFunction
			<< "Inconsistent number of cells (" << globalCellCells.size()
			<< ") and number of cell centres (" << cellCentres.size()
			<< ")." << exit(FatalError);
	}


	// Make Metis CSR (Compressed Storage Format) storage
	//   adjncy      : contains neighbours (= edges in graph)
	//   xadj(celli) : start of information in adjncy for celli

	CompactListList<label> cellCells(globalCellCells);

	// Decompose using default weights
	labelList decomp;
	decompose(cellCells.m(), cellCells.offsets(), cellWeights, decomp);

	return decomp;
}


// ************************************************************************* //