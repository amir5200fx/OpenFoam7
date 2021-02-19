#include <rotorDiskSource.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <trimModel.hxx>
#include <fvMatrices.hxx>
#include <geometricOneField.hxx>
#include <syncTools.hxx>

using namespace tnbLib::constant;

// * * * * * * * * * * * * * Static Member Functions * * * * * * * * * * * * //

namespace tnbLib
{
	namespace fv
	{
		defineTypeNameAndDebug(rotorDiskSource, 0);
		addToRunTimeSelectionTable(option, rotorDiskSource, dictionary);
	}

	/*template<> const char* NamedEnum<fv::rotorDiskSource::geometryModeType, 2>::
		names[] =
	{
		"auto",
		"specified"
	};

	const NamedEnum<fv::rotorDiskSource::geometryModeType, 2>
		fv::rotorDiskSource::geometryModeTypeNames_;

	template<> const char* NamedEnum<fv::rotorDiskSource::inletFlowType, 3>::
		names[] =
	{
		"fixed",
		"surfaceNormal",
		"local"
	};

	const NamedEnum<fv::rotorDiskSource::inletFlowType, 3>
		fv::rotorDiskSource::inletFlowTypeNames_;*/
}


// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

void tnbLib::fv::rotorDiskSource::checkData()
{
	// Set inflow type
	switch (selectionMode())
	{
	case smCellSet:
	case smCellZone:
	case smAll:
	{
		// Set the profile ID for each blade section
		profiles_.connectBlades(blade_.profileName(), blade_.profileID());
		switch (inletFlow_)
		{
		case ifFixed:
		{
			coeffs_.lookup("inletVelocity") >> inletVelocity_;
			break;
		}
		case ifSurfaceNormal:
		{
			scalar UIn
			(
				readScalar(coeffs_.lookup("inletNormalVelocity"))
			);
			inletVelocity_ = -coordSys_.R().e3()*UIn;
			break;
		}
		case ifLocal:
		{
			break;
		}
		default:
		{
			FatalErrorInFunction
				<< "Unknown inlet velocity type" << abort(FatalError);
		}
		}


		break;
	}
	default:
	{
		FatalErrorInFunction
			<< "Source cannot be used with '"
			<< selectionModeTypeNames_[selectionMode()]
			<< "' mode.  Please use one of: " << nl
			<< selectionModeTypeNames_[smCellSet] << nl
			<< selectionModeTypeNames_[smCellZone] << nl
			<< selectionModeTypeNames_[smAll]
			<< exit(FatalError);
	}
	}
}


void tnbLib::fv::rotorDiskSource::setFaceArea(vector& axis, const bool correct)
{
	area_ = 0.0;

	static const scalar tol = 0.8;

	const label nInternalFaces = mesh_.nInternalFaces();
	const polyBoundaryMesh& pbm = mesh_.boundaryMesh();
	const vectorField& Sf = mesh_.Sf();
	const scalarField& magSf = mesh_.magSf();

	vector n = Zero;

	// Calculate cell addressing for selected cells
	labelList cellAddr(mesh_.nCells(), -1);
	UIndirectList<label>(cellAddr, cells_) = identity(cells_.size());
	labelList nbrFaceCellAddr(mesh_.nFaces() - nInternalFaces, -1);
	forAll(pbm, patchi)
	{
		const polyPatch& pp = pbm[patchi];

		if (pp.coupled())
		{
			forAll(pp, i)
			{
				label facei = pp.start() + i;
				label nbrFacei = facei - nInternalFaces;
				label own = mesh_.faceOwner()[facei];
				nbrFaceCellAddr[nbrFacei] = cellAddr[own];
			}
		}
	}

	// Correct for parallel running
	syncTools::swapBoundaryFaceList(mesh_, nbrFaceCellAddr);

	// Add internal field contributions
	for (label facei = 0; facei < nInternalFaces; facei++)
	{
		const label own = cellAddr[mesh_.faceOwner()[facei]];
		const label nbr = cellAddr[mesh_.faceNeighbour()[facei]];

		if ((own != -1) && (nbr == -1))
		{
			vector nf = Sf[facei] / magSf[facei];

			if ((nf & axis) > tol)
			{
				area_[own] += magSf[facei];
				n += Sf[facei];
			}
		}
		else if ((own == -1) && (nbr != -1))
		{
			vector nf = Sf[facei] / magSf[facei];

			if ((-nf & axis) > tol)
			{
				area_[nbr] += magSf[facei];
				n -= Sf[facei];
			}
		}
	}


	// Add boundary contributions
	forAll(pbm, patchi)
	{
		const polyPatch& pp = pbm[patchi];
		const vectorField& Sfp = mesh_.Sf().boundaryField()[patchi];
		const scalarField& magSfp = mesh_.magSf().boundaryField()[patchi];

		if (pp.coupled())
		{
			forAll(pp, j)
			{
				const label facei = pp.start() + j;
				const label own = cellAddr[mesh_.faceOwner()[facei]];
				const label nbr = nbrFaceCellAddr[facei - nInternalFaces];
				const vector nf = Sfp[j] / magSfp[j];

				if ((own != -1) && (nbr == -1) && ((nf & axis) > tol))
				{
					area_[own] += magSfp[j];
					n += Sfp[j];
				}
			}
		}
		else
		{
			forAll(pp, j)
			{
				const label facei = pp.start() + j;
				const label own = cellAddr[mesh_.faceOwner()[facei]];
				const vector nf = Sfp[j] / magSfp[j];

				if ((own != -1) && ((nf & axis) > tol))
				{
					area_[own] += magSfp[j];
					n += Sfp[j];
				}
			}
		}
	}

	if (correct)
	{
		reduce(n, sumOp<vector>());
		axis = n / mag(n);
	}

	if (debug)
	{
		volScalarField area
		(
			IOobject
			(
				name_ + ":area",
				mesh_.time().timeName(),
				mesh_,
				IOobject::NO_READ,
				IOobject::NO_WRITE
			),
			mesh_,
			dimensionedScalar(dimArea, 0)
		);
		UIndirectList<scalar>(area.primitiveField(), cells_) = area_;

		Info << type() << ": " << name_ << " writing field " << area.name()
			<< endl;

		area.write();
	}
}


void tnbLib::fv::rotorDiskSource::createCoordinateSystem()
{
	// Construct the local rotor co-prdinate system
	vector origin(Zero);
	vector axis(Zero);
	vector refDir(Zero);

	geometryModeType gm =
		geometryModeTypeNames_.read(coeffs_.lookup("geometryMode"));

	switch (gm)
	{
	case gmAuto:
	{
		// Determine rotation origin (cell volume weighted)
		scalar sumV = 0.0;
		const scalarField& V = mesh_.V();
		const vectorField& C = mesh_.C();
		forAll(cells_, i)
		{
			const label celli = cells_[i];
			sumV += V[celli];
			origin += V[celli] * C[celli];
		}
		reduce(origin, sumOp<vector>());
		reduce(sumV, sumOp<scalar>());
		origin /= sumV;

		// Determine first radial vector
		vector dx1(Zero);
		scalar magR = -great;
		forAll(cells_, i)
		{
			const label celli = cells_[i];
			vector test = C[celli] - origin;
			if (mag(test) > magR)
			{
				dx1 = test;
				magR = mag(test);
			}
		}
		reduce(dx1, maxMagSqrOp<vector>());
		magR = mag(dx1);

		// Determine second radial vector and cross to determine axis
		forAll(cells_, i)
		{
			const label celli = cells_[i];
			vector dx2 = C[celli] - origin;
			if (mag(dx2) > 0.5*magR)
			{
				axis = dx1 ^ dx2;
				if (mag(axis) > small)
				{
					break;
				}
			}
		}
		reduce(axis, maxMagSqrOp<vector>());
		axis /= mag(axis);

		// Correct the axis direction using a point above the rotor
		{
			vector pointAbove(coeffs_.lookup("pointAbove"));
			vector dir = pointAbove - origin;
			dir /= mag(dir);
			if ((dir & axis) < 0)
			{
				axis *= -1.0;
			}
		}

		coeffs_.lookup("refDirection") >> refDir;

		cylindrical_.reset
		(
			new cylindrical
			(
				mesh_,
				axis,
				origin,
				cells_
			)
		);

		// Set the face areas and apply correction to calculated axis
		// e.g. if cellZone is more than a single layer in thickness
		setFaceArea(axis, true);

		break;
	}
	case gmSpecified:
	{
		coeffs_.lookup("origin") >> origin;
		coeffs_.lookup("axis") >> axis;
		coeffs_.lookup("refDirection") >> refDir;

		cylindrical_.reset
		(
			new cylindrical
			(
				mesh_,
				axis,
				origin,
				cells_
			)
		);

		setFaceArea(axis, false);

		break;
	}
	default:
	{
		FatalErrorInFunction
			<< "Unknown geometryMode " << geometryModeTypeNames_[gm]
			<< ". Available geometry modes include "
			<< geometryModeTypeNames_ << exit(FatalError);
	}
	}

	coordSys_ = cylindricalCS("rotorCoordSys", origin, axis, refDir, false);

	const scalar sumArea = gSum(area_);
	const scalar diameter = tnbLib::sqrt(4.0*sumArea / mathematical::pi);
	Info << "    Rotor geometry:" << nl
		<< "    - disk diameter = " << diameter << nl
		<< "    - disk area     = " << sumArea << nl
		<< "    - origin        = " << coordSys_.origin() << nl
		<< "    - r-axis        = " << coordSys_.R().e1() << nl
		<< "    - psi-axis      = " << coordSys_.R().e2() << nl
		<< "    - z-axis        = " << coordSys_.R().e3() << endl;
}


void tnbLib::fv::rotorDiskSource::constructGeometry()
{
	const vectorField& C = mesh_.C();

	forAll(cells_, i)
	{
		if (area_[i] > rootVSmall)
		{
			const label celli = cells_[i];

			// Position in (planar) rotor co-ordinate system
			x_[i] = coordSys_.localPosition(C[celli]);

			// Cache max radius
			rMax_ = max(rMax_, x_[i].x());

			// Swept angle relative to rDir axis [radians] in range 0 -> 2*pi
			scalar psi = x_[i].y();

			// Blade flap angle [radians]
			scalar beta =
				flap_.beta0 - flap_.beta1c*cos(psi) - flap_.beta2s*sin(psi);

			// Determine rotation tensor to convert from planar system into the
			// rotor cone system
			scalar c = cos(beta);
			scalar s = sin(beta);
			R_[i] = tensor(c, 0, -s, 0, 1, 0, s, 0, c);
			invR_[i] = R_[i].T();
		}
	}
}


tnbLib::tmp<tnbLib::vectorField> tnbLib::fv::rotorDiskSource::inflowVelocity
(
	const volVectorField& U
) const
{
	switch (inletFlow_)
	{
	case ifFixed:
	case ifSurfaceNormal:
	{
		return tmp<vectorField>
			(
				new vectorField(mesh_.nCells(), inletVelocity_)
				);

		break;
	}
	case ifLocal:
	{
		return U.primitiveField();

		break;
	}
	default:
	{
		FatalErrorInFunction
			<< "Unknown inlet flow specification" << abort(FatalError);
	}
	}

	return tmp<vectorField>(new vectorField(mesh_.nCells(), Zero));
}


// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

tnbLib::fv::rotorDiskSource::rotorDiskSource
(
	const word& name,
	const word& modelType,
	const dictionary& dict,
	const fvMesh& mesh

)
	:
	cellSetOption(name, modelType, dict, mesh),
	rhoRef_(1.0),
	omega_(0.0),
	nBlades_(0),
	inletFlow_(ifLocal),
	inletVelocity_(Zero),
	tipEffect_(1.0),
	flap_(),
	x_(cells_.size(), Zero),
	R_(cells_.size(), I),
	invR_(cells_.size(), I),
	area_(cells_.size(), 0.0),
	coordSys_(false),
	cylindrical_(),
	rMax_(0.0),
	trim_(trimModel::New(*this, coeffs_)),
	blade_(coeffs_.subDict("blade")),
	profiles_(coeffs_.subDict("profiles"))
{
	read(dict);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::fv::rotorDiskSource::~rotorDiskSource()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::fv::rotorDiskSource::addSup
(
	fvMatrix<vector>& eqn,
	const label fieldi
)
{
	volVectorField force
	(
		IOobject
		(
			name_ + ":rotorForce",
			mesh_.time().timeName(),
			mesh_
		),
		mesh_,
		dimensionedVector
		(
			"zero",
			eqn.dimensions() / dimVolume,
			Zero
		)
	);

	// Read the reference density for incompressible flow
	coeffs_.lookup("rhoRef") >> rhoRef_;

	const vectorField Uin(inflowVelocity(eqn.psi()));
	trim_->correct(Uin, force);
	calculate(geometricOneField(), Uin, trim_->thetag(), force);

	// Add source to rhs of eqn
	eqn -= force;

	if (mesh_.time().writeTime())
	{
		force.write();
	}
}


void tnbLib::fv::rotorDiskSource::addSup
(
	const volScalarField& rho,
	fvMatrix<vector>& eqn,
	const label fieldi
)
{
	volVectorField force
	(
		IOobject
		(
			name_ + ":rotorForce",
			mesh_.time().timeName(),
			mesh_
		),
		mesh_,
		dimensionedVector
		(
			"zero",
			eqn.dimensions() / dimVolume,
			Zero
		)
	);

	const vectorField Uin(inflowVelocity(eqn.psi()));
	trim_->correct(rho, Uin, force);
	calculate(rho, Uin, trim_->thetag(), force);

	// Add source to rhs of eqn
	eqn -= force;

	if (mesh_.time().writeTime())
	{
		force.write();
	}
}


bool tnbLib::fv::rotorDiskSource::read(const dictionary& dict)
{
	if (cellSetOption::read(dict))
	{
		coeffs_.lookup("fields") >> fieldNames_;
		applied_.setSize(fieldNames_.size(), false);

		// Read co-ordinate system/geometry invariant properties
		scalar rpm(readScalar(coeffs_.lookup("rpm")));
		omega_ = rpm / 60.0*mathematical::twoPi;

		coeffs_.lookup("nBlades") >> nBlades_;

		inletFlow_ = inletFlowTypeNames_.read(coeffs_.lookup("inletFlowType"));

		coeffs_.lookup("tipEffect") >> tipEffect_;

		const dictionary& flapCoeffs(coeffs_.subDict("flapCoeffs"));
		flapCoeffs.lookup("beta0") >> flap_.beta0;
		flapCoeffs.lookup("beta1c") >> flap_.beta1c;
		flapCoeffs.lookup("beta2s") >> flap_.beta2s;
		flap_.beta0 = degToRad(flap_.beta0);
		flap_.beta1c = degToRad(flap_.beta1c);
		flap_.beta2s = degToRad(flap_.beta2s);


		// Create co-ordinate system
		createCoordinateSystem();

		// Read co-odinate system dependent properties
		checkData();

		constructGeometry();

		trim_->read(coeffs_);

		if (debug)
		{
			writeField("thetag", trim_->thetag()(), true);
			writeField("faceArea", area_, true);
		}

		return true;
	}
	else
	{
		return false;
	}
}


// ************************************************************************* //