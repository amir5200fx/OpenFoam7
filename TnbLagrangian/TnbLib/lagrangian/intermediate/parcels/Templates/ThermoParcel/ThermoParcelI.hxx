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
inline tnbLib::ThermoParcel<ParcelType>::constantProperties::constantProperties()
	:
	ParcelType::constantProperties(),
	T0_(this->dict_, 0.0),
	TMin_(this->dict_, 0.0),
	TMax_(this->dict_, vGreat),
	Cp0_(this->dict_, 0.0),
	epsilon0_(this->dict_, 0.0),
	f0_(this->dict_, 0.0)
{}


template<class ParcelType>
inline tnbLib::ThermoParcel<ParcelType>::constantProperties::constantProperties
(
	const constantProperties& cp
)
	:
	ParcelType::constantProperties(cp),
	T0_(cp.T0_),
	TMin_(cp.TMin_),
	TMax_(cp.TMax_),
	Cp0_(cp.Cp0_),
	epsilon0_(cp.epsilon0_),
	f0_(cp.f0_)
{}


template<class ParcelType>
inline tnbLib::ThermoParcel<ParcelType>::constantProperties::constantProperties
(
	const dictionary& parentDict
)
	:
	ParcelType::constantProperties(parentDict),
	T0_(this->dict_, "T0"),
	TMin_(this->dict_, "TMin", 200.0),
	TMax_(this->dict_, "TMax", 5000.0),
	Cp0_(this->dict_, "Cp0"),
	epsilon0_(this->dict_, "epsilon0"),
	f0_(this->dict_, "f0")
{}


template<class ParcelType>
inline tnbLib::ThermoParcel<ParcelType>::ThermoParcel
(
	const polyMesh& mesh,
	const barycentric& coordinates,
	const label celli,
	const label tetFacei,
	const label tetPti
)
	:
	ParcelType(mesh, coordinates, celli, tetFacei, tetPti),
	T_(0.0),
	Cp_(0.0)
{}


template<class ParcelType>
inline tnbLib::ThermoParcel<ParcelType>::ThermoParcel
(
	const polyMesh& mesh,
	const vector& position,
	const label celli
)
	:
	ParcelType(mesh, position, celli),
	T_(0.0),
	Cp_(0.0)
{}


template<class ParcelType>
inline tnbLib::ThermoParcel<ParcelType>::ThermoParcel
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
		constProps
	),
	T_(constProps.T0()),
	Cp_(constProps.Cp0())
{}


// * * * * * * * * * constantProperties Member Functions * * * * * * * * * * //

template<class ParcelType>
inline tnbLib::scalar
tnbLib::ThermoParcel<ParcelType>::constantProperties::T0() const
{
	return T0_.value();
}


template<class ParcelType>
inline tnbLib::scalar
tnbLib::ThermoParcel<ParcelType>::constantProperties::TMin() const
{
	return TMin_.value();
}


template<class ParcelType>
inline tnbLib::scalar
tnbLib::ThermoParcel<ParcelType>::constantProperties::TMax() const
{
	return TMax_.value();
}


template<class ParcelType>
inline void
tnbLib::ThermoParcel<ParcelType>::constantProperties::setTMax(const scalar TMax)
{
	TMax_.setValue(TMax);
}


template<class ParcelType>
inline tnbLib::scalar
tnbLib::ThermoParcel<ParcelType>::constantProperties::Cp0() const
{
	return Cp0_.value();
}


template<class ParcelType>
inline tnbLib::scalar
tnbLib::ThermoParcel<ParcelType>::constantProperties::epsilon0() const
{
	return epsilon0_.value();
}


template<class ParcelType>
inline tnbLib::scalar
tnbLib::ThermoParcel<ParcelType>::constantProperties::f0() const
{
	return f0_.value();
}


// * * * * * * * * * * ThermoParcel Member Functions * * * * * * * * * * * * //

template<class ParcelType>
inline tnbLib::scalar tnbLib::ThermoParcel<ParcelType>::T() const
{
	return T_;
}


template<class ParcelType>
inline tnbLib::scalar tnbLib::ThermoParcel<ParcelType>::Cp() const
{
	return Cp_;
}


template<class ParcelType>
inline tnbLib::scalar tnbLib::ThermoParcel<ParcelType>::hs() const
{
	return Cp_ * (T_ - 298.15);
}


template<class ParcelType>
inline tnbLib::scalar& tnbLib::ThermoParcel<ParcelType>::T()
{
	return T_;
}


template<class ParcelType>
inline tnbLib::scalar& tnbLib::ThermoParcel<ParcelType>::Cp()
{
	return Cp_;
}


// ************************************************************************* //

// IO.cxx
#include <IOstreams.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

template<class ParcelType>
tnbLib::string tnbLib::ThermoParcel<ParcelType>::propertyList_ =
tnbLib::ThermoParcel<ParcelType>::propertyList();

template<class ParcelType>
const std::size_t tnbLib::ThermoParcel<ParcelType>::sizeofFields_
(
	sizeof(ThermoParcel<ParcelType>)
	- offsetof(ThermoParcel<ParcelType>, T_)
);


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class ParcelType>
tnbLib::ThermoParcel<ParcelType>::ThermoParcel
(
	const polyMesh& mesh,
	Istream& is,
	bool readFields
)
	:
	ParcelType(mesh, is, readFields),
	T_(0.0),
	Cp_(0.0)
{
	if (readFields)
	{
		if (is.format() == IOstream::ASCII)
		{
			T_ = readScalar(is);
			Cp_ = readScalar(is);
		}
		else
		{
			is.read(reinterpret_cast<char*>(&T_), sizeofFields_);
		}
	}

	// Check state of Istream
	is.check
	(
		"ThermoParcel::ThermoParcel(const polyMesh&, Istream&, bool)"
	);
}


template<class ParcelType>
template<class CloudType>
void tnbLib::ThermoParcel<ParcelType>::readFields(CloudType& c)
{
	bool valid = c.size();

	ParcelType::readFields(c);

	IOField<scalar> T(c.fieldIOobject("T", IOobject::MUST_READ), valid);
	c.checkFieldIOobject(c, T);

	IOField<scalar> Cp(c.fieldIOobject("Cp", IOobject::MUST_READ), valid);
	c.checkFieldIOobject(c, Cp);


	label i = 0;
	forAllIter(typename Cloud<ThermoParcel<ParcelType>>, c, iter)
	{
		ThermoParcel<ParcelType>& p = iter();

		p.T_ = T[i];
		p.Cp_ = Cp[i];
		i++;
	}
}


template<class ParcelType>
template<class CloudType>
void tnbLib::ThermoParcel<ParcelType>::writeFields(const CloudType& c)
{
	ParcelType::writeFields(c);

	label np = c.size();

	IOField<scalar> T(c.fieldIOobject("T", IOobject::NO_READ), np);
	IOField<scalar> Cp(c.fieldIOobject("Cp", IOobject::NO_READ), np);

	label i = 0;
	forAllConstIter(typename Cloud<ThermoParcel<ParcelType>>, c, iter)
	{
		const ThermoParcel<ParcelType>& p = iter();

		T[i] = p.T_;
		Cp[i] = p.Cp_;
		i++;
	}

	T.write(np > 0);
	Cp.write(np > 0);
}


// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

template<class ParcelType>
tnbLib::Ostream& tnbLib::operator<<
(
	Ostream& os,
	const ThermoParcel<ParcelType>& p
	)
{
	if (os.format() == IOstream::ASCII)
	{
		os << static_cast<const ParcelType&>(p)
			<< token::SPACE << p.T()
			<< token::SPACE << p.Cp();
	}
	else
	{
		os << static_cast<const ParcelType&>(p);
		os.write
		(
			reinterpret_cast<const char*>(&p.T_),
			ThermoParcel<ParcelType>::sizeofFields_
		);
	}

	// Check state of Ostream
	os.check
	(
		"Ostream& operator<<(Ostream&, const ThermoParcel<ParcelType>&)"
	);

	return os;
}


// ************************************************************************* //

// .cxx
#include <physicoChemicalConstants.hxx>

using namespace tnbLib::constant;

// * * * * * * * * * * *  Protected Member Functions * * * * * * * * * * * * //

template<class ParcelType>
template<class TrackCloudType>
void tnbLib::ThermoParcel<ParcelType>::setCellValues
(
	TrackCloudType& cloud,
	trackingData& td
)
{
	ParcelType::setCellValues(cloud, td);

	tetIndices tetIs = this->currentTetIndices();

	td.Cpc() = td.CpInterp().interpolate(this->coordinates(), tetIs);

	td.Tc() = td.TInterp().interpolate(this->coordinates(), tetIs);

	if (td.Tc() < cloud.constProps().TMin())
	{
		if (debug)
		{
			WarningInFunction
				<< "Limiting observed temperature in cell " << this->cell()
				<< " to " << cloud.constProps().TMin() << nl << endl;
		}

		td.Tc() = cloud.constProps().TMin();
	}
}


template<class ParcelType>
template<class TrackCloudType>
void tnbLib::ThermoParcel<ParcelType>::cellValueSourceCorrection
(
	TrackCloudType& cloud,
	trackingData& td,
	const scalar dt
)
{
	td.Uc() += cloud.UTrans()[this->cell()] / this->massCell(td);

	const scalar CpMean = td.CpInterp().psi()[this->cell()];
	td.Tc() += cloud.hsTrans()[this->cell()] / (CpMean * this->massCell(td));

	if (td.Tc() < cloud.constProps().TMin())
	{
		if (debug)
		{
			WarningInFunction
				<< "Limiting observed temperature in cell " << this->cell()
				<< " to " << cloud.constProps().TMin() << nl << endl;
		}

		td.Tc() = cloud.constProps().TMin();
	}
}


template<class ParcelType>
template<class TrackCloudType>
void tnbLib::ThermoParcel<ParcelType>::calcSurfaceValues
(
	TrackCloudType& cloud,
	trackingData& td,
	const scalar T,
	scalar& Ts,
	scalar& rhos,
	scalar& mus,
	scalar& Pr,
	scalar& kappas
) const
{
	// Surface temperature using two thirds rule
	Ts = (2.0 * T + td.Tc()) / 3.0;

	if (Ts < cloud.constProps().TMin())
	{
		if (debug)
		{
			WarningInFunction
				<< "Limiting parcel surface temperature to "
				<< cloud.constProps().TMin() << nl << endl;
		}

		Ts = cloud.constProps().TMin();
	}

	// Assuming thermo props vary linearly with T for small d(T)
	const scalar TRatio = td.Tc() / Ts;

	rhos = td.rhoc() * TRatio;

	tetIndices tetIs = this->currentTetIndices();
	mus = td.muInterp().interpolate(this->coordinates(), tetIs) / TRatio;
	kappas = td.kappaInterp().interpolate(this->coordinates(), tetIs) / TRatio;

	Pr = td.Cpc() * mus / kappas;
	Pr = max(rootVSmall, Pr);
}


template<class ParcelType>
template<class TrackCloudType>
void tnbLib::ThermoParcel<ParcelType>::calc
(
	TrackCloudType& cloud,
	trackingData& td,
	const scalar dt
)
{
	// Define local properties at beginning of time step
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	const scalar np0 = this->nParticle_;
	const scalar mass0 = this->mass();

	// Store T for consistent radiation source
	const scalar T0 = this->T_;


	// Calc surface values
	// ~~~~~~~~~~~~~~~~~~~
	scalar Ts, rhos, mus, Pr, kappas;
	calcSurfaceValues(cloud, td, this->T_, Ts, rhos, mus, Pr, kappas);

	// Reynolds number
	scalar Re = this->Re(rhos, this->U_, td.Uc(), this->d_, mus);


	// Sources
	// ~~~~~~~

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


	// Heat transfer
	// ~~~~~~~~~~~~~

	// Sum Ni*Cpi*Wi of emission species
	scalar NCpW = 0.0;

	// Calculate new particle temperature
	this->T_ =
		this->calcHeatTransfer
		(
			cloud,
			td,
			dt,
			Re,
			Pr,
			kappas,
			NCpW,
			Sh,
			dhsTrans,
			Sph
		);


	// Motion
	// ~~~~~~

	// Calculate new particle velocity
	this->U_ =
		this->calcVelocity(cloud, td, dt, Re, mus, mass0, Su, dUTrans, Spu);


	//  Accumulate carrier phase source terms
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	if (cloud.solution().coupled())
	{
		// Update momentum transfer
		cloud.UTrans()[this->cell()] += np0 * dUTrans;

		// Update momentum transfer coefficient
		cloud.UCoeff()[this->cell()] += np0 * Spu;

		// Update sensible enthalpy transfer
		cloud.hsTrans()[this->cell()] += np0 * dhsTrans;

		// Update sensible enthalpy coefficient
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


template<class ParcelType>
template<class TrackCloudType>
tnbLib::scalar tnbLib::ThermoParcel<ParcelType>::calcHeatTransfer
(
	TrackCloudType& cloud,
	trackingData& td,
	const scalar dt,
	const scalar Re,
	const scalar Pr,
	const scalar kappa,
	const scalar NCpW,
	const scalar Sh,
	scalar& dhsTrans,
	scalar& Sph
)
{
	if (!cloud.heatTransfer().active())
	{
		return T_;
	}

	const scalar d = this->d();
	const scalar rho = this->rho();
	const scalar As = this->areaS(d);
	const scalar V = this->volume(d);
	const scalar m = rho * V;

	// Calc heat transfer coefficient
	scalar htc = cloud.heatTransfer().htc(d, Re, Pr, kappa, NCpW);

	// Calculate the integration coefficients
	const scalar bcp = htc * As / (m * Cp_);
	const scalar acp = bcp * td.Tc();
	scalar ancp = Sh;
	if (cloud.radiation())
	{
		const tetIndices tetIs = this->currentTetIndices();
		const scalar Gc = td.GInterp().interpolate(this->coordinates(), tetIs);
		const scalar sigma = physicoChemical::sigma.value();
		const scalar epsilon = cloud.constProps().epsilon0();

		ancp += As * epsilon * (Gc / 4.0 - sigma * pow4(T_));
	}
	ancp /= m * Cp_;

	// Integrate to find the new parcel temperature
	const scalar deltaT = cloud.TIntegrator().delta(T_, dt, acp + ancp, bcp);
	const scalar deltaTncp = ancp * dt;
	const scalar deltaTcp = deltaT - deltaTncp;

	// Calculate the new temperature and the enthalpy transfer terms
	scalar Tnew = T_ + deltaT;
	Tnew = min(max(Tnew, cloud.constProps().TMin()), cloud.constProps().TMax());

	dhsTrans -= m * Cp_ * deltaTcp;

	Sph = dt * m * Cp_ * bcp;

	return Tnew;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class ParcelType>
tnbLib::ThermoParcel<ParcelType>::ThermoParcel
(
	const ThermoParcel<ParcelType>& p
)
	:
	ParcelType(p),
	T_(p.T_),
	Cp_(p.Cp_)
{}


template<class ParcelType>
tnbLib::ThermoParcel<ParcelType>::ThermoParcel
(
	const ThermoParcel<ParcelType>& p,
	const polyMesh& mesh
)
	:
	ParcelType(p, mesh),
	T_(p.T_),
	Cp_(p.Cp_)
{}


// * * * * * * * * * * * * * * IOStream operators  * * * * * * * * * * * * * //

//#include <ThermoParcelIO.cxx>

// ************************************************************************* //