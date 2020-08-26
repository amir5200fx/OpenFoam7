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

inline const tnbLib::volScalarField&
tnbLib::radiationModels::radiativeIntensityRay::I() const
{
	return I_;
}


inline const tnbLib::volScalarField&
tnbLib::radiationModels::radiativeIntensityRay::qr() const
{
	return qr_;
}


inline tnbLib::volScalarField& tnbLib::radiationModels::radiativeIntensityRay::qr()
{
	return qr_;
}

inline const tnbLib::volScalarField& tnbLib::radiationModels::
radiativeIntensityRay::qin() const
{
	return qin_;
}


inline tnbLib::volScalarField& tnbLib::radiationModels::radiativeIntensityRay::qin()
{
	return qin_;
}


inline const tnbLib::volScalarField& tnbLib::radiationModels::
radiativeIntensityRay::qem() const
{
	return qem_;
}


inline tnbLib::volScalarField& tnbLib::radiationModels::radiativeIntensityRay::qem()
{
	return qem_;
}


inline const tnbLib::vector&
tnbLib::radiationModels::radiativeIntensityRay::d() const
{
	return d_;
}


inline const tnbLib::vector&
tnbLib::radiationModels::radiativeIntensityRay::dAve() const
{
	return dAve_;
}


inline tnbLib::scalar
tnbLib::radiationModels::radiativeIntensityRay::nLambda() const
{
	return nLambda_;
}


inline tnbLib::scalar tnbLib::radiationModels::radiativeIntensityRay::phi() const
{
	return phi_;
}


inline tnbLib::scalar tnbLib::radiationModels::radiativeIntensityRay::theta() const
{
	return theta_;
}


inline tnbLib::scalar tnbLib::radiationModels::radiativeIntensityRay::omega() const
{
	return omega_;
}


inline const tnbLib::volScalarField&
tnbLib::radiationModels::radiativeIntensityRay::ILambda
(
	const label lambdaI
) const
{
	return ILambda_[lambdaI];
}


// ************************************************************************* //
