#pragma once

#include <phaseSystem.hxx>

#include <fvmDdt.hxx>
#include <fvmDiv.hxx>
#include <fvmSup.hxx>
#include <fvmLaplacian.hxx>
#include <fvcDdt.hxx>
#include <fvcDiv.hxx>
#include <fvMatrix.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class BasePhaseModel>
tnbLib::MultiComponentPhaseModel<BasePhaseModel>::MultiComponentPhaseModel
(
	const phaseSystem& fluid,
	const word& phaseName,
	const label index
)
	:
	BasePhaseModel(fluid, phaseName, index),
	Sct_
	(
		"Sct",
		dimless,
		fluid.subDict(phaseName)
	),
	residualAlpha_
	(
		"residualAlpha",
		dimless,
		fluid.mesh().solverDict("Yi")
	),
	inertIndex_(-1)
{
	const word inertSpecie
	(
		this->thermo_->lookupOrDefault("inertSpecie", word::null)
	);

	if (inertSpecie != word::null)
	{
		inertIndex_ = this->thermo_->composition().species()[inertSpecie];
	}

	PtrList<volScalarField>& Y = this->thermo_->composition().Y();

	forAll(Y, i)
	{
		if (i != inertIndex_ && this->thermo_->composition().active(i))
		{
			const label j = YActive_.size();
			YActive_.resize(j + 1);
			YActive_.set(j, &Y[i]);
		}
	}
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class BasePhaseModel>
tnbLib::MultiComponentPhaseModel<BasePhaseModel>::~MultiComponentPhaseModel()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class BasePhaseModel>
void tnbLib::MultiComponentPhaseModel<BasePhaseModel>::correctThermo()
{
	volScalarField Yt
	(
		IOobject
		(
			IOobject::groupName("Yt", this->name()),
			this->fluid().mesh().time().timeName(),
			this->fluid().mesh()
		),
		this->fluid().mesh(),
		dimensionedScalar(dimless, 0)
	);

	PtrList<volScalarField>& Yi = YRef();

	forAll(Yi, i)
	{
		if (i != inertIndex_)
		{
			Yt += Yi[i];
		}
	}

	if (inertIndex_ != -1)
	{
		Yi[inertIndex_] = scalar(1) - Yt;
		Yi[inertIndex_].max(0);
	}
	else
	{
		forAll(Yi, i)
		{
			Yi[i] /= Yt;
			Yi[i].max(0);
		}
	}

	BasePhaseModel::correctThermo();
}


template<class BasePhaseModel>
bool tnbLib::MultiComponentPhaseModel<BasePhaseModel>::pure() const
{
	return false;
}


template<class BasePhaseModel>
tnbLib::tmp<tnbLib::fvScalarMatrix>
tnbLib::MultiComponentPhaseModel<BasePhaseModel>::YiEqn(volScalarField& Yi)
{
	const volScalarField& alpha = *this;
	const surfaceScalarField alphaRhoPhi(this->alphaRhoPhi());
	const volScalarField& rho = this->thermo().rho();

	return
		(
			fvm::ddt(alpha, rho, Yi)
			+ fvm::div(alphaRhoPhi, Yi, "div(" + alphaRhoPhi.name() + ",Yi)")

			- fvm::laplacian
			(
				fvc::interpolate(alpha)
				* fvc::interpolate(this->muEff() / Sct_),
				Yi
			)
			==
			alpha * this->R(Yi)

			+ fvc::ddt(residualAlpha_ * rho, Yi)
			- fvm::ddt(residualAlpha_ * rho, Yi)
			);
}


template<class BasePhaseModel>
const tnbLib::PtrList<tnbLib::volScalarField>&
tnbLib::MultiComponentPhaseModel<BasePhaseModel>::Y() const
{
	return this->thermo_->composition().Y();
}


template<class BasePhaseModel>
const tnbLib::volScalarField&
tnbLib::MultiComponentPhaseModel<BasePhaseModel>::Y(const word& name) const
{
	return this->thermo_->composition().Y(name);
}


template<class BasePhaseModel>
tnbLib::PtrList<tnbLib::volScalarField>&
tnbLib::MultiComponentPhaseModel<BasePhaseModel>::YRef()
{
	return this->thermo_->composition().Y();
}


template<class BasePhaseModel>
const tnbLib::UPtrList<tnbLib::volScalarField>&
tnbLib::MultiComponentPhaseModel<BasePhaseModel>::YActive() const
{
	return YActive_;
}


template<class BasePhaseModel>
tnbLib::UPtrList<tnbLib::volScalarField>&
tnbLib::MultiComponentPhaseModel<BasePhaseModel>::YActiveRef()
{
	return YActive_;
}