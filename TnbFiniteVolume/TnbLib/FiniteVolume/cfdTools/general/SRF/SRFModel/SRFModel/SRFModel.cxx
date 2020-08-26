#include <SRFModel.hxx>

#include <SRFVelocityFvPatchVectorField.hxx>
#include <Time.hxx>  // added by amir

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace SRF
	{
		defineTypeNameAndDebug(SRFModel, 0);
		defineRunTimeSelectionTable(SRFModel, dictionary);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::SRF::SRFModel::SRFModel
(
	const word& type,
	const volVectorField& Urel
)
	:
	IOdictionary
	(
		IOobject
		(
			"SRFProperties",
			Urel.time().constant(),
			Urel.db(),
			IOobject::MUST_READ_IF_MODIFIED,
			IOobject::NO_WRITE
		)
	),
	Urel_(Urel),
	mesh_(Urel_.mesh()),
	origin_("origin", dimLength, lookup("origin")),
	axis_(lookup("axis")),
	SRFModelCoeffs_(optionalSubDict(type + "Coeffs")),
	omega_(dimensionedVector("omega", dimless / dimTime, Zero))
{
	// Normalise the axis
	axis_ /= mag(axis_);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::SRF::SRFModel::~SRFModel()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::SRF::SRFModel::read()
{
	if (regIOobject::read())
	{
		// Re-read origin
		lookup("origin") >> origin_;

		// Re-read axis
		lookup("axis") >> axis_;
		axis_ /= mag(axis_);

		// Re-read sub-model coeffs
		SRFModelCoeffs_ = optionalSubDict(type() + "Coeffs");

		return true;
	}
	else
	{
		return false;
	}
}


const tnbLib::dimensionedVector& tnbLib::SRF::SRFModel::origin() const
{
	return origin_;
}


const tnbLib::vector& tnbLib::SRF::SRFModel::axis() const
{
	return axis_;
}


const tnbLib::dimensionedVector& tnbLib::SRF::SRFModel::omega() const
{
	return omega_;
}


tnbLib::tmp<tnbLib::DimensionedField<tnbLib::vector, tnbLib::volMesh>>
tnbLib::SRF::SRFModel::Fcoriolis() const
{
	return volVectorField::Internal::New
	(
		"Fcoriolis",
		2.0*omega_ ^ Urel_
	);
}


tnbLib::tmp<tnbLib::DimensionedField<tnbLib::vector, tnbLib::volMesh>>
tnbLib::SRF::SRFModel::Fcentrifugal() const
{
	return volVectorField::Internal::New
	(
		"Fcentrifugal",
		omega_ ^ (omega_ ^ (mesh_.C() - origin_))
	);
}


tnbLib::tmp<tnbLib::DimensionedField<tnbLib::vector, tnbLib::volMesh>>
tnbLib::SRF::SRFModel::Su() const
{
	return Fcoriolis() + Fcentrifugal();
}


tnbLib::vectorField tnbLib::SRF::SRFModel::velocity
(
	const vectorField& positions
) const
{
	tmp<vectorField> tfld =
		omega_.value()
		^ (
		(positions - origin_.value())
			- axis_ * (axis_ & (positions - origin_.value()))
			);

	return tfld();
}


tnbLib::tmp<tnbLib::volVectorField> tnbLib::SRF::SRFModel::U() const
{
	return volVectorField::New
	(
		"Usrf",
		omega_ ^ ((mesh_.C() - origin_) - axis_ * (axis_ & (mesh_.C() - origin_)))
	);
}


tnbLib::tmp<tnbLib::volVectorField> tnbLib::SRF::SRFModel::Uabs() const
{
	tmp<volVectorField> Usrf = U();

	tmp<volVectorField> tUabs
	(
		volVectorField::New("Uabs", Usrf)
	);

	volVectorField& Uabs = tUabs.ref();

	// Add SRF contribution to internal field
	Uabs.primitiveFieldRef() += Urel_.primitiveField();

	// Add Urel boundary contributions
	volVectorField::Boundary& Uabsbf = Uabs.boundaryFieldRef();
	const volVectorField::Boundary& bvf = Urel_.boundaryField();

	forAll(bvf, i)
	{
		if (isA<SRFVelocityFvPatchVectorField>(bvf[i]))
		{
			// Only include relative contributions from
			// SRFVelocityFvPatchVectorField's
			const SRFVelocityFvPatchVectorField& UrelPatch =
				refCast<const SRFVelocityFvPatchVectorField>(bvf[i]);
			if (UrelPatch.relative())
			{
				Uabsbf[i] += Urel_.boundaryField()[i];
			}
		}
		else
		{
			Uabsbf[i] += Urel_.boundaryField()[i];
		}
	}

	return tUabs;
}


// ************************************************************************* //