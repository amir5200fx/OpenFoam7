#pragma once
#include <volFields.hxx>
#include <unitConversion.hxx>

using namespace tnbLib::constant;

// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

template<class RhoFieldType>
void tnbLib::fv::rotorDiskSource::calculate
(
	const RhoFieldType& rho,
	const vectorField& U,
	const scalarField& thetag,
	vectorField& force,
	const bool divideVolume,
	const bool output
) const
{
	const scalarField& V = mesh_.V();

	// Logging info
	scalar dragEff = 0;
	scalar liftEff = 0;
	scalar AOAmin = great;
	scalar AOAmax = -great;
	scalar powerEff = 0;

	forAll(cells_, i)
	{
		if (area_[i] > rootVSmall)
		{
			const label celli = cells_[i];

			const scalar radius = x_[i].x();

			// Transform velocity into local cylindrical reference frame
			vector Uc = cylindrical_->invTransform(U[celli], i);
			// Uc.x(): radial direction.
			// Uc.y(): drag direction.
			// Uc.z(): lift / thrust direction.

			// Transform velocity into local coning system
			Uc = R_[i] & Uc;

			// Set radial component of velocity to zero
			Uc.x() = 0;

			// Set blade normal component of velocity
			Uc.y() = radius * omega_ - Uc.y();

			// Determine blade data for this radius
			// i2 = index of upper radius bound data point in blade list
			scalar twist = 0;
			scalar chord = 0;
			label i1 = -1;
			label i2 = -1;
			scalar invDr = 0;
			blade_.interpolate(radius, twist, chord, i1, i2, invDr);

			const scalar alphaGeom = thetag[i] + twist;

			// Effective angle of attack
			const int rotationSign = sign(omega_);
			const scalar alphaEff =
				alphaGeom - atan2(-Uc.z(), rotationSign*Uc.y());

			AOAmin = min(AOAmin, alphaEff);
			AOAmax = max(AOAmax, alphaEff);

			// Determine profile data for this radius and angle of attack
			const label profile1 = blade_.profileID()[i1];
			const label profile2 = blade_.profileID()[i2];

			scalar Cd1 = 0;
			scalar Cl1 = 0;
			profiles_[profile1].Cdl(alphaEff, Cd1, Cl1);

			scalar Cd2 = 0;
			scalar Cl2 = 0;
			profiles_[profile2].Cdl(alphaEff, Cd2, Cl2);

			const scalar Cd = invDr * (Cd2 - Cd1) + Cd1;
			const scalar Cl = invDr * (Cl2 - Cl1) + Cl1;

			// Apply tip effect for blade lift
			const scalar tipFactor = neg(radius / rMax_ - tipEffect_);

			// Calculate forces perpendicular to blade
			const scalar pDyn = 0.5*rho[celli] * magSqr(Uc);

			const scalar f =
				pDyn * chord*nBlades_*area_[i] / radius / mathematical::twoPi;

			vector localForce = vector(0, rotationSign*-f * Cd, tipFactor*f*Cl);

			// Accumulate forces
			dragEff += rhoRef_ * localForce.y();
			liftEff += rhoRef_ * localForce.z();
			powerEff += rhoRef_ * localForce.y()*radius*omega_;

			// Transform force from local coning system into rotor cylindrical
			localForce = invR_[i] & localForce;

			// Transform force into global Cartesian co-ordinate system
			force[celli] = cylindrical_->transform(localForce, i);

			if (divideVolume)
			{
				force[celli] /= V[celli];
			}
		}
	}

	if (output)
	{
		reduce(AOAmin, minOp<scalar>());
		reduce(AOAmax, maxOp<scalar>());
		reduce(dragEff, sumOp<scalar>());
		reduce(liftEff, sumOp<scalar>());

		Info << type() << " output:" << nl
			<< "    min/max(AOA)   = " << radToDeg(AOAmin) << ", "
			<< radToDeg(AOAmax) << nl
			<< "    Effective power = " << powerEff << nl
			<< "    Effective drag = " << dragEff << nl
			<< "    Effective lift = " << liftEff << endl;
	}
}


template<class Type>
void tnbLib::fv::rotorDiskSource::writeField
(
	const word& name,
	const List<Type>& values,
	const bool writeNow
) const
{
	typedef GeometricField<Type, fvPatchField, volMesh> fieldType;

	if (mesh_.time().writeTime() || writeNow)
	{
		tmp<fieldType> tfield
		(
			new fieldType
			(
				IOobject
				(
					name,
					mesh_.time().timeName(),
					mesh_,
					IOobject::NO_READ,
					IOobject::NO_WRITE
				),
				mesh_,
				dimensioned<Type>("zero", dimless, Zero)
			)
		);

		Field<Type>& field = tfield.ref().primitiveFieldRef();

		if (cells_.size() != values.size())
		{
			FatalErrorInFunction << abort(FatalError);
		}

		forAll(cells_, i)
		{
			const label celli = cells_[i];
			field[celli] = values[i];
		}

		tfield().write();
	}
}


// ************************************************************************* //