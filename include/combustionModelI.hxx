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

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline const tnbLib::fvMesh& tnbLib::combustionModel::mesh() const
{
	return mesh_;
}


inline const tnbLib::compressibleTurbulenceModel&
tnbLib::combustionModel::turbulence() const
{
	return turb_;
}


inline const tnbLib::volScalarField& tnbLib::combustionModel::rho() const
{
	return turbulence().rho();
}


inline tnbLib::tmp<tnbLib::surfaceScalarField> tnbLib::combustionModel::phi() const
{
	return turbulence().alphaRhoPhi();
}


inline const tnbLib::dictionary& tnbLib::combustionModel::coeffs() const
{
	return coeffs_;
}

// ************************************************************************* //
