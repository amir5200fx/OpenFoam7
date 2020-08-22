#include <angularOscillatingVelocityPointPatchVectorField.hxx>

#include <pointPatchFields.hxx>
#include <addToRunTimeSelectionTable.hxx>
#include <Time.hxx>
#include <polyMesh.hxx>

#include <pointPatchFieldMapper.hxx>  // added by amir
#include <pointMesh.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	angularOscillatingVelocityPointPatchVectorField::
		angularOscillatingVelocityPointPatchVectorField
		(
			const pointPatch& p,
			const DimensionedField<vector, pointMesh>& iF
		)
		:
		fixedValuePointPatchField<vector>(p, iF),
		axis_(Zero),
		origin_(Zero),
		angle0_(0.0),
		amplitude_(0.0),
		omega_(0.0),
		p0_(p.localPoints())
	{}


	angularOscillatingVelocityPointPatchVectorField::
		angularOscillatingVelocityPointPatchVectorField
		(
			const pointPatch& p,
			const DimensionedField<vector, pointMesh>& iF,
			const dictionary& dict
		)
		:
		fixedValuePointPatchField<vector>(p, iF, dict),
		axis_(dict.lookup("axis")),
		origin_(dict.lookup("origin")),
		angle0_(readScalar(dict.lookup("angle0"))),
		amplitude_(readScalar(dict.lookup("amplitude"))),
		omega_(readScalar(dict.lookup("omega")))
	{
		if (!dict.found("value"))
		{
			updateCoeffs();
		}

		if (dict.found("p0"))
		{
			p0_ = vectorField("p0", dict, p.size());
		}
		else
		{
			p0_ = p.localPoints();
		}
	}


	angularOscillatingVelocityPointPatchVectorField::
		angularOscillatingVelocityPointPatchVectorField
		(
			const angularOscillatingVelocityPointPatchVectorField& ptf,
			const pointPatch& p,
			const DimensionedField<vector, pointMesh>& iF,
			const pointPatchFieldMapper& mapper
		)
		:
		fixedValuePointPatchField<vector>(ptf, p, iF, mapper),
		axis_(ptf.axis_),
		origin_(ptf.origin_),
		angle0_(ptf.angle0_),
		amplitude_(ptf.amplitude_),
		omega_(ptf.omega_),
		p0_(ptf.p0_)
	{}


	angularOscillatingVelocityPointPatchVectorField::
		angularOscillatingVelocityPointPatchVectorField
		(
			const angularOscillatingVelocityPointPatchVectorField& ptf,
			const DimensionedField<vector, pointMesh>& iF
		)
		:
		fixedValuePointPatchField<vector>(ptf, iF),
		axis_(ptf.axis_),
		origin_(ptf.origin_),
		angle0_(ptf.angle0_),
		amplitude_(ptf.amplitude_),
		omega_(ptf.omega_),
		p0_(ptf.p0_)
	{}


	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	void angularOscillatingVelocityPointPatchVectorField::autoMap
	(
		const pointPatchFieldMapper& m
	)
	{
		fixedValuePointPatchField<vector>::autoMap(m);

		m(p0_, p0_);
	}


	void angularOscillatingVelocityPointPatchVectorField::rmap
	(
		const pointPatchField<vector>& ptf,
		const labelList& addr
	)
	{
		const angularOscillatingVelocityPointPatchVectorField& aOVptf =
			refCast<const angularOscillatingVelocityPointPatchVectorField>(ptf);

		fixedValuePointPatchField<vector>::rmap(aOVptf, addr);

		p0_.rmap(aOVptf.p0_, addr);
	}


	void angularOscillatingVelocityPointPatchVectorField::updateCoeffs()
	{
		if (this->updated())
		{
			return;
		}

		const polyMesh& mesh = this->internalField().mesh()();
		const Time& t = mesh.time();
		const pointPatch& p = this->patch();

		scalar angle = angle0_ + amplitude_ * sin(omega_*t.value());
		vector axisHat = axis_ / mag(axis_);
		vectorField p0Rel(p0_ - origin_);

		vectorField::operator=
			(
			(
				p0_
				+ p0Rel * (cos(angle) - 1)
				+ (axisHat ^ p0Rel*sin(angle))
				+ (axisHat & p0Rel)*(1 - cos(angle))*axisHat
				- p.localPoints()
				) / t.deltaTValue()
				);

		fixedValuePointPatchField<vector>::updateCoeffs();
	}


	void angularOscillatingVelocityPointPatchVectorField::write
	(
		Ostream& os
	) const
	{
		pointPatchField<vector>::write(os);
		writeEntry(os, "axis", axis_);
		writeEntry(os, "origin", origin_);
		writeEntry(os, "angle0", angle0_);
		writeEntry(os, "amplitude", amplitude_);
		writeEntry(os, "omega", omega_);
		writeEntry(os, "p0", p0_);
		writeEntry(os, "value", *this);
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	makePointPatchTypeField
	(
		pointPatchVectorField,
		angularOscillatingVelocityPointPatchVectorField
	);

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //