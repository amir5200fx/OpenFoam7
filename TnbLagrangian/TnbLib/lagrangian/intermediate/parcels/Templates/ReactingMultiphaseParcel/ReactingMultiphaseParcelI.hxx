#pragma once
/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2011-2018 OpenFOAM Foundation
	 \\/     M anipulation  |
-------------------------------------------------------------------------------
License
	This file is part of OpenFOAM.

	OpenFOAM is free software: you can redistribute it and/or modify it
	under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
	ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
	FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
	for more details.

	You should have received a copy of the GNU General Public License
	along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

\*---------------------------------------------------------------------------*/

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class ParcelType>
inline tnbLib::ReactingMultiphaseParcel<ParcelType>::constantProperties::
constantProperties()
	:
	ParcelType::constantProperties(),
	TDevol_(this->dict_, 0.0),
	LDevol_(this->dict_, 0.0),
	hRetentionCoeff_(this->dict_, 0.0)
{}


template<class ParcelType>
inline tnbLib::ReactingMultiphaseParcel<ParcelType>::constantProperties::
constantProperties
(
	const constantProperties& cp
)
	:
	ParcelType::constantProperties(cp),
	TDevol_(cp.TDevol_),
	LDevol_(cp.LDevol_),
	hRetentionCoeff_(cp.hRetentionCoeff_)
{}


template<class ParcelType>
inline tnbLib::ReactingMultiphaseParcel<ParcelType>::constantProperties::
constantProperties
(
	const dictionary& parentDict
)
	:
	ParcelType::constantProperties(parentDict),
	TDevol_(this->dict_, "TDevol"),
	LDevol_(this->dict_, "LDevol"),
	hRetentionCoeff_(this->dict_, "hRetentionCoeff")
{}


template<class ParcelType>
inline tnbLib::ReactingMultiphaseParcel<ParcelType>::ReactingMultiphaseParcel
(
	const polyMesh& mesh,
	const barycentric& coordinates,
	const label celli,
	const label tetFacei,
	const label tetPti
)
	:
	ParcelType(mesh, coordinates, celli, tetFacei, tetPti),
	YGas_(0),
	YLiquid_(0),
	YSolid_(0),
	canCombust_(0)
{}


template<class ParcelType>
inline tnbLib::ReactingMultiphaseParcel<ParcelType>::ReactingMultiphaseParcel
(
	const polyMesh& mesh,
	const vector& position,
	const label celli
)
	:
	ParcelType(mesh, position, celli),
	YGas_(0),
	YLiquid_(0),
	YSolid_(0),
	canCombust_(0)
{}


template<class ParcelType>
inline tnbLib::ReactingMultiphaseParcel<ParcelType>::ReactingMultiphaseParcel
(
	const polyMesh& mesh,
	const barycentric& coordinates,
	const label celli,
	const label tetFacei,
	const label tetPti,
	const label typeId,
	const scalar nParticle0,
	const scalar d0,
	const scalar dTarget0,
	const vector& U0,
	const vector& f0,
	const vector& angularMomentum0,
	const vector& torque0,
	const scalarField& Y0,
	const scalarField& YGas0,
	const scalarField& YLiquid0,
	const scalarField& YSolid0,
	const constantProperties& constProps
)
	:
	ParcelType
	(
		mesh,
		coordinates,
		celli,
		tetFacei,
		tetPti,
		typeId,
		nParticle0,
		d0,
		dTarget0,
		U0,
		f0,
		angularMomentum0,
		torque0,
		Y0,
		constProps
	),
	YGas_(YGas0),
	YLiquid_(YLiquid0),
	YSolid_(YSolid0),
	canCombust_(0)
{}


// * * * * * * * * * constantProperties Member Functions * * * * * * * * * * //

template<class ParcelType>
inline tnbLib::scalar
tnbLib::ReactingMultiphaseParcel<ParcelType>::constantProperties::TDevol() const
{
	return TDevol_.value();
}


template<class ParcelType>
inline tnbLib::scalar
tnbLib::ReactingMultiphaseParcel<ParcelType>::constantProperties::LDevol() const
{
	return LDevol_.value();
}


template<class ParcelType>
inline tnbLib::scalar
tnbLib::ReactingMultiphaseParcel<ParcelType>::constantProperties::
hRetentionCoeff() const
{
	scalar value = hRetentionCoeff_.value();

	if ((value < 0) || (value > 1))
	{
		FatalErrorInFunction
			<< "hRetentionCoeff must be in the range 0 to 1" << nl
			<< exit(FatalError) << endl;
	}

	return value;
}


// * * * * * * * * * * ThermoParcel Member Functions * * * * * * * * * * * * //

template<class ParcelType>
inline const tnbLib::scalarField& tnbLib::ReactingMultiphaseParcel<ParcelType>::
YGas() const
{
	return YGas_;
}


template<class ParcelType>
inline const tnbLib::scalarField& tnbLib::ReactingMultiphaseParcel<ParcelType>::
YLiquid() const
{
	return YLiquid_;
}


template<class ParcelType>
inline const tnbLib::scalarField& tnbLib::ReactingMultiphaseParcel<ParcelType>::
YSolid() const
{
	return YSolid_;
}


template<class ParcelType>
inline tnbLib::label
tnbLib::ReactingMultiphaseParcel<ParcelType>::canCombust() const
{
	return canCombust_;
}


template<class ParcelType>
inline tnbLib::scalarField& tnbLib::ReactingMultiphaseParcel<ParcelType>::YGas()
{
	return YGas_;
}


template<class ParcelType>
inline tnbLib::scalarField& tnbLib::ReactingMultiphaseParcel<ParcelType>::YLiquid()
{
	return YLiquid_;
}


template<class ParcelType>
inline tnbLib::scalarField& tnbLib::ReactingMultiphaseParcel<ParcelType>::YSolid()
{
	return YSolid_;
}


template<class ParcelType>
inline tnbLib::label& tnbLib::ReactingMultiphaseParcel<ParcelType>::canCombust()
{
	return canCombust_;
}


// ************************************************************************* //

// IO.cxx
#include <IOstreams.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

template<class ParcelType>
tnbLib::string tnbLib::ReactingMultiphaseParcel<ParcelType>::propertyList_ =
tnbLib::ReactingMultiphaseParcel<ParcelType>::propertyList();

template<class ParcelType>
const std::size_t tnbLib::ReactingMultiphaseParcel<ParcelType>::sizeofFields_
(
	0
);


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class ParcelType>
tnbLib::ReactingMultiphaseParcel<ParcelType>::ReactingMultiphaseParcel
(
	const polyMesh& mesh,
	Istream& is,
	bool readFields
)
	:
	ParcelType(mesh, is, readFields),
	YGas_(0),
	YLiquid_(0),
	YSolid_(0),
	canCombust_(0)
{
	if (readFields)
	{
		DynamicList<scalar> Yg;
		DynamicList<scalar> Yl;
		DynamicList<scalar> Ys;

		is >> Yg >> Yl >> Ys;

		YGas_.transfer(Yg);
		YLiquid_.transfer(Yl);
		YSolid_.transfer(Ys);

		// scale the mass fractions
		const scalarField& YMix = this->Y_;
		YGas_ /= YMix[GAS] + rootVSmall;
		YLiquid_ /= YMix[LIQ] + rootVSmall;
		YSolid_ /= YMix[SLD] + rootVSmall;
	}

	// Check state of Istream
	is.check
	(
		"ReactingMultiphaseParcel<ParcelType>::ReactingMultiphaseParcel"
		"("
		"const polyMesh&, "
		"Istream&, "
		"bool"
		")"
	);
}


template<class ParcelType>
template<class CloudType>
void tnbLib::ReactingMultiphaseParcel<ParcelType>::readFields(CloudType& c)
{
	ParcelType::readFields(c);
}


template<class ParcelType>
template<class CloudType, class CompositionType>
void tnbLib::ReactingMultiphaseParcel<ParcelType>::readFields
(
	CloudType& c,
	const CompositionType& compModel
)
{
	bool valid = c.size();

	ParcelType::readFields(c, compModel);

	// Get names and sizes for each Y...
	const label idGas = compModel.idGas();
	const wordList& gasNames = compModel.componentNames(idGas);
	const label idLiquid = compModel.idLiquid();
	const wordList& liquidNames = compModel.componentNames(idLiquid);
	const label idSolid = compModel.idSolid();
	const wordList& solidNames = compModel.componentNames(idSolid);
	const wordList& stateLabels = compModel.stateLabels();

	// Set storage for each Y... for each parcel
	forAllIter(typename Cloud<ReactingMultiphaseParcel<ParcelType>>, c, iter)
	{
		ReactingMultiphaseParcel<ParcelType>& p = iter();
		p.YGas_.setSize(gasNames.size(), 0.0);
		p.YLiquid_.setSize(liquidNames.size(), 0.0);
		p.YSolid_.setSize(solidNames.size(), 0.0);
	}

	// Populate YGas for each parcel
	forAll(gasNames, j)
	{
		IOField<scalar> YGas
		(
			c.fieldIOobject
			(
				"Y" + gasNames[j] + stateLabels[idGas],
				IOobject::MUST_READ
			),
			valid
		);

		label i = 0;
		forAllIter
		(
			typename Cloud<ReactingMultiphaseParcel<ParcelType>>,
			c,
			iter
		)
		{
			ReactingMultiphaseParcel<ParcelType>& p = iter();
			p.YGas_[j] = YGas[i++] / (p.Y()[GAS] + rootVSmall);
		}
	}
	// Populate YLiquid for each parcel
	forAll(liquidNames, j)
	{
		IOField<scalar> YLiquid
		(
			c.fieldIOobject
			(
				"Y" + liquidNames[j] + stateLabels[idLiquid],
				IOobject::MUST_READ
			),
			valid
		);

		label i = 0;
		forAllIter
		(
			typename Cloud<ReactingMultiphaseParcel<ParcelType>>,
			c,
			iter
		)
		{
			ReactingMultiphaseParcel<ParcelType>& p = iter();
			p.YLiquid_[j] = YLiquid[i++] / (p.Y()[LIQ] + rootVSmall);
		}
	}
	// Populate YSolid for each parcel
	forAll(solidNames, j)
	{
		IOField<scalar> YSolid
		(
			c.fieldIOobject
			(
				"Y" + solidNames[j] + stateLabels[idSolid],
				IOobject::MUST_READ
			),
			valid
		);

		label i = 0;
		forAllIter
		(
			typename Cloud<ReactingMultiphaseParcel<ParcelType>>,
			c,
			iter
		)
		{
			ReactingMultiphaseParcel<ParcelType>& p = iter();
			p.YSolid_[j] = YSolid[i++] / (p.Y()[SLD] + rootVSmall);
		}
	}
}


template<class ParcelType>
template<class CloudType>
void tnbLib::ReactingMultiphaseParcel<ParcelType>::writeFields(const CloudType& c)
{
	ParcelType::writeFields(c);
}


template<class ParcelType>
template<class CloudType, class CompositionType>
void tnbLib::ReactingMultiphaseParcel<ParcelType>::writeFields
(
	const CloudType& c,
	const CompositionType& compModel
)
{
	ParcelType::writeFields(c, compModel);

	label np = c.size();

	// Write the composition fractions
	{
		const wordList& stateLabels = compModel.stateLabels();

		const label idGas = compModel.idGas();
		const wordList& gasNames = compModel.componentNames(idGas);
		forAll(gasNames, j)
		{
			IOField<scalar> YGas
			(
				c.fieldIOobject
				(
					"Y" + gasNames[j] + stateLabels[idGas],
					IOobject::NO_READ
				),
				np
			);

			label i = 0;
			forAllConstIter
			(
				typename Cloud<ReactingMultiphaseParcel<ParcelType>>,
				c,
				iter
			)
			{
				const ReactingMultiphaseParcel<ParcelType>& p0 = iter();
				YGas[i++] = p0.YGas()[j] * p0.Y()[GAS];
			}

			YGas.write(np > 0);
		}

		const label idLiquid = compModel.idLiquid();
		const wordList& liquidNames = compModel.componentNames(idLiquid);
		forAll(liquidNames, j)
		{
			IOField<scalar> YLiquid
			(
				c.fieldIOobject
				(
					"Y" + liquidNames[j] + stateLabels[idLiquid],
					IOobject::NO_READ
				),
				np
			);

			label i = 0;
			forAllConstIter
			(
				typename Cloud<ReactingMultiphaseParcel<ParcelType>>,
				c,
				iter
			)
			{
				const ReactingMultiphaseParcel<ParcelType>& p0 = iter();
				YLiquid[i++] = p0.YLiquid()[j] * p0.Y()[LIQ];
			}

			YLiquid.write(np > 0);
		}

		const label idSolid = compModel.idSolid();
		const wordList& solidNames = compModel.componentNames(idSolid);
		forAll(solidNames, j)
		{
			IOField<scalar> YSolid
			(
				c.fieldIOobject
				(
					"Y" + solidNames[j] + stateLabels[idSolid],
					IOobject::NO_READ
				),
				np
			);

			label i = 0;
			forAllConstIter
			(
				typename Cloud<ReactingMultiphaseParcel<ParcelType>>,
				c,
				iter
			)
			{
				const ReactingMultiphaseParcel<ParcelType>& p0 = iter();
				YSolid[i++] = p0.YSolid()[j] * p0.Y()[SLD];
			}

			YSolid.write(np > 0);
		}
	}
}


// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

template<class ParcelType>
tnbLib::Ostream& tnbLib::operator<<
(
	Ostream& os,
	const ReactingMultiphaseParcel<ParcelType>& p
	)
{
	scalarField YGasLoc(p.YGas() * p.Y()[0]);
	scalarField YLiquidLoc(p.YLiquid() * p.Y()[1]);
	scalarField YSolidLoc(p.YSolid() * p.Y()[2]);
	if (os.format() == IOstream::ASCII)
	{
		os << static_cast<const ParcelType&>(p)
			<< token::SPACE << YGasLoc
			<< token::SPACE << YLiquidLoc
			<< token::SPACE << YSolidLoc;
	}
	else
	{
		os << static_cast<const ParcelType&>(p);
		os << YGasLoc << YLiquidLoc << YSolidLoc;
	}

	// Check state of Ostream
	os.check
	(
		"Ostream& operator<<"
		"("
		"Ostream&, "
		"const ReactingMultiphaseParcel<ParcelType>&"
		")"
	);

	return os;
}


// ************************************************************************* //

// .cxx
#include <mathematicalConstants.hxx>
#include <CompositionModel.hxx>  // added by amir

using namespace tnbLib::constant::mathematical;

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

template<class ParcelType>
const tnbLib::label tnbLib::ReactingMultiphaseParcel<ParcelType>::GAS(0);

template<class ParcelType>
const tnbLib::label tnbLib::ReactingMultiphaseParcel<ParcelType>::LIQ(1);

template<class ParcelType>
const tnbLib::label tnbLib::ReactingMultiphaseParcel<ParcelType>::SLD(2);


// * * * * * * * * * * * *  Private Member Functions * * * * * * * * * * * * //

template<class ParcelType>
template<class TrackCloudType>
tnbLib::scalar tnbLib::ReactingMultiphaseParcel<ParcelType>::CpEff
(
	TrackCloudType& cloud,
	trackingData& td,
	const scalar p,
	const scalar T,
	const label idG,
	const label idL,
	const label idS
) const
{
	return
		this->Y_[GAS] * cloud.composition().Cp(idG, YGas_, p, T)
		+ this->Y_[LIQ] * cloud.composition().Cp(idL, YLiquid_, p, T)
		+ this->Y_[SLD] * cloud.composition().Cp(idS, YSolid_, p, T);
}


template<class ParcelType>
template<class TrackCloudType>
tnbLib::scalar tnbLib::ReactingMultiphaseParcel<ParcelType>::HsEff
(
	TrackCloudType& cloud,
	trackingData& td,
	const scalar p,
	const scalar T,
	const label idG,
	const label idL,
	const label idS
) const
{
	return
		this->Y_[GAS] * cloud.composition().Hs(idG, YGas_, p, T)
		+ this->Y_[LIQ] * cloud.composition().Hs(idL, YLiquid_, p, T)
		+ this->Y_[SLD] * cloud.composition().Hs(idS, YSolid_, p, T);
}


template<class ParcelType>
template<class TrackCloudType>
tnbLib::scalar tnbLib::ReactingMultiphaseParcel<ParcelType>::LEff
(
	TrackCloudType& cloud,
	trackingData& td,
	const scalar p,
	const scalar T,
	const label idG,
	const label idL,
	const label idS
) const
{
	return
		this->Y_[GAS] * cloud.composition().L(idG, YGas_, p, T)
		+ this->Y_[LIQ] * cloud.composition().L(idL, YLiquid_, p, T)
		+ this->Y_[SLD] * cloud.composition().L(idS, YSolid_, p, T);
}


template<class ParcelType>
tnbLib::scalar tnbLib::ReactingMultiphaseParcel<ParcelType>::updateMassFractions
(
	const scalar mass0,
	const scalarField& dMassGas,
	const scalarField& dMassLiquid,
	const scalarField& dMassSolid
)
{
	scalarField& YMix = this->Y_;

	scalar massGas =
		this->updateMassFraction(mass0 * YMix[GAS], dMassGas, YGas_);
	scalar massLiquid =
		this->updateMassFraction(mass0 * YMix[LIQ], dMassLiquid, YLiquid_);
	scalar massSolid =
		this->updateMassFraction(mass0 * YMix[SLD], dMassSolid, YSolid_);

	scalar massNew = max(massGas + massLiquid + massSolid, rootVSmall);

	YMix[GAS] = massGas / massNew;
	YMix[LIQ] = massLiquid / massNew;
	YMix[SLD] = 1.0 - YMix[GAS] - YMix[LIQ];

	return massNew;
}


// * * * * * * * * * * *  Protected Member Functions * * * * * * * * * * * * //

template<class ParcelType>
template<class TrackCloudType>
void tnbLib::ReactingMultiphaseParcel<ParcelType>::setCellValues
(
	TrackCloudType& cloud,
	trackingData& td
)
{
	ParcelType::setCellValues(cloud, td);
}


template<class ParcelType>
template<class TrackCloudType>
void tnbLib::ReactingMultiphaseParcel<ParcelType>::cellValueSourceCorrection
(
	TrackCloudType& cloud,
	trackingData& td,
	const scalar dt
)
{
	// Re-use correction from reacting parcel
	ParcelType::cellValueSourceCorrection(cloud, td, dt);
}


template<class ParcelType>
template<class TrackCloudType>
void tnbLib::ReactingMultiphaseParcel<ParcelType>::calc
(
	TrackCloudType& cloud,
	trackingData& td,
	const scalar dt
)
{
	typedef typename TrackCloudType::reactingCloudType reactingCloudType;
	const CompositionModel<reactingCloudType>& composition =
		cloud.composition();


	// Define local properties at beginning of timestep
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	const scalar np0 = this->nParticle_;
	const scalar d0 = this->d_;
	const vector& U0 = this->U_;
	const scalar T0 = this->T_;
	const scalar mass0 = this->mass();

	const scalar pc = td.pc();

	const scalarField& YMix = this->Y_;
	const label idG = composition.idGas();
	const label idL = composition.idLiquid();
	const label idS = composition.idSolid();


	// Calc surface values
	scalar Ts, rhos, mus, Prs, kappas;
	this->calcSurfaceValues(cloud, td, T0, Ts, rhos, mus, Prs, kappas);
	scalar Res = this->Re(rhos, U0, td.Uc(), d0, mus);


	// Sources
	//~~~~~~~~

	// Explicit momentum source for particle
	vector Su = Zero;

	// Linearised momentum source coefficient
	scalar Spu = 0.0;

	// Momentum transfer from the particle to the carrier phase
	vector dUTrans = Zero;

	// Explicit enthalpy source for particle
	scalar Sh = 0.0;

	// Linearised enthalpy source coefficient
	scalar Sph = 0.0;

	// Sensible enthalpy transfer from the particle to the carrier phase
	scalar dhsTrans = 0.0;


	// 1. Compute models that contribute to mass transfer - U, T held constant
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	// Phase change in liquid phase
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	// Mass transfer due to phase change
	scalarField dMassPC(YLiquid_.size(), 0.0);

	// Molar flux of species emitted from the particle (kmol/m^2/s)
	scalar Ne = 0.0;

	// Sum Ni*Cpi*Wi of emission species
	scalar NCpW = 0.0;

	// Surface concentrations of emitted species
	scalarField Cs(composition.carrier().species().size(), 0.0);

	// Calc mass and enthalpy transfer due to phase change
	this->calcPhaseChange
	(
		cloud,
		td,
		dt,
		Res,
		Prs,
		Ts,
		mus / rhos,
		d0,
		T0,
		mass0,
		idL,
		YMix[LIQ],
		YLiquid_,
		dMassPC,
		Sh,
		Ne,
		NCpW,
		Cs
	);


	// Devolatilisation
	// ~~~~~~~~~~~~~~~~

	// Mass transfer due to devolatilisation
	scalarField dMassDV(YGas_.size(), 0.0);

	// Calc mass and enthalpy transfer due to devolatilisation
	calcDevolatilisation
	(
		cloud,
		td,
		dt,
		this->age_,
		Ts,
		d0,
		T0,
		mass0,
		this->mass0_,
		YMix[GAS] * YGas_,
		YMix[LIQ] * YLiquid_,
		YMix[SLD] * YSolid_,
		canCombust_,
		dMassDV,
		Sh,
		Ne,
		NCpW,
		Cs
	);


	// Surface reactions
	// ~~~~~~~~~~~~~~~~~

	// Change in carrier phase composition due to surface reactions
	scalarField dMassSRGas(YGas_.size(), 0.0);
	scalarField dMassSRLiquid(YLiquid_.size(), 0.0);
	scalarField dMassSRSolid(YSolid_.size(), 0.0);
	scalarField dMassSRCarrier(composition.carrier().species().size(), 0.0);

	// Calc mass and enthalpy transfer due to surface reactions
	calcSurfaceReactions
	(
		cloud,
		td,
		dt,
		d0,
		T0,
		mass0,
		canCombust_,
		Ne,
		YMix,
		YGas_,
		YLiquid_,
		YSolid_,
		dMassSRGas,
		dMassSRLiquid,
		dMassSRSolid,
		dMassSRCarrier,
		Sh,
		dhsTrans
	);


	// 2. Update the parcel properties due to change in mass
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	scalarField dMassGas(dMassDV + dMassSRGas);
	scalarField dMassLiquid(dMassPC + dMassSRLiquid);
	scalarField dMassSolid(dMassSRSolid);
	scalar mass1 =
		updateMassFractions(mass0, dMassGas, dMassLiquid, dMassSolid);

	this->Cp_ = CpEff(cloud, td, pc, T0, idG, idL, idS);

	// Update particle density or diameter
	if (cloud.constProps().constantVolume())
	{
		this->rho_ = mass1 / this->volume();
	}
	else
	{
		this->d_ = cbrt(mass1 / this->rho_ * 6.0 / pi);
	}

	// Remove the particle when mass falls below minimum threshold
	if (np0 * mass1 < cloud.constProps().minParcelMass())
	{
		td.keepParticle = false;

		if (cloud.solution().coupled())
		{
			scalar dm = np0 * mass0;

			// Absorb parcel into carrier phase
			forAll(YGas_, i)
			{
				label gid = composition.localToCarrierId(GAS, i);
				cloud.rhoTrans(gid)[this->cell()] += dm * YMix[GAS] * YGas_[i];
			}
			forAll(YLiquid_, i)
			{
				label gid = composition.localToCarrierId(LIQ, i);
				cloud.rhoTrans(gid)[this->cell()] += dm * YMix[LIQ] * YLiquid_[i];
			}

			// No mapping between solid components and carrier phase
			/*
			forAll(YSolid_, i)
			{
				label gid = composition.localToCarrierId(SLD, i);
				cloud.rhoTrans(gid)[this->cell()] += dm*YMix[SLD]*YSolid_[i];
			}
			*/

			cloud.UTrans()[this->cell()] += dm * U0;

			cloud.hsTrans()[this->cell()] +=
				dm * HsEff(cloud, td, pc, T0, idG, idL, idS);

			cloud.phaseChange().addToPhaseChangeMass(np0 * mass1);
		}

		return;
	}

	// Correct surface values due to emitted species
	this->correctSurfaceValues(cloud, td, Ts, Cs, rhos, mus, Prs, kappas);
	Res = this->Re(rhos, U0, td.Uc(), this->d_, mus);


	// 3. Compute heat- and momentum transfers
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	// Heat transfer
	// ~~~~~~~~~~~~~

	// Calculate new particle temperature
	this->T_ =
		this->calcHeatTransfer
		(
			cloud,
			td,
			dt,
			Res,
			Prs,
			kappas,
			NCpW,
			Sh,
			dhsTrans,
			Sph
		);


	this->Cp_ = CpEff(cloud, td, pc, this->T_, idG, idL, idS);


	// Motion
	// ~~~~~~

	// Calculate new particle velocity
	this->U_ =
		this->calcVelocity(cloud, td, dt, Res, mus, mass1, Su, dUTrans, Spu);


	// 4. Accumulate carrier phase source terms
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	if (cloud.solution().coupled())
	{
		// Transfer mass lost to carrier mass, momentum and enthalpy sources
		forAll(YGas_, i)
		{
			scalar dm = np0 * dMassGas[i];
			label gid = composition.localToCarrierId(GAS, i);
			scalar hs = composition.carrier().Hs(gid, pc, T0);
			cloud.rhoTrans(gid)[this->cell()] += dm;
			cloud.UTrans()[this->cell()] += dm * U0;
			cloud.hsTrans()[this->cell()] += dm * hs;
		}
		forAll(YLiquid_, i)
		{
			scalar dm = np0 * dMassLiquid[i];
			label gid = composition.localToCarrierId(LIQ, i);
			scalar hs = composition.carrier().Hs(gid, pc, T0);
			cloud.rhoTrans(gid)[this->cell()] += dm;
			cloud.UTrans()[this->cell()] += dm * U0;
			cloud.hsTrans()[this->cell()] += dm * hs;
		}

		// No mapping between solid components and carrier phase
		/*
		forAll(YSolid_, i)
		{
			scalar dm = np0*dMassSolid[i];
			label gid = composition.localToCarrierId(SLD, i);
			scalar hs = composition.carrier().Hs(gid, pc, T0);
			cloud.rhoTrans(gid)[this->cell()] += dm;
			cloud.UTrans()[this->cell()] += dm*U0;
			cloud.hsTrans()[this->cell()] += dm*hs;
		}
		*/

		forAll(dMassSRCarrier, i)
		{
			scalar dm = np0 * dMassSRCarrier[i];
			scalar hs = composition.carrier().Hs(i, pc, T0);
			cloud.rhoTrans(i)[this->cell()] += dm;
			cloud.UTrans()[this->cell()] += dm * U0;
			cloud.hsTrans()[this->cell()] += dm * hs;
		}

		// Update momentum transfer
		cloud.UTrans()[this->cell()] += np0 * dUTrans;
		cloud.UCoeff()[this->cell()] += np0 * Spu;

		// Update sensible enthalpy transfer
		cloud.hsTrans()[this->cell()] += np0 * dhsTrans;
		cloud.hsCoeff()[this->cell()] += np0 * Sph;

		// Update radiation fields
		if (cloud.radiation())
		{
			const scalar ap = this->areaP();
			const scalar T4 = pow4(T0);
			cloud.radAreaP()[this->cell()] += dt * np0 * ap;
			cloud.radT4()[this->cell()] += dt * np0 * T4;
			cloud.radAreaPT4()[this->cell()] += dt * np0 * ap * T4;
		}
	}
}


// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

template<class ParcelType>
template<class TrackCloudType>
void tnbLib::ReactingMultiphaseParcel<ParcelType>::calcDevolatilisation
(
	TrackCloudType& cloud,
	trackingData& td,
	const scalar dt,
	const scalar age,
	const scalar Ts,
	const scalar d,
	const scalar T,
	const scalar mass,
	const scalar mass0,
	const scalarField& YGasEff,
	const scalarField& YLiquidEff,
	const scalarField& YSolidEff,
	label& canCombust,
	scalarField& dMassDV,
	scalar& Sh,
	scalar& N,
	scalar& NCpW,
	scalarField& Cs
) const
{
	// Check that model is active
	if (!cloud.devolatilisation().active())
	{
		if (canCombust != -1)
		{
			canCombust = 1;
		}
		return;
	}

	// Initialise demand-driven constants
	(void)cloud.constProps().TDevol();
	(void)cloud.constProps().LDevol();

	// Check that the parcel temperature is within necessary limits for
	// devolatilisation to occur
	if (T < cloud.constProps().TDevol() || canCombust == -1)
	{
		return;
	}

	typedef typename TrackCloudType::reactingCloudType reactingCloudType;
	const CompositionModel<reactingCloudType>& composition =
		cloud.composition();


	// Total mass of volatiles evolved
	cloud.devolatilisation().calculate
	(
		dt,
		age,
		mass0,
		mass,
		T,
		YGasEff,
		YLiquidEff,
		YSolidEff,
		canCombust,
		dMassDV
	);

	scalar dMassTot = sum(dMassDV);

	cloud.devolatilisation().addToDevolatilisationMass
	(
		this->nParticle_ * dMassTot
	);

	Sh -= dMassTot * cloud.constProps().LDevol() / dt;

	// Update molar emissions
	if (cloud.heatTransfer().BirdCorrection())
	{
		// Molar average molecular weight of carrier mix
		const scalar Wc = max(small, td.rhoc() * RR * td.Tc() / td.pc());

		// Note: hardcoded gaseous diffusivities for now
		// TODO: add to carrier thermo
		const scalar beta = sqr(cbrt(15.0) + cbrt(15.0));

		forAll(dMassDV, i)
		{
			const label id = composition.localToCarrierId(GAS, i);
			const scalar Cp = composition.carrier().Cp(id, td.pc(), Ts);
			const scalar W = composition.carrier().Wi(id);
			const scalar Ni = dMassDV[i] / (this->areaS(d) * dt * W);

			// Dab calc'd using API vapour mass diffusivity function
			const scalar Dab =
				3.6059e-3 * (pow(1.8 * Ts, 1.75))
				* sqrt(1.0 / W + 1.0 / Wc)
				/ (td.pc() * beta);

			N += Ni;
			NCpW += Ni * Cp * W;
			Cs[id] += Ni * d / (2.0 * Dab);
		}
	}
}


template<class ParcelType>
template<class TrackCloudType>
void tnbLib::ReactingMultiphaseParcel<ParcelType>::calcSurfaceReactions
(
	TrackCloudType& cloud,
	trackingData& td,
	const scalar dt,
	const scalar d,
	const scalar T,
	const scalar mass,
	const label canCombust,
	const scalar N,
	const scalarField& YMix,
	const scalarField& YGas,
	const scalarField& YLiquid,
	const scalarField& YSolid,
	scalarField& dMassSRGas,
	scalarField& dMassSRLiquid,
	scalarField& dMassSRSolid,
	scalarField& dMassSRCarrier,
	scalar& Sh,
	scalar& dhsTrans
) const
{
	// Check that model is active
	if (!cloud.surfaceReaction().active())
	{
		return;
	}

	// Initialise demand-driven constants
	(void)cloud.constProps().hRetentionCoeff();
	(void)cloud.constProps().TMax();

	// Check that model is active
	if (canCombust != 1)
	{
		return;
	}


	// Update surface reactions
	const scalar hReaction = cloud.surfaceReaction().calculate
	(
		dt,
		this->cell(),
		d,
		T,
		td.Tc(),
		td.pc(),
		td.rhoc(),
		mass,
		YGas,
		YLiquid,
		YSolid,
		YMix,
		N,
		dMassSRGas,
		dMassSRLiquid,
		dMassSRSolid,
		dMassSRCarrier
	);

	cloud.surfaceReaction().addToSurfaceReactionMass
	(
		this->nParticle_
		* (sum(dMassSRGas) + sum(dMassSRLiquid) + sum(dMassSRSolid))
	);

	const scalar xsi = min(T / cloud.constProps().TMax(), 1.0);
	const scalar coeff =
		(1.0 - xsi * xsi) * cloud.constProps().hRetentionCoeff();

	Sh += coeff * hReaction / dt;

	dhsTrans += (1.0 - coeff) * hReaction;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class ParcelType>
tnbLib::ReactingMultiphaseParcel<ParcelType>::ReactingMultiphaseParcel
(
	const ReactingMultiphaseParcel<ParcelType>& p
)
	:
	ParcelType(p),
	YGas_(p.YGas_),
	YLiquid_(p.YLiquid_),
	YSolid_(p.YSolid_),
	canCombust_(p.canCombust_)
{}


template<class ParcelType>
tnbLib::ReactingMultiphaseParcel<ParcelType>::ReactingMultiphaseParcel
(
	const ReactingMultiphaseParcel<ParcelType>& p,
	const polyMesh& mesh
)
	:
	ParcelType(p, mesh),
	YGas_(p.YGas_),
	YLiquid_(p.YLiquid_),
	YSolid_(p.YSolid_),
	canCombust_(p.canCombust_)
{}


// * * * * * * * * * * * * * * IOStream operators  * * * * * * * * * * * * * //

//#include <ReactingMultiphaseParcelIO.cxx>

// ************************************************************************* //