#pragma once
/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2011-2019 OpenFOAM Foundation
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

inline const tnbLib::radiationModels::radiativeIntensityRay&
tnbLib::radiationModels::fvDOM::IRay(const label rayI) const
{
	return  IRay_[rayI];
}


inline const tnbLib::volScalarField&
tnbLib::radiationModels::fvDOM::IRayLambda
(
	const label rayI,
	const label lambdaI
) const
{
	return IRay_[rayI].ILambda(lambdaI);
}


inline tnbLib::label tnbLib::radiationModels::fvDOM::nTheta() const
{
	return nTheta_;
}


inline tnbLib::label tnbLib::radiationModels::fvDOM::nPhi() const
{
	return nPhi_;
}


inline tnbLib::label tnbLib::radiationModels::fvDOM::nRay() const
{
	return nRay_;
}


inline tnbLib::label tnbLib::radiationModels::fvDOM::nLambda() const
{
	return nLambda_;
}


inline const tnbLib::volScalarField& tnbLib::radiationModels::fvDOM::a() const
{
	return a_;
}


inline const tnbLib::volScalarField& tnbLib::radiationModels::fvDOM::aLambda
(
	const label lambdaI
) const
{
	return aLambda_[lambdaI];
}


inline const tnbLib::volScalarField& tnbLib::radiationModels::fvDOM::G() const
{
	return G_;
}


inline const tnbLib::volScalarField& tnbLib::radiationModels::fvDOM::qr() const
{
	return qr_;
}

inline const tnbLib::volScalarField& tnbLib::radiationModels::fvDOM::qin() const
{
	return qin_;
}


inline const tnbLib::volScalarField& tnbLib::radiationModels::fvDOM::qem() const
{
	return qem_;
}


inline const tnbLib::radiationModels::blackBodyEmission&
tnbLib::radiationModels::fvDOM::blackBody() const
{
	return blackBody_;
}


inline tnbLib::scalar tnbLib::radiationModels::fvDOM::omegaMax() const
{
	return omegaMax_;
}


// ************************************************************************* //
