#pragma once
/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2013-2018 OpenFOAM Foundation
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

template<class CloudType>
inline const tnbLib::MPPICCloud<CloudType>&
tnbLib::MPPICCloud<CloudType>::cloudCopy() const
{
	return cloudCopyPtr_();
}


template<class CloudType>
inline const tnbLib::PackingModel<tnbLib::MPPICCloud<CloudType>>&
tnbLib::MPPICCloud<CloudType>::packingModel() const
{
	return packingModel_();
}


template<class CloudType>
inline tnbLib::PackingModel<tnbLib::MPPICCloud<CloudType>>&
tnbLib::MPPICCloud<CloudType>::packingModel()
{
	return packingModel_();
}


template<class CloudType>
inline const tnbLib::DampingModel<tnbLib::MPPICCloud<CloudType>>&
tnbLib::MPPICCloud<CloudType>::dampingModel() const
{
	return dampingModel_();
}


template<class CloudType>
inline tnbLib::DampingModel<tnbLib::MPPICCloud<CloudType>>&
tnbLib::MPPICCloud<CloudType>::dampingModel()
{
	return dampingModel_();
}


template<class CloudType>
inline const tnbLib::IsotropyModel<tnbLib::MPPICCloud<CloudType>>&
tnbLib::MPPICCloud<CloudType>::isotropyModel() const
{
	return isotropyModel_();
}


template<class CloudType>
inline tnbLib::IsotropyModel<tnbLib::MPPICCloud<CloudType>>&
tnbLib::MPPICCloud<CloudType>::isotropyModel()
{
	return isotropyModel_();
}


// ************************************************************************* //
