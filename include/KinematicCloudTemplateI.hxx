#pragma once
#include <fvmSup.hxx>
#include <SortableList.hxx>

#include <PstreamReduceOps.hxx>  // added by amir
#include <extrapolatedCalculatedFvPatchFields.hxx>  // added by amir

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CloudType>
inline const tnbLib::KinematicCloud<CloudType>&
tnbLib::KinematicCloud<CloudType>::cloudCopy() const
{
	return cloudCopyPtr_();
}


template<class CloudType>
inline const tnbLib::fvMesh& tnbLib::KinematicCloud<CloudType>::mesh() const
{
	return mesh_;
}


template<class CloudType>
inline const tnbLib::IOdictionary&
tnbLib::KinematicCloud<CloudType>::particleProperties() const
{
	return particleProperties_;
}


template<class CloudType>
inline const tnbLib::IOdictionary&
tnbLib::KinematicCloud<CloudType>::outputProperties() const
{
	return outputProperties_;
}


template<class CloudType>
inline tnbLib::IOdictionary& tnbLib::KinematicCloud<CloudType>::outputProperties()
{
	return outputProperties_;
}


template<class CloudType>
inline const tnbLib::cloudSolution&
tnbLib::KinematicCloud<CloudType>::solution() const
{
	return solution_;
}


template<class CloudType>
inline tnbLib::cloudSolution& tnbLib::KinematicCloud<CloudType>::solution()
{
	return solution_;
}


template<class CloudType>
inline const typename CloudType::particleType::constantProperties&
tnbLib::KinematicCloud<CloudType>::constProps() const
{
	return constProps_;
}


template<class CloudType>
inline typename CloudType::particleType::constantProperties&
tnbLib::KinematicCloud<CloudType>::constProps()
{
	return constProps_;
}


template<class CloudType>
inline const tnbLib::dictionary&
tnbLib::KinematicCloud<CloudType>::subModelProperties() const
{
	return subModelProperties_;
}


template<class CloudType>
inline const tnbLib::volScalarField& tnbLib::KinematicCloud<CloudType>::rho() const
{
	return rho_;
}


template<class CloudType>
inline const tnbLib::volVectorField& tnbLib::KinematicCloud<CloudType>::U() const
{
	return U_;
}


template<class CloudType>
inline const tnbLib::volScalarField& tnbLib::KinematicCloud<CloudType>::mu() const
{
	return mu_;
}


template<class CloudType>
inline const tnbLib::dimensionedVector& tnbLib::KinematicCloud<CloudType>::g() const
{
	return g_;
}


template<class CloudType>
inline tnbLib::scalar tnbLib::KinematicCloud<CloudType>::pAmbient() const
{
	return pAmbient_;
}


template<class CloudType>
inline tnbLib::scalar& tnbLib::KinematicCloud<CloudType>::pAmbient()
{
	return pAmbient_;
}


template<class CloudType>
//inline const typename CloudType::parcelType::forceType&
inline const typename tnbLib::KinematicCloud<CloudType>::forceType&
tnbLib::KinematicCloud<CloudType>::forces() const
{
	return forces_;
}


template<class CloudType>
inline typename tnbLib::KinematicCloud<CloudType>::forceType&
tnbLib::KinematicCloud<CloudType>::forces()
{
	return forces_;
}


template<class CloudType>
inline typename tnbLib::KinematicCloud<CloudType>::functionType&
tnbLib::KinematicCloud<CloudType>::functions()
{
	return functions_;
}


template<class CloudType>
inline const tnbLib::InjectionModelList<tnbLib::KinematicCloud<CloudType>>&
tnbLib::KinematicCloud<CloudType>::injectors() const
{
	return injectors_;
}


template<class CloudType>
inline tnbLib::InjectionModelList<tnbLib::KinematicCloud<CloudType>>&
tnbLib::KinematicCloud<CloudType>::injectors()
{
	return injectors_;
}


template<class CloudType>
inline const tnbLib::DispersionModel<tnbLib::KinematicCloud<CloudType>>&
tnbLib::KinematicCloud<CloudType>::dispersion() const
{
	return dispersionModel_;
}


template<class CloudType>
inline tnbLib::DispersionModel<tnbLib::KinematicCloud<CloudType>>&
tnbLib::KinematicCloud<CloudType>::dispersion()
{
	return dispersionModel_();
}


template<class CloudType>
inline const tnbLib::PatchInteractionModel<tnbLib::KinematicCloud<CloudType>>&
tnbLib::KinematicCloud<CloudType>::patchInteraction() const
{
	return patchInteractionModel_;
}


template<class CloudType>
inline tnbLib::PatchInteractionModel<tnbLib::KinematicCloud<CloudType>>&
tnbLib::KinematicCloud<CloudType>::patchInteraction()
{
	return patchInteractionModel_();
}


template<class CloudType>
inline const tnbLib::StochasticCollisionModel<tnbLib::KinematicCloud<CloudType>>&
tnbLib::KinematicCloud<CloudType>::stochasticCollision() const
{
	return stochasticCollisionModel_();
}


template<class CloudType>
inline tnbLib::StochasticCollisionModel<tnbLib::KinematicCloud<CloudType>>&
tnbLib::KinematicCloud<CloudType>::stochasticCollision()
{
	return stochasticCollisionModel_();
}


template<class CloudType>
inline const tnbLib::SurfaceFilmModel<tnbLib::KinematicCloud<CloudType>>&
tnbLib::KinematicCloud<CloudType>::surfaceFilm() const
{
	return surfaceFilmModel_();
}


template<class CloudType>
inline tnbLib::SurfaceFilmModel<tnbLib::KinematicCloud<CloudType>>&
tnbLib::KinematicCloud<CloudType>::surfaceFilm()
{
	return surfaceFilmModel_();
}


template<class CloudType>
inline const tnbLib::integrationScheme&
tnbLib::KinematicCloud<CloudType>::UIntegrator() const
{
	return UIntegrator_;
}


template<class CloudType>
inline tnbLib::label tnbLib::KinematicCloud<CloudType>::nParcels() const
{
	return this->size();
}


template<class CloudType>
inline tnbLib::scalar tnbLib::KinematicCloud<CloudType>::massInSystem() const
{
	scalar sysMass = 0.0;
	forAllConstIter(typename KinematicCloud<CloudType>, *this, iter)
	{
		const parcelType& p = iter();
		sysMass += p.nParticle()*p.mass();
	}

	return sysMass;
}


template<class CloudType>
inline tnbLib::vector
tnbLib::KinematicCloud<CloudType>::linearMomentumOfSystem() const
{
	vector linearMomentum(Zero);

	forAllConstIter(typename KinematicCloud<CloudType>, *this, iter)
	{
		const parcelType& p = iter();

		linearMomentum += p.nParticle()*p.mass()*p.U();
	}

	return linearMomentum;
}


template<class CloudType>
inline tnbLib::scalar
tnbLib::KinematicCloud<CloudType>::linearKineticEnergyOfSystem() const
{
	scalar linearKineticEnergy = 0.0;

	forAllConstIter(typename KinematicCloud<CloudType>, *this, iter)
	{
		const parcelType& p = iter();

		linearKineticEnergy += p.nParticle()*0.5*p.mass()*(p.U() & p.U());
	}

	return linearKineticEnergy;
}


template<class CloudType>
inline tnbLib::scalar tnbLib::KinematicCloud<CloudType>::Dij
(
	const label i,
	const label j
) const
{
	scalar si = 0.0;
	scalar sj = 0.0;
	forAllConstIter(typename KinematicCloud<CloudType>, *this, iter)
	{
		const parcelType& p = iter();
		si += p.nParticle()*pow(p.d(), i);
		sj += p.nParticle()*pow(p.d(), j);
	}

	reduce(si, sumOp<scalar>());
	reduce(sj, sumOp<scalar>());
	sj = max(sj, vSmall);

	return si / sj;
}


template<class CloudType>
inline tnbLib::scalar tnbLib::KinematicCloud<CloudType>::Dmax() const
{
	scalar d = -great;
	forAllConstIter(typename KinematicCloud<CloudType>, *this, iter)
	{
		const parcelType& p = iter();
		d = max(d, p.d());
	}

	reduce(d, maxOp<scalar>());

	return max(0.0, d);
}


template<class CloudType>
inline tnbLib::Random& tnbLib::KinematicCloud<CloudType>::rndGen() const
{
	return rndGen_;
}


//template<class CloudType>
//inline tnbLib::List<tnbLib::DynamicList<typename CloudType::particleType*>>&
//tnbLib::KinematicCloud<CloudType>::cellOccupancy()
//{
//	if (cellOccupancyPtr_.empty())
//	{
//		buildCellOccupancy();
//	}
//
//	return cellOccupancyPtr_();
//}

// Edited by amir
template<class CloudType>
inline tnbLib::List<tnbLib::DynamicList<typename tnbLib::KinematicCloud<CloudType>::parcelType *>>&
tnbLib::KinematicCloud<CloudType>::cellOccupancy()
{
	if (cellOccupancyPtr_.empty())
	{
		buildCellOccupancy();
	}

	return cellOccupancyPtr_();
}


template<class CloudType>
inline const tnbLib::scalarField&
tnbLib::KinematicCloud<CloudType>::cellLengthScale() const
{
	return cellLengthScale_;
}


template<class CloudType>
inline tnbLib::DimensionedField<tnbLib::vector, tnbLib::volMesh>&
tnbLib::KinematicCloud<CloudType>::UTrans()
{
	return UTrans_();
}


template<class CloudType>
inline const tnbLib::DimensionedField<tnbLib::vector, tnbLib::volMesh>&
tnbLib::KinematicCloud<CloudType>::UTrans() const
{
	return UTrans_();
}


template<class CloudType>
inline tnbLib::DimensionedField<tnbLib::scalar, tnbLib::volMesh>&
tnbLib::KinematicCloud<CloudType>::UCoeff()
{
	return UCoeff_();
}


template<class CloudType>
inline const tnbLib::DimensionedField<tnbLib::scalar, tnbLib::volMesh>&
tnbLib::KinematicCloud<CloudType>::UCoeff() const
{
	return UCoeff_();
}


template<class CloudType>
inline tnbLib::tmp<tnbLib::fvVectorMatrix>
tnbLib::KinematicCloud<CloudType>::SU(volVectorField& U) const
{
	if (debug)
	{
		Info << "UTrans min/max = " << min(UTrans()).value() << ", "
			<< max(UTrans()).value() << nl
			<< "UCoeff min/max = " << min(UCoeff()).value() << ", "
			<< max(UCoeff()).value() << endl;
	}

	if (solution_.coupled())
	{
		if (solution_.semiImplicit("U"))
		{
			const volScalarField::Internal
				Vdt(mesh_.V()*this->db().time().deltaT());

			return UTrans() / Vdt - fvm::Sp(UCoeff() / Vdt, U) + UCoeff() / Vdt * U;
		}
		else
		{
			tmp<fvVectorMatrix> tfvm(new fvVectorMatrix(U, dimForce));
			fvVectorMatrix& fvm = tfvm.ref();

			fvm.source() = -UTrans() / (this->db().time().deltaT());

			return tfvm;
		}
	}

	return tmp<fvVectorMatrix>(new fvVectorMatrix(U, dimForce));
}


template<class CloudType>
inline const tnbLib::tmp<tnbLib::volScalarField>
tnbLib::KinematicCloud<CloudType>::vDotSweep() const
{
	tmp<volScalarField> tvDotSweep
	(
		volScalarField::New
		(
			this->name() + ":vDotSweep",
			mesh_,
			dimensionedScalar(dimless / dimTime, 0),
			extrapolatedCalculatedFvPatchScalarField::typeName
		)
	);

	volScalarField& vDotSweep = tvDotSweep.ref();
	forAllConstIter(typename KinematicCloud<CloudType>, *this, iter)
	{
		const parcelType& p = iter();
		const label celli = p.cell();

		vDotSweep[celli] += p.nParticle()*p.areaP()*mag(p.U() - U_[celli]);
	}

	vDotSweep.primitiveFieldRef() /= mesh_.V();
	vDotSweep.correctBoundaryConditions();

	return tvDotSweep;
}


template<class CloudType>
inline const tnbLib::tmp<tnbLib::volScalarField>
tnbLib::KinematicCloud<CloudType>::theta() const
{
	tmp<volScalarField> ttheta
	(
		volScalarField::New
		(
			this->name() + ":theta",
			mesh_,
			dimensionedScalar(dimless, 0),
			extrapolatedCalculatedFvPatchScalarField::typeName
		)
	);

	volScalarField& theta = ttheta.ref();
	forAllConstIter(typename KinematicCloud<CloudType>, *this, iter)
	{
		const parcelType& p = iter();
		const label celli = p.cell();

		theta[celli] += p.nParticle()*p.volume();
	}

	theta.primitiveFieldRef() /= mesh_.V();
	theta.correctBoundaryConditions();

	return ttheta;
}


template<class CloudType>
inline const tnbLib::tmp<tnbLib::volScalarField>
tnbLib::KinematicCloud<CloudType>::alpha() const
{
	tmp<volScalarField> talpha
	(
		volScalarField::New
		(
			this->name() + ":alpha",
			mesh_,
			dimensionedScalar(dimless, 0)
		)
	);

	scalarField& alpha = talpha.ref().primitiveFieldRef();
	forAllConstIter(typename KinematicCloud<CloudType>, *this, iter)
	{
		const parcelType& p = iter();
		const label celli = p.cell();

		alpha[celli] += p.nParticle()*p.mass();
	}

	alpha /= (mesh_.V()*rho_);

	return talpha;
}


template<class CloudType>
inline const tnbLib::tmp<tnbLib::volScalarField>
tnbLib::KinematicCloud<CloudType>::rhoEff() const
{
	tmp<volScalarField> trhoEff
	(
		volScalarField::New
		(
			this->name() + ":rhoEff",
			mesh_,
			dimensionedScalar(dimDensity, 0)
		)
	);

	scalarField& rhoEff = trhoEff.ref().primitiveFieldRef();
	forAllConstIter(typename KinematicCloud<CloudType>, *this, iter)
	{
		const parcelType& p = iter();
		const label celli = p.cell();

		rhoEff[celli] += p.nParticle()*p.mass();
	}

	rhoEff /= mesh_.V();

	return trhoEff;
}


// ************************************************************************* //