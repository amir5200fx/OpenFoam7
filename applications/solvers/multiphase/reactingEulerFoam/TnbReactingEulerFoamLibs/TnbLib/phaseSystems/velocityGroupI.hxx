#pragma once
/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2017-2019 OpenFOAM Foundation
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

inline const tnbLib::word&
tnbLib::diameterModels::velocityGroup::popBalName() const
{
    return popBalName_;
}


inline const tnbLib::volScalarField&
tnbLib::diameterModels::velocityGroup::f() const
{
    return f_;
}


inline const tnbLib::dimensionedScalar&
tnbLib::diameterModels::velocityGroup::formFactor() const
{
    return formFactor_;
}


inline const tnbLib::PtrList<tnbLib::diameterModels::sizeGroup>&
tnbLib::diameterModels::velocityGroup::sizeGroups() const
{
    return sizeGroups_;
}


inline const tnbLib::tmp<tnbLib::fv::convectionScheme<tnbLib::scalar>>&
tnbLib::diameterModels::velocityGroup::mvConvection() const
{
    return mvConvection_;
}


inline const tnbLib::volScalarField& tnbLib::diameterModels::velocityGroup::
dmdt() const
{
    return dmdt_;
}


inline tnbLib::volScalarField& tnbLib::diameterModels::velocityGroup::dmdtRef()
{
    return dmdt_;
}


// ************************************************************************* //
