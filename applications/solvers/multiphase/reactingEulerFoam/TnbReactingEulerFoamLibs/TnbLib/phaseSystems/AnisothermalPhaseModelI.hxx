#pragma once

#include <phaseSystem.hxx>

using namespace tnbLib;

	template<class BasePhaseModel>
	tnbLib::tmp<tnbLib::volScalarField>
		tnbLib::AnisothermalPhaseModel<BasePhaseModel>::filterPressureWork
		(
			const tmp<volScalarField>& pressureWork
		) const
	{
		const volScalarField& alpha = *this;

		scalar pressureWorkAlphaLimit =
			this->thermo_->lookupOrDefault("pressureWorkAlphaLimit", 0.0);

		if (pressureWorkAlphaLimit > 0)
		{
			return
				(
					max(alpha - pressureWorkAlphaLimit, scalar(0))
					/ max(alpha - pressureWorkAlphaLimit, pressureWorkAlphaLimit)
					) * pressureWork;
		}
		else
		{
			return pressureWork;
		}
	}


	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	template<class BasePhaseModel>
	tnbLib::AnisothermalPhaseModel<BasePhaseModel>::AnisothermalPhaseModel
	(
		const phaseSystem& fluid,
		const word& phaseName,
		const label index
	)
		:
		BasePhaseModel(fluid, phaseName, index)
	{}


	// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

	template<class BasePhaseModel>
	tnbLib::AnisothermalPhaseModel<BasePhaseModel>::~AnisothermalPhaseModel()
	{}


	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	template<class BasePhaseModel>
	void tnbLib::AnisothermalPhaseModel<BasePhaseModel>::correctThermo()
	{
		BasePhaseModel::correctThermo();

		this->thermo_->correct();
	}


	template<class BasePhaseModel>
	bool tnbLib::AnisothermalPhaseModel<BasePhaseModel>::isothermal() const
	{
		return false;
	}


	template<class BasePhaseModel>
	tnbLib::tmp<tnbLib::fvScalarMatrix>
		tnbLib::AnisothermalPhaseModel<BasePhaseModel>::heEqn()
	{
		const volScalarField& alpha = *this;

		const volVectorField U(this->U());
		const surfaceScalarField alphaPhi(this->alphaPhi());
		const surfaceScalarField alphaRhoPhi(this->alphaRhoPhi());

		const volScalarField contErr(this->continuityError());
		const volScalarField K(this->K());

		volScalarField& he = this->thermo_->he();

		tmp<fvScalarMatrix> tEEqn
		(
			fvm::ddt(alpha, this->rho(), he)
			+ fvm::div(alphaRhoPhi, he)
			- fvm::Sp(contErr, he)

			+ fvc::ddt(alpha, this->rho(), K) + fvc::div(alphaRhoPhi, K)
			- contErr * K

			- fvm::laplacian
			(
				fvc::interpolate(alpha)
				* fvc::interpolate(this->alphaEff()),
				he
			)
			==
			alpha * this->Qdot()
		);

		// Add the appropriate pressure-work term
		if (he.name() == this->thermo_->phasePropertyName("e"))
		{
			tEEqn.ref() += filterPressureWork
			(
				fvc::div(fvc::absolute(alphaPhi, alpha, U), this->thermo().p())
				+ this->thermo().p() * fvc::ddt(alpha)
			);
		}
		else if (this->thermo_->dpdt())
		{
			tEEqn.ref() -= filterPressureWork(alpha * this->fluid().dpdt());
		}

		return tEEqn;
	}

