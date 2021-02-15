#include <waveVelocityFvPatchVectorField.hxx>

#include <wavePressureFvPatchScalarField.hxx>
#include <addToRunTimeSelectionTable.hxx>
#include <levelSet.hxx>
#include <volFields.hxx>
#include <fvMeshSubset.hxx>
#include <symmTensor.hxx>  // added by amir

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::waveVelocityFvPatchVectorField::waveVelocityFvPatchVectorField
(
	const fvPatch& p,
	const DimensionedField<vector, volMesh>& iF
)
	:
	directionMixedFvPatchVectorField(p, iF),
	phiName_("phi"),
	pName_("p"),
	inletOutlet_(true),
	faceCellSubset_(nullptr),
	faceCellSubsetTimeIndex_(-1)
{
	refValue() = Zero;
	refGrad() = Zero;
	valueFraction() = Zero;
}


tnbLib::waveVelocityFvPatchVectorField::waveVelocityFvPatchVectorField
(
	const fvPatch& p,
	const DimensionedField<vector, volMesh>& iF,
	const dictionary& dict
)
	:
	directionMixedFvPatchVectorField(p, iF),
	phiName_(dict.lookupOrDefault<word>("phi", "phi")),
	pName_(dict.lookupOrDefault<word>("p", "p")),
	inletOutlet_(dict.lookupOrDefault<Switch>("inletOutlet", true)),
	faceCellSubset_(nullptr),
	faceCellSubsetTimeIndex_(-1)
{
	if (dict.found("value"))
	{
		fvPatchVectorField::operator=(vectorField("value", dict, p.size()));
	}
	else
	{
		fvPatchVectorField::operator=(patchInternalField());
	}

	refValue() = *this;
	refGrad() = Zero;
	valueFraction() = Zero;
}


tnbLib::waveVelocityFvPatchVectorField::waveVelocityFvPatchVectorField
(
	const waveVelocityFvPatchVectorField& ptf,
	const fvPatch& p,
	const DimensionedField<vector, volMesh>& iF,
	const fvPatchFieldMapper& mapper
)
	:
	directionMixedFvPatchVectorField(ptf, p, iF, mapper),
	phiName_(ptf.phiName_),
	pName_(ptf.pName_),
	inletOutlet_(ptf.inletOutlet_),
	faceCellSubset_(nullptr),
	faceCellSubsetTimeIndex_(-1)
{}


tnbLib::waveVelocityFvPatchVectorField::waveVelocityFvPatchVectorField
(
	const waveVelocityFvPatchVectorField& ptf
)
	:
	directionMixedFvPatchVectorField(ptf),
	phiName_(ptf.phiName_),
	pName_(ptf.pName_),
	inletOutlet_(ptf.inletOutlet_),
	faceCellSubset_(nullptr),
	faceCellSubsetTimeIndex_(-1)
{}


tnbLib::waveVelocityFvPatchVectorField::waveVelocityFvPatchVectorField
(
	const waveVelocityFvPatchVectorField& ptf,
	const DimensionedField<vector, volMesh>& iF
)
	:
	directionMixedFvPatchVectorField(ptf, iF),
	phiName_(ptf.phiName_),
	pName_(ptf.pName_),
	inletOutlet_(ptf.inletOutlet_),
	faceCellSubset_(nullptr),
	faceCellSubsetTimeIndex_(-1)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

const tnbLib::fvMeshSubset&
tnbLib::waveVelocityFvPatchVectorField::faceCellSubset() const
{
	const fvMesh& mesh = patch().boundaryMesh().mesh();
	const label timeIndex = mesh.time().timeIndex();

	if
		(
			!faceCellSubset_.valid()
			|| (mesh.changing() && faceCellSubsetTimeIndex_ != timeIndex)
			)
	{
		faceCellSubset_.reset(new fvMeshSubset(mesh));
		faceCellSubset_->setCellSubset(patch().faceCells());
		faceCellSubsetTimeIndex_ = timeIndex;

		// Ask for the tetBasePtIs to trigger all processors to build them.
		// Without this, processors that do not contain this patch will
		// generate a comms mismatch.
		faceCellSubset_->subMesh().tetBasePtIs();
	}

	return faceCellSubset_();
}


tnbLib::tmp<tnbLib::vectorField> tnbLib::waveVelocityFvPatchVectorField::U() const
{
	const scalar t = db().time().timeOutputValue();
	const waveSuperposition& waves = waveSuperposition::New(db());

	return
		levelSetAverage
		(
			patch(),
			waves.height(t, patch().Cf()),
			waves.height(t, patch().patch().localPoints()),
			waves.UGas(t, patch().Cf())(),
			waves.UGas(t, patch().patch().localPoints())(),
			waves.ULiquid(t, patch().Cf())(),
			waves.ULiquid(t, patch().patch().localPoints())()
		);
}


tnbLib::tmp<tnbLib::vectorField> tnbLib::waveVelocityFvPatchVectorField::Un() const
{
	const scalar t = db().time().timeOutputValue();
	const waveSuperposition& waves = waveSuperposition::New(db());

	const fvMeshSubset& subset = faceCellSubset();
	const fvMesh& meshs = subset.subMesh();
	const label patchis = findIndex(subset.patchMap(), patch().index());

	const vectorField Us
	(
		levelSetAverage
		(
			meshs,
			waves.height(t, meshs.cellCentres())(),
			waves.height(t, meshs.points())(),
			waves.UGas(t, meshs.cellCentres())(),
			waves.UGas(t, meshs.points())(),
			waves.ULiquid(t, meshs.cellCentres())(),
			waves.ULiquid(t, meshs.points())()
		)
	);

	tmp<vectorField> tResult(new vectorField(patch().size()));
	vectorField& result = tResult.ref();

	if (patchis != -1)
	{
		forAll(meshs.boundary()[patchis], is)
		{
			const label fs = is + meshs.boundary()[patchis].patch().start();
			const label cs = meshs.boundary()[patchis].faceCells()[is];
			const label f = subset.faceMap()[fs];
			const label i = patch().patch().whichFace(f);
			result[i] = Us[cs];
		}
	}

	return tResult;
}


void tnbLib::waveVelocityFvPatchVectorField::updateCoeffs()
{
	if (updated())
	{
		return;
	}

	const fvPatchScalarField& pp =
		patch().lookupPatchField<volScalarField, scalar>(pName_);

	if (isA<wavePressureFvPatchScalarField>(pp))
	{
		const vectorField U(this->U()), Un(this->Un());
		const scalarField out(pos0(U & patch().Sf()));

		// Where inflow, set all velocity components to values specified by the
		// wave model. Where outflow, set the tangential values and the normal
		// gradient.
		valueFraction() = symmTensor::I - out * sqr(patch().nf());
		refValue() = U;
		refGrad() = (U - Un)*patch().deltaCoeffs();
	}
	else
	{
		const vectorField U(this->U());

		if (inletOutlet_)
		{
			const scalarField& phip =
				patch().lookupPatchField<surfaceScalarField, scalar>(phiName_);
			const scalarField out(pos0(phip));

			// Where inflow, fix all velocity components to values specified by
			// the wave model.
			refValue() = (1 - out)*U;
			valueFraction() = (1 - out)*symmTensor::I;

			// Where outflow, set the normal component of the velocity to a
			// value consistent with phi, but scale it to get the volumetric
			// flow rate specified by the wave model. Tangential components are
			// extrapolated.
			const scalar QPhip = gSum(out*phip);
			const scalar QWave = gSum(out*(U & patch().Sf()));
			const vectorField nBySf(patch().Sf() / sqr(patch().magSf()));
			if (QPhip > vSmall)
			{
				refValue() += out * (QWave / QPhip)*phip*nBySf;
			}
			else
			{
				refValue() += out * QWave*nBySf;
			}
			valueFraction() += out * sqr(patch().nf());
		}
		else
		{
			refValue() = U;
			valueFraction() = symmTensor::I;
		}
	}

	directionMixedFvPatchVectorField::updateCoeffs();
	directionMixedFvPatchVectorField::evaluate();
}


void tnbLib::waveVelocityFvPatchVectorField::write
(
	Ostream& os
) const
{
	directionMixedFvPatchVectorField::write(os);
	writeEntryIfDifferent<word>(os, "phi", "phi", phiName_);
	writeEntryIfDifferent<word>(os, "p", "p", pName_);
	writeEntryIfDifferent<Switch>(os, "inletOutlet", true, inletOutlet_);
}

#include <Istream.hxx>

// * * * * * * * * * * * * * * Build Macro Function  * * * * * * * * * * * * //

namespace tnbLib
{
	makePatchTypeField
	(
		fvPatchVectorField,
		waveVelocityFvPatchVectorField
	);
}

// ************************************************************************* //