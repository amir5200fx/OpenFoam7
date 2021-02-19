#include <meanVelocityForce.hxx>

#include <fvMatrices.hxx>
#include <DimensionedField.hxx>
#include <IFstream.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * Static Member Functions * * * * * * * * * * * * //

namespace tnbLib
{
	namespace fv
	{
		defineTypeNameAndDebug(meanVelocityForce, 0);

		addToRunTimeSelectionTable
		(
			option,
			meanVelocityForce,
			dictionary
		);
	}
}


// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

void tnbLib::fv::meanVelocityForce::writeProps
(
	const scalar gradP
) const
{
	// Only write on output time
	if (mesh_.time().writeTime())
	{
		IOdictionary propsDict
		(
			IOobject
			(
				name_ + "Properties",
				mesh_.time().timeName(),
				"uniform",
				mesh_,
				IOobject::NO_READ,
				IOobject::NO_WRITE
			)
		);
		propsDict.add("gradient", gradP);
		propsDict.regIOobject::write();
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::fv::meanVelocityForce::meanVelocityForce
(
	const word& sourceName,
	const word& modelType,
	const dictionary& dict,
	const fvMesh& mesh
)
	:
	cellSetOption(sourceName, modelType, dict, mesh),
	Ubar_(coeffs_.lookup("Ubar")),
	gradP0_(0.0),
	dGradP_(0.0),
	flowDir_(Ubar_ / mag(Ubar_)),
	relaxation_(coeffs_.lookupOrDefault<scalar>("relaxation", 1.0)),
	rAPtr_(nullptr)
{
	coeffs_.lookup("fields") >> fieldNames_;

	if (fieldNames_.size() != 1)
	{
		FatalErrorInFunction
			<< "settings are:" << fieldNames_ << exit(FatalError);
	}

	applied_.setSize(fieldNames_.size(), false);

	// Read the initial pressure gradient from file if it exists
	IFstream propsFile
	(
		mesh_.time().timePath() / "uniform" / (name_ + "Properties")
	);

	if (propsFile.good())
	{
		Info << "    Reading pressure gradient from file" << endl;
		dictionary propsDict(dictionary::null, propsFile);
		propsDict.lookup("gradient") >> gradP0_;
	}

	Info << "    Initial pressure gradient = " << gradP0_ << nl << endl;
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::scalar tnbLib::fv::meanVelocityForce::magUbarAve
(
	const volVectorField& U
) const
{
	scalar magUbarAve = 0.0;

	const scalarField& cv = mesh_.V();
	forAll(cells_, i)
	{
		label celli = cells_[i];
		scalar volCell = cv[celli];
		magUbarAve += (flowDir_ & U[celli])*volCell;
	}

	reduce(magUbarAve, sumOp<scalar>());

	magUbarAve /= V_;

	return magUbarAve;
}


void tnbLib::fv::meanVelocityForce::correct(volVectorField& U)
{
	const scalarField& rAU = rAPtr_();

	// Integrate flow variables over cell set
	scalar rAUave = 0.0;
	const scalarField& cv = mesh_.V();
	forAll(cells_, i)
	{
		label celli = cells_[i];
		scalar volCell = cv[celli];
		rAUave += rAU[celli] * volCell;
	}

	// Collect across all processors
	reduce(rAUave, sumOp<scalar>());

	// Volume averages
	rAUave /= V_;

	scalar magUbarAve = this->magUbarAve(U);

	// Calculate the pressure gradient increment needed to adjust the average
	// flow-rate to the desired value
	dGradP_ = relaxation_ * (mag(Ubar_) - magUbarAve) / rAUave;

	// Apply correction to velocity field
	forAll(cells_, i)
	{
		label celli = cells_[i];
		U[celli] += flowDir_ * rAU[celli] * dGradP_;
	}

	scalar gradP = gradP0_ + dGradP_;

	Info << "Pressure gradient source: uncorrected Ubar = " << magUbarAve
		<< ", pressure gradient = " << gradP << endl;

	writeProps(gradP);
}


void tnbLib::fv::meanVelocityForce::addSup
(
	fvMatrix<vector>& eqn,
	const label fieldi
)
{
	volVectorField::Internal Su
	(
		IOobject
		(
			name_ + fieldNames_[fieldi] + "Sup",
			mesh_.time().timeName(),
			mesh_,
			IOobject::NO_READ,
			IOobject::NO_WRITE
		),
		mesh_,
		dimensionedVector(eqn.dimensions() / dimVolume, Zero)
	);

	scalar gradP = gradP0_ + dGradP_;

	UIndirectList<vector>(Su, cells_) = flowDir_ * gradP;

	eqn += Su;
}


void tnbLib::fv::meanVelocityForce::addSup
(
	const volScalarField& rho,
	fvMatrix<vector>& eqn,
	const label fieldi
)
{
	this->addSup(eqn, fieldi);
}


void tnbLib::fv::meanVelocityForce::constrain
(
	fvMatrix<vector>& eqn,
	const label
)
{
	if (rAPtr_.empty())
	{
		rAPtr_.reset
		(
			new volScalarField
			(
				IOobject
				(
					name_ + ":rA",
					mesh_.time().timeName(),
					mesh_,
					IOobject::NO_READ,
					IOobject::NO_WRITE,
					false
				),
				1.0 / eqn.A()
			)
		);
	}
	else
	{
		rAPtr_() = 1.0 / eqn.A();
	}

	gradP0_ += dGradP_;
	dGradP_ = 0.0;
}


// ************************************************************************* //