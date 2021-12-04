#pragma once

#include <MovingPhaseModel.hxx>
#include <phaseSystem.hxx>

#include <fixedValueFvPatchFields.hxx>
#include <slipFvPatchFields.hxx>
#include <partialSlipFvPatchFields.hxx>

#include <fvmDdt.hxx>
#include <fvmDiv.hxx>
#include <fvmSup.hxx>
#include <fvcDdt.hxx>
#include <fvcDiv.hxx>
#include <fvcFlux.hxx>
#include <surfaceInterpolate.hxx>
#include <fvMatrix.hxx>

// * * * * * * * * * * * * * Static Member Functions * * * * * * * * * * * * //

using namespace tnbLib;

template<class BasePhaseModel>
tnbLib::tmp<tnbLib::surfaceScalarField>
tnbLib::MovingPhaseModel<BasePhaseModel>::phi(const volVectorField& U) const
{
	word phiName(IOobject::groupName("phi", this->name()));

	IOobject phiHeader
	(
		phiName,
		U.mesh().time().timeName(),
		U.mesh(),
		IOobject::NO_READ
	);

	if (phiHeader.typeHeaderOk<surfaceScalarField>(true))
	{
		Info << "Reading face flux field " << phiName << endl;

		return tmp<surfaceScalarField>
			(
				new surfaceScalarField
				(
					IOobject
					(
						phiName,
						U.mesh().time().timeName(),
						U.mesh(),
						IOobject::MUST_READ,
						IOobject::AUTO_WRITE
					),
					U.mesh()
				)
				);
	}
	else
	{
		Info << "Calculating face flux field " << phiName << endl;

		wordList phiTypes
		(
			U.boundaryField().size(),
			calculatedFvPatchScalarField::typeName
		);

		forAll(U.boundaryField(), i)
		{
			if
				(
					isA<fixedValueFvPatchVectorField>(U.boundaryField()[i])
					|| isA<slipFvPatchVectorField>(U.boundaryField()[i])
					|| isA<partialSlipFvPatchVectorField>(U.boundaryField()[i])
					)
			{
				phiTypes[i] = fixedValueFvPatchScalarField::typeName;
			}
		}

		return tmp<surfaceScalarField>
			(
				new surfaceScalarField
				(
					IOobject
					(
						phiName,
						U.mesh().time().timeName(),
						U.mesh(),
						IOobject::NO_READ,
						IOobject::AUTO_WRITE
					),
					fvc::flux(U),
					phiTypes
				)
				);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class BasePhaseModel>
tnbLib::MovingPhaseModel<BasePhaseModel>::MovingPhaseModel
(
	const phaseSystem& fluid,
	const word& phaseName,
	const label index
)
	:
	BasePhaseModel(fluid, phaseName, index),
	U_
	(
		IOobject
		(
			IOobject::groupName("U", this->name()),
			fluid.mesh().time().timeName(),
			fluid.mesh(),
			IOobject::MUST_READ,
			IOobject::AUTO_WRITE
		),
		fluid.mesh()
	),
	phi_(phi(U_)),
	alphaPhi_
	(
		IOobject
		(
			IOobject::groupName("alphaPhi", this->name()),
			fluid.mesh().time().timeName(),
			fluid.mesh()
		),
		fluid.mesh(),
		dimensionedScalar(dimensionSet(0, 3, -1, 0, 0), 0)
	),
	alphaRhoPhi_
	(
		IOobject
		(
			IOobject::groupName("alphaRhoPhi", this->name()),
			fluid.mesh().time().timeName(),
			fluid.mesh()
		),
		fluid.mesh(),
		dimensionedScalar(dimensionSet(1, 0, -1, 0, 0), 0)
	),
	DUDt_(nullptr),
	DUDtf_(nullptr),
	divU_(nullptr),
	turbulence_
	(
		phaseCompressibleTurbulenceModel::New
		(
			*this,
			this->thermo().rho(),
			U_,
			alphaRhoPhi_,
			phi_,
			*this
		)
	),
	continuityErrorFlow_
	(
		IOobject
		(
			IOobject::groupName("continuityErrorFlow", this->name()),
			fluid.mesh().time().timeName(),
			fluid.mesh()
		),
		fluid.mesh(),
		dimensionedScalar(dimDensity / dimTime, 0)
	),
	continuityErrorSources_
	(
		IOobject
		(
			IOobject::groupName("continuityErrorSources", this->name()),
			fluid.mesh().time().timeName(),
			fluid.mesh()
		),
		fluid.mesh(),
		dimensionedScalar(dimDensity / dimTime, 0)
	),
	K_(nullptr)
{
	phi_.writeOpt() = IOobject::AUTO_WRITE;

	correctKinematics();
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class BasePhaseModel>
tnbLib::MovingPhaseModel<BasePhaseModel>::~MovingPhaseModel()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class BasePhaseModel>
void tnbLib::MovingPhaseModel<BasePhaseModel>::correctContinuityErrors()
{
	volScalarField& rho = this->thermoRef().rho();

	continuityErrorFlow_ = fvc::ddt(*this, rho) + fvc::div(alphaRhoPhi_);

	continuityErrorSources_ = -(this->fluid().fvOptions()(*this, rho) & rho);
}


template<class BasePhaseModel>
void tnbLib::MovingPhaseModel<BasePhaseModel>::correct()
{
	BasePhaseModel::correct();
	this->fluid().MRF().correctBoundaryVelocity(U_);
	correctContinuityErrors();
}


template<class BasePhaseModel>
void tnbLib::MovingPhaseModel<BasePhaseModel>::correctKinematics()
{
	BasePhaseModel::correctKinematics();

	if (DUDt_.valid())
	{
		DUDt_.clear();
		DUDt();
	}

	if (DUDtf_.valid())
	{
		DUDtf_.clear();
		DUDtf();
	}

	if (K_.valid())
	{
		K_.clear();
		K();
	}
}


template<class BasePhaseModel>
void tnbLib::MovingPhaseModel<BasePhaseModel>::correctThermo()
{
	correctContinuityErrors();
}


template<class BasePhaseModel>
void tnbLib::MovingPhaseModel<BasePhaseModel>::correctTurbulence()
{
	BasePhaseModel::correctTurbulence();

	turbulence_->correct();
}


template<class BasePhaseModel>
void tnbLib::MovingPhaseModel<BasePhaseModel>::correctEnergyTransport()
{
	BasePhaseModel::correctEnergyTransport();

	turbulence_->correctEnergyTransport();
}


template<class BasePhaseModel>
bool tnbLib::MovingPhaseModel<BasePhaseModel>::stationary() const
{
	return false;
}


template<class BasePhaseModel>
tnbLib::tmp<tnbLib::fvVectorMatrix>
tnbLib::MovingPhaseModel<BasePhaseModel>::UEqn()
{
	const volScalarField& alpha = *this;
	const volScalarField& rho = this->thermo().rho();

	return
		(
			fvm::ddt(alpha, rho, U_)
			+ fvm::div(alphaRhoPhi_, U_)
			+ fvm::SuSp(-this->continuityError(), U_)
			+ this->fluid().MRF().DDt(alpha * rho, U_)
			+ turbulence_->divDevRhoReff(U_)
			);
}


template<class BasePhaseModel>
tnbLib::tmp<tnbLib::fvVectorMatrix>
tnbLib::MovingPhaseModel<BasePhaseModel>::UfEqn()
{
	// As the "normal" U-eqn but without the ddt terms

	const volScalarField& alpha = *this;
	const volScalarField& rho = this->thermo().rho();

	return
		(
			fvm::div(alphaRhoPhi_, U_)
			- fvm::Sp(fvc::div(alphaRhoPhi_), U_)
			+ fvm::SuSp(-this->continuityErrorSources(), U_)
			+ this->fluid().MRF().DDt(alpha * rho, U_)
			+ turbulence_->divDevRhoReff(U_)
			);
}


template<class BasePhaseModel>
tnbLib::tmp<tnbLib::volVectorField>
tnbLib::MovingPhaseModel<BasePhaseModel>::U() const
{
	return U_;
}


template<class BasePhaseModel>
tnbLib::volVectorField&
tnbLib::MovingPhaseModel<BasePhaseModel>::URef()
{
	return U_;
}


template<class BasePhaseModel>
tnbLib::tmp<tnbLib::surfaceScalarField>
tnbLib::MovingPhaseModel<BasePhaseModel>::phi() const
{
	return phi_;
}


template<class BasePhaseModel>
tnbLib::surfaceScalarField&
tnbLib::MovingPhaseModel<BasePhaseModel>::phiRef()
{
	return phi_;
}


template<class BasePhaseModel>
tnbLib::tmp<tnbLib::surfaceScalarField>
tnbLib::MovingPhaseModel<BasePhaseModel>::alphaPhi() const
{
	return alphaPhi_;
}


template<class BasePhaseModel>
tnbLib::surfaceScalarField&
tnbLib::MovingPhaseModel<BasePhaseModel>::alphaPhiRef()
{
	return alphaPhi_;
}


template<class BasePhaseModel>
tnbLib::tmp<tnbLib::surfaceScalarField>
tnbLib::MovingPhaseModel<BasePhaseModel>::alphaRhoPhi() const
{
	return alphaRhoPhi_;
}


template<class BasePhaseModel>
tnbLib::surfaceScalarField&
tnbLib::MovingPhaseModel<BasePhaseModel>::alphaRhoPhiRef()
{
	return alphaRhoPhi_;
}


template<class BasePhaseModel>
tnbLib::tmp<tnbLib::volVectorField>
tnbLib::MovingPhaseModel<BasePhaseModel>::DUDt() const
{
	if (!DUDt_.valid())
	{
		DUDt_ = fvc::ddt(U_) + fvc::div(phi_, U_) - fvc::div(phi_) * U_;
	}

	return tmp<volVectorField>(DUDt_());
}


template<class BasePhaseModel>
tnbLib::tmp<tnbLib::surfaceScalarField>
tnbLib::MovingPhaseModel<BasePhaseModel>::DUDtf() const
{
	if (!DUDtf_.valid())
	{
		DUDtf_ = byDt(phi_ - phi_.oldTime());
	}

	return tmp<surfaceScalarField>(DUDtf_());
}


template<class BasePhaseModel>
tnbLib::tmp<tnbLib::volScalarField>
tnbLib::MovingPhaseModel<BasePhaseModel>::continuityError() const
{
	return continuityErrorFlow_ + continuityErrorSources_;
}


template<class BasePhaseModel>
tnbLib::tmp<tnbLib::volScalarField>
tnbLib::MovingPhaseModel<BasePhaseModel>::continuityErrorFlow() const
{
	return continuityErrorFlow_;
}


template<class BasePhaseModel>
tnbLib::tmp<tnbLib::volScalarField>
tnbLib::MovingPhaseModel<BasePhaseModel>::continuityErrorSources() const
{
	return continuityErrorSources_;
}


template<class BasePhaseModel>
tnbLib::tmp<tnbLib::volScalarField>
tnbLib::MovingPhaseModel<BasePhaseModel>::K() const
{
	if (!K_.valid())
	{
		K_ = volScalarField::New
		(
			IOobject::groupName("K", this->name()),
			0.5 * magSqr(this->U())
		);
	}

	return tmp<volScalarField>(K_());
}


template<class BasePhaseModel>
tnbLib::tmp<tnbLib::volScalarField>
tnbLib::MovingPhaseModel<BasePhaseModel>::divU() const
{
	return divU_.valid() ? tmp<volScalarField>(divU_()) : tmp<volScalarField>();
}


template<class BasePhaseModel>
void tnbLib::MovingPhaseModel<BasePhaseModel>::divU(tmp<volScalarField> divU)
{
	divU_ = divU;
}


template<class BasePhaseModel>
tnbLib::tmp<tnbLib::volScalarField>
tnbLib::MovingPhaseModel<BasePhaseModel>::mut() const
{
	return turbulence_->mut();
}


template<class BasePhaseModel>
tnbLib::tmp<tnbLib::volScalarField>
tnbLib::MovingPhaseModel<BasePhaseModel>::muEff() const
{
	return turbulence_->muEff();
}


template<class BasePhaseModel>
tnbLib::tmp<tnbLib::volScalarField>
tnbLib::MovingPhaseModel<BasePhaseModel>::nut() const
{
	return turbulence_->nut();
}


template<class BasePhaseModel>
tnbLib::tmp<tnbLib::volScalarField>
tnbLib::MovingPhaseModel<BasePhaseModel>::nuEff() const
{
	return turbulence_->nuEff();
}


template<class BasePhaseModel>
tnbLib::tmp<tnbLib::volScalarField>
tnbLib::MovingPhaseModel<BasePhaseModel>::kappaEff() const
{
	return turbulence_->kappaEff();
}


template<class BasePhaseModel>
tnbLib::tmp<tnbLib::scalarField>
tnbLib::MovingPhaseModel<BasePhaseModel>::kappaEff(const label patchi) const
{
	return turbulence_->kappaEff(patchi);
}


template<class BasePhaseModel>
tnbLib::tmp<tnbLib::volScalarField>
tnbLib::MovingPhaseModel<BasePhaseModel>::alphaEff() const
{
	return turbulence_->alphaEff();
}


template<class BasePhaseModel>
tnbLib::tmp<tnbLib::scalarField>
tnbLib::MovingPhaseModel<BasePhaseModel>::alphaEff(const label patchi) const
{
	return turbulence_->alphaEff(patchi);
}


template<class BasePhaseModel>
tnbLib::tmp<tnbLib::volScalarField>
tnbLib::MovingPhaseModel<BasePhaseModel>::k() const
{
	return turbulence_->k();
}


template<class BasePhaseModel>
tnbLib::tmp<tnbLib::volScalarField>
tnbLib::MovingPhaseModel<BasePhaseModel>::pPrime() const
{
	return turbulence_->pPrime();
}
