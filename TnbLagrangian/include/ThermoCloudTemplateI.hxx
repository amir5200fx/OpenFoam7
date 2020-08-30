#pragma once
#include <physicoChemicalConstants.hxx>

using namespace tnbLib::constant;

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CloudType>
inline const tnbLib::ThermoCloud<CloudType>&
tnbLib::ThermoCloud<CloudType>::cloudCopy() const
{
	return cloudCopyPtr_();
}


template<class CloudType>
inline const typename CloudType::particleType::constantProperties&
tnbLib::ThermoCloud<CloudType>::constProps() const
{
	return constProps_;
}


template<class CloudType>
inline typename CloudType::particleType::constantProperties&
tnbLib::ThermoCloud<CloudType>::constProps()
{
	return constProps_;
}


template<class CloudType>
inline const tnbLib::SLGThermo& tnbLib::ThermoCloud<CloudType>::thermo() const
{
	return thermo_;
}


template<class CloudType>
inline const tnbLib::volScalarField& tnbLib::ThermoCloud<CloudType>::T() const
{
	return T_;
}


template<class CloudType>
inline const tnbLib::volScalarField& tnbLib::ThermoCloud<CloudType>::p() const
{
	return p_;
}


template<class CloudType>
inline const tnbLib::HeatTransferModel<tnbLib::ThermoCloud<CloudType>>&
tnbLib::ThermoCloud<CloudType>::heatTransfer() const
{
	return heatTransferModel_;
}


template<class CloudType>
inline const tnbLib::integrationScheme&
tnbLib::ThermoCloud<CloudType>::TIntegrator() const
{
	return TIntegrator_;
}


template<class CloudType>
inline bool tnbLib::ThermoCloud<CloudType>::radiation() const
{
	return radiation_;
}


template<class CloudType>
inline tnbLib::DimensionedField<tnbLib::scalar, tnbLib::volMesh>&
tnbLib::ThermoCloud<CloudType>::radAreaP()
{
	if (!radiation_)
	{
		FatalErrorInFunction
			<< "Radiation field requested, but radiation model not active"
			<< abort(FatalError);
	}

	return radAreaP_();
}


template<class CloudType>
inline const tnbLib::DimensionedField<tnbLib::scalar, tnbLib::volMesh>&
tnbLib::ThermoCloud<CloudType>::radAreaP() const
{
	if (!radiation_)
	{
		FatalErrorInFunction
			<< "Radiation field requested, but radiation model not active"
			<< abort(FatalError);
	}

	return radAreaP_();
}


template<class CloudType>
inline tnbLib::DimensionedField<tnbLib::scalar, tnbLib::volMesh>&
tnbLib::ThermoCloud<CloudType>::radT4()
{
	if (!radiation_)
	{
		FatalErrorInFunction
			<< "Radiation field requested, but radiation model not active"
			<< abort(FatalError);
	}

	return radT4_();
}


template<class CloudType>
inline const tnbLib::DimensionedField<tnbLib::scalar, tnbLib::volMesh>&
tnbLib::ThermoCloud<CloudType>::radT4() const
{
	if (!radiation_)
	{
		FatalErrorInFunction
			<< "Radiation field requested, but radiation model not active"
			<< abort(FatalError);
	}

	return radT4_();
}


template<class CloudType>
inline tnbLib::DimensionedField<tnbLib::scalar, tnbLib::volMesh>&
tnbLib::ThermoCloud<CloudType>::radAreaPT4()
{
	if (!radiation_)
	{
		FatalErrorInFunction
			<< "Radiation field requested, but radiation model not active"
			<< abort(FatalError);
	}

	return radAreaPT4_();
}


template<class CloudType>
inline const tnbLib::DimensionedField<tnbLib::scalar, tnbLib::volMesh>&
tnbLib::ThermoCloud<CloudType>::radAreaPT4() const
{
	if (!radiation_)
	{
		FatalErrorInFunction
			<< "Radiation field requested, but radiation model not active"
			<< abort(FatalError);
	}

	return radAreaPT4_();
}


template<class CloudType>
inline tnbLib::DimensionedField<tnbLib::scalar, tnbLib::volMesh>&
tnbLib::ThermoCloud<CloudType>::hsTrans()
{
	return hsTrans_();
}


template<class CloudType>
inline const tnbLib::DimensionedField<tnbLib::scalar, tnbLib::volMesh>&
tnbLib::ThermoCloud<CloudType>::hsTrans() const
{
	return hsTrans_();
}


template<class CloudType>
inline tnbLib::DimensionedField<tnbLib::scalar, tnbLib::volMesh>&
tnbLib::ThermoCloud<CloudType>::hsCoeff()
{
	return hsCoeff_();
}


template<class CloudType>
inline const tnbLib::DimensionedField<tnbLib::scalar, tnbLib::volMesh>&
tnbLib::ThermoCloud<CloudType>::hsCoeff() const
{
	return hsCoeff_();
}


template<class CloudType>
inline tnbLib::tmp<tnbLib::fvScalarMatrix>
tnbLib::ThermoCloud<CloudType>::Sh(volScalarField& hs) const
{
	if (debug)
	{
		Info << "hsTrans min/max = " << min(hsTrans()).value() << ", "
			<< max(hsTrans()).value() << nl
			<< "hsCoeff min/max = " << min(hsCoeff()).value() << ", "
			<< max(hsCoeff()).value() << endl;
	}

	if (this->solution().coupled())
	{
		if (this->solution().semiImplicit("h"))
		{
			const volScalarField Cp(thermo_.thermo().Cp());
			const volScalarField::Internal
				Vdt(this->mesh().V()*this->db().time().deltaT());

			return
				hsTrans() / Vdt
				- fvm::SuSp(hsCoeff() / (Cp*Vdt), hs)
				+ hsCoeff() / (Cp*Vdt)*hs;
		}
		else
		{
			tmp<fvScalarMatrix> tfvm(new fvScalarMatrix(hs, dimEnergy / dimTime));
			fvScalarMatrix& fvm = tfvm.ref();

			fvm.source() = -hsTrans() / (this->db().time().deltaT());

			return tfvm;
		}
	}

	return tmp<fvScalarMatrix>(new fvScalarMatrix(hs, dimEnergy / dimTime));
}


template<class CloudType>
inline tnbLib::tmp<tnbLib::volScalarField> tnbLib::ThermoCloud<CloudType>::Ep() const
{
	tmp<volScalarField> tEp
	(
		volScalarField::New
		(
			this->name() + ":radiation:Ep",
			this->mesh(),
			dimensionedScalar(dimMass / dimLength / pow3(dimTime), 0)
		)
	);

	if (radiation_)
	{
		scalarField& Ep = tEp.ref().primitiveFieldRef();
		const scalar dt = this->db().time().deltaTValue();
		const scalarField& V = this->mesh().V();
		const scalar epsilon = constProps_.epsilon0();
		const scalarField& sumAreaPT4 = radAreaPT4_->field();

		Ep = sumAreaPT4 * epsilon*physicoChemical::sigma.value() / V / dt;
	}

	return tEp;
}


template<class CloudType>
inline tnbLib::tmp<tnbLib::volScalarField> tnbLib::ThermoCloud<CloudType>::ap() const
{
	tmp<volScalarField> tap
	(
		volScalarField::New
		(
			this->name() + ":radiation:ap",
			this->mesh(),
			dimensionedScalar(dimless / dimLength, 0)
		)
	);

	if (radiation_)
	{
		scalarField& ap = tap.ref().primitiveFieldRef();
		const scalar dt = this->db().time().deltaTValue();
		const scalarField& V = this->mesh().V();
		const scalar epsilon = constProps_.epsilon0();
		const scalarField& sumAreaP = radAreaP_->field();

		ap = sumAreaP * epsilon / V / dt;
	}

	return tap;
}


template<class CloudType>
inline tnbLib::tmp<tnbLib::volScalarField>
tnbLib::ThermoCloud<CloudType>::sigmap() const
{
	tmp<volScalarField> tsigmap
	(
		volScalarField::New
		(
			this->name() + ":radiation:sigmap",
			this->mesh(),
			dimensionedScalar(dimless / dimLength, 0)
		)
	);

	if (radiation_)
	{
		scalarField& sigmap = tsigmap.ref().primitiveFieldRef();
		const scalar dt = this->db().time().deltaTValue();
		const scalarField& V = this->mesh().V();
		const scalar epsilon = constProps_.epsilon0();
		const scalar f = constProps_.f0();
		const scalarField& sumAreaP = radAreaP_->field();

		sigmap *= sumAreaP * (1.0 - f)*(1.0 - epsilon) / V / dt;
	}

	return tsigmap;
}


template<class CloudType>
inline tnbLib::scalar tnbLib::ThermoCloud<CloudType>::Tmax() const
{
	scalar T = -great;
	label n = 0;
	forAllConstIter(typename ThermoCloud<CloudType>, *this, iter)
	{
		const parcelType& p = iter();
		T = max(T, p.T());
		n++;
	}

	reduce(T, maxOp<scalar>());
	reduce(n, sumOp<label>());

	if (n > 0)
	{
		return T;
	}
	else
	{
		return 0.0;
	}
}


template<class CloudType>
inline tnbLib::scalar tnbLib::ThermoCloud<CloudType>::Tmin() const
{
	scalar T = great;
	label n = 0;
	forAllConstIter(typename ThermoCloud<CloudType>, *this, iter)
	{
		const parcelType& p = iter();
		T = min(T, p.T());
		n++;
	}

	reduce(T, minOp<scalar>());
	reduce(n, sumOp<label>());

	if (n > 0)
	{
		return T;
	}
	else
	{
		return 0.0;
	}
}


// ************************************************************************* //