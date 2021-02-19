#include <powerLawLopesdaCosta.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <geometricOneField.hxx>
#include <fvMatrices.hxx>
#include <triSurfaceMesh.hxx>
#include <triSurfaceTools.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace porosityModels
	{
		defineTypeNameAndDebug(powerLawLopesdaCosta, 0);
		addToRunTimeSelectionTable(porosityModel, powerLawLopesdaCosta, mesh);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::porosityModels::powerLawLopesdaCostaZone::powerLawLopesdaCostaZone
(
	const word& name,
	const word& modelType,
	const fvMesh& mesh,
	const dictionary& dict
)
	:
	zoneName_(name + ":porousZone")
{
	dictionary coeffs(dict.optionalSubDict(modelType + "Coeffs"));

	// Vertical direction within porous region
	vector zDir(coeffs.lookup("zDir"));

	// Span of the search for the cells in the porous region
	scalar searchSpan(readScalar(coeffs.lookup("searchSpan")));

	// Top surface file name defining the extent of the porous region
	word topSurfaceFileName(coeffs.lookup("topSurface"));

	// List of the ground patches defining the lower surface
	// of the porous region
	List<wordRe> groundPatches(coeffs.lookup("groundPatches"));

	// Functional form of the porosity surface area per unit volume as a
	// function of the normalized vertical position
	autoPtr<Function1<scalar >> SigmaFunc
	(
		Function1<scalar>::New("Sigma", dict)
	);

	// Searchable triSurface for the top of the porous region
	triSurfaceMesh searchSurf
	(
		IOobject
		(
			topSurfaceFileName,
			mesh.time().constant(),
			"triSurface",
			mesh.time()
		)
	);

	// Limit the porous cell search to those within the lateral and vertical
	// extent of the top surface

	boundBox surfBounds(searchSurf.points());
	boundBox searchBounds
	(
		surfBounds.min() - searchSpan * zDir, surfBounds.max()
	);

	const pointField& C = mesh.cellCentres();

	// List of cells within the porous region
	labelList porousCells(C.size());
	label porousCelli = 0;

	forAll(C, celli)
	{
		if (searchBounds.contains(C[celli]))
		{
			porousCells[porousCelli++] = celli;
		}
	}

	porousCells.setSize(porousCelli);

	pointField start(porousCelli);
	pointField end(porousCelli);

	forAll(porousCells, porousCelli)
	{
		start[porousCelli] = C[porousCells[porousCelli]];
		end[porousCelli] = start[porousCelli] + searchSpan * zDir;
	}

	// Field of distance between the cell centre and the corresponding point
	// on the porous region top surface
	scalarField zTop(porousCelli);

	// Search the porous cells for those with a corresponding point on the
	// porous region top surface
	List<pointIndexHit> hitInfo;
	searchSurf.findLine(start, end, hitInfo);

	porousCelli = 0;

	forAll(porousCells, celli)
	{
		const pointIndexHit& hit = hitInfo[celli];

		if (hit.hit())
		{
			porousCells[porousCelli] = porousCells[celli];

			zTop[porousCelli] =
				(hit.hitPoint() - C[porousCells[porousCelli]]) & zDir;

			porousCelli++;
		}
	}

	// Resize the porous cells list and height field
	porousCells.setSize(porousCelli);
	zTop.setSize(porousCelli);

	// Create a triSurface for the ground patch(s)
	triSurface groundSurface
	(
		triSurfaceTools::triangulate
		(
			mesh.boundaryMesh(),
			mesh.boundaryMesh().patchSet(groundPatches),
			searchBounds
		)
	);

	// Combine the ground triSurfaces across all processors
	if (Pstream::parRun())
	{
		List<List<labelledTri>> groundSurfaceProcTris(Pstream::nProcs());
		List<pointField> groundSurfaceProcPoints(Pstream::nProcs());

		groundSurfaceProcTris[Pstream::myProcNo()] = groundSurface;
		groundSurfaceProcPoints[Pstream::myProcNo()] = groundSurface.points();

		Pstream::gatherList(groundSurfaceProcTris);
		Pstream::scatterList(groundSurfaceProcTris);
		Pstream::gatherList(groundSurfaceProcPoints);
		Pstream::scatterList(groundSurfaceProcPoints);

		label nTris = 0;
		forAll(groundSurfaceProcTris, i)
		{
			nTris += groundSurfaceProcTris[i].size();
		}

		List<labelledTri> groundSurfaceTris(nTris);
		label trii = 0;
		label offset = 0;
		forAll(groundSurfaceProcTris, i)
		{
			forAll(groundSurfaceProcTris[i], j)
			{
				groundSurfaceTris[trii] = groundSurfaceProcTris[i][j];
				groundSurfaceTris[trii][0] += offset;
				groundSurfaceTris[trii][1] += offset;
				groundSurfaceTris[trii][2] += offset;
				trii++;
			}
			offset += groundSurfaceProcPoints[i].size();
		}

		label nPoints = 0;
		forAll(groundSurfaceProcPoints, i)
		{
			nPoints += groundSurfaceProcPoints[i].size();
		}

		pointField groundSurfacePoints(nPoints);

		label pointi = 0;
		forAll(groundSurfaceProcPoints, i)
		{
			forAll(groundSurfaceProcPoints[i], j)
			{
				groundSurfacePoints[pointi++] = groundSurfaceProcPoints[i][j];
			}
		}

		groundSurface = triSurface(groundSurfaceTris, groundSurfacePoints);
	}

	// Create a searchable triSurface for the ground
	triSurfaceSearch groundSearch(groundSurface);

	// Search the porous cells for the corresponding point on the ground

	start.setSize(porousCelli);
	end.setSize(porousCelli);

	forAll(porousCells, porousCelli)
	{
		start[porousCelli] = C[porousCells[porousCelli]];
		end[porousCelli] = start[porousCelli] - searchSpan * zDir;
	}

	groundSearch.findLine(start, end, hitInfo);

	scalarField zBottom(porousCelli);

	forAll(porousCells, porousCelli)
	{
		const pointIndexHit& hit = hitInfo[porousCelli];

		if (hit.hit())
		{
			zBottom[porousCelli] =
				(C[porousCells[porousCelli]] - hit.hitPoint()) & zDir;
		}
	}

	// Create the normalized height field
	scalarField zNorm(zBottom / (zBottom + zTop));

	// Create the porosity surface area per unit volume zone field
	Sigma_ = SigmaFunc->value(zNorm);

	// Create the porous region cellZone and add to the mesh cellZones

	cellZoneMesh& cellZones = const_cast<cellZoneMesh&>(mesh.cellZones());

	label zoneID = cellZones.findZoneID(zoneName_);

	if (zoneID == -1)
	{
		zoneID = cellZones.size();
		cellZones.setSize(zoneID + 1);

		cellZones.set
		(
			zoneID,
			new cellZone
			(
				zoneName_,
				porousCells,
				zoneID,
				cellZones
			)
		);
	}
	else
	{
		FatalErrorInFunction
			<< "Unable to create porous cellZone " << zoneName_
			<< ": zone already exists"
			<< abort(FatalError);
	}
}


tnbLib::porosityModels::powerLawLopesdaCosta::powerLawLopesdaCosta
(
	const word& name,
	const word& modelType,
	const fvMesh& mesh,
	const dictionary& dict,
	const word& dummyCellZoneName
)
	:
	powerLawLopesdaCostaZone(name, modelType, mesh, dict),
	porosityModel
	(
		name,
		modelType,
		mesh,
		dict,
		powerLawLopesdaCostaZone::zoneName_
	),
	Cd_(readScalar(coeffs_.lookup("Cd"))),
	C1_(readScalar(coeffs_.lookup("C1"))),
	rhoName_(coeffs_.lookupOrDefault<word>("rho", "rho"))
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::porosityModels::powerLawLopesdaCosta::~powerLawLopesdaCosta()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

const tnbLib::scalarField&
tnbLib::porosityModels::powerLawLopesdaCostaZone::Sigma() const
{
	return Sigma_;
}


void tnbLib::porosityModels::powerLawLopesdaCosta::calcTransformModelData()
{}


void tnbLib::porosityModels::powerLawLopesdaCosta::calcForce
(
	const volVectorField& U,
	const volScalarField& rho,
	const volScalarField& mu,
	vectorField& force
) const
{
	scalarField Udiag(U.size(), 0.0);
	const scalarField& V = mesh_.V();

	apply(Udiag, V, rho, U);

	force = Udiag * U;
}


void tnbLib::porosityModels::powerLawLopesdaCosta::correct
(
	fvVectorMatrix& UEqn
) const
{
	const vectorField& U = UEqn.psi();
	const scalarField& V = mesh_.V();
	scalarField& Udiag = UEqn.diag();

	if (UEqn.dimensions() == dimForce)
	{
		const volScalarField& rho =
			mesh_.lookupObject<volScalarField>(rhoName_);

		apply(Udiag, V, rho, U);
	}
	else
	{
		apply(Udiag, V, geometricOneField(), U);
	}
}


void tnbLib::porosityModels::powerLawLopesdaCosta::correct
(
	fvVectorMatrix& UEqn,
	const volScalarField& rho,
	const volScalarField& mu
) const
{
	const vectorField& U = UEqn.psi();
	const scalarField& V = mesh_.V();
	scalarField& Udiag = UEqn.diag();

	apply(Udiag, V, rho, U);
}


void tnbLib::porosityModels::powerLawLopesdaCosta::correct
(
	const fvVectorMatrix& UEqn,
	volTensorField& AU
) const
{
	const vectorField& U = UEqn.psi();

	if (UEqn.dimensions() == dimForce)
	{
		const volScalarField& rho =
			mesh_.lookupObject<volScalarField>(rhoName_);

		apply(AU, rho, U);
	}
	else
	{
		apply(AU, geometricOneField(), U);
	}
}


bool tnbLib::porosityModels::powerLawLopesdaCosta::writeData(Ostream& os) const
{
	os << indent << name_ << endl;
	dict_.write(os);

	return true;
}


// ************************************************************************* //