#pragma once
/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2012-2018 OpenFOAM Foundation
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

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

inline const tnbLib::word&
tnbLib::fv::interRegionHeatTransferModel::nbrRegionName() const
{
	return nbrRegionName_;
}


inline const tnbLib::meshToMesh&
tnbLib::fv::interRegionHeatTransferModel::meshInterp() const
{
	if (!meshInterpPtr_.valid())
	{
		FatalErrorInFunction
			<< "Interpolation object not set"
			<< abort(FatalError);
	}

	return meshInterpPtr_();
}


inline const tnbLib::volScalarField&
tnbLib::fv::interRegionHeatTransferModel::htc() const
{
	return  htc_;
}


inline const tnbLib::fv::interRegionHeatTransferModel&
tnbLib::fv::interRegionHeatTransferModel::nbrModel() const
{
	if (nbrModel_ == nullptr)
	{
		FatalErrorInFunction
			<< "Neighbour model not set"
			<< abort(FatalError);
	}

	return *nbrModel_;
}


inline tnbLib::fv::interRegionHeatTransferModel&
tnbLib::fv::interRegionHeatTransferModel::nbrModel()
{
	if (nbrModel_ == nullptr)
	{
		FatalErrorInFunction
			<< "Neighbour model not set"
			<< abort(FatalError);
	}

	return *nbrModel_;
}


// ************************************************************************* //