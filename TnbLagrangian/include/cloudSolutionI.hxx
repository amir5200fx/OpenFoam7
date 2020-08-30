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

inline const tnbLib::fvMesh& tnbLib::cloudSolution::mesh() const
{
	return mesh_;
}


inline const tnbLib::dictionary& tnbLib::cloudSolution::dict() const
{
	return dict_;
}


inline const tnbLib::Switch tnbLib::cloudSolution::active() const
{
	return active_;
}


inline const tnbLib::dictionary& tnbLib::cloudSolution::sourceTermDict() const
{
	return dict_.subDict("sourceTerms");
}


inline const tnbLib::dictionary& tnbLib::cloudSolution::interpolationSchemes() const
{
	return dict_.subDict("interpolationSchemes");
}


inline const tnbLib::dictionary& tnbLib::cloudSolution::integrationSchemes() const
{
	return dict_.subDict("integrationSchemes");
}


inline const tnbLib::Switch tnbLib::cloudSolution::transient() const
{
	return transient_;
}


inline const tnbLib::Switch tnbLib::cloudSolution::steadyState() const
{
	return !transient_;
}


inline tnbLib::label tnbLib::cloudSolution::calcFrequency() const
{
	return calcFrequency_;
}


inline tnbLib::scalar tnbLib::cloudSolution::maxCo() const
{
	return maxCo_;
}


inline tnbLib::label tnbLib::cloudSolution::iter() const
{
	return iter_;
}


inline tnbLib::label tnbLib::cloudSolution::nextIter()
{
	return ++iter_;
}


inline tnbLib::scalar tnbLib::cloudSolution::trackTime() const
{
	return trackTime_;
}


inline tnbLib::Switch& tnbLib::cloudSolution::coupled()
{
	return coupled_;
}


inline const tnbLib::Switch tnbLib::cloudSolution::coupled() const
{
	return coupled_;
}


inline const tnbLib::Switch tnbLib::cloudSolution::cellValueSourceCorrection() const
{
	return cellValueSourceCorrection_;
}


inline tnbLib::scalar tnbLib::cloudSolution::maxTrackTime() const
{
	return maxTrackTime_;
}


inline const tnbLib::Switch tnbLib::cloudSolution::resetSourcesOnStartup() const
{
	return resetSourcesOnStartup_;
}


// ************************************************************************* //
