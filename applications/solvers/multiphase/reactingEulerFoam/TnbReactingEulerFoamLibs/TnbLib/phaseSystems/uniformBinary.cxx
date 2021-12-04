/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2017-2018 OpenFOAM Foundation
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

#include <uniformBinary.hxx>
#include <addToRunTimeSelectionTable.hxx>
#include <breakupModelMultiphase.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
    namespace diameterModels
    {
        namespace daughterSizeDistributionModels
        {
            defineTypeNameAndDebug(uniformBinary, 0);
            addToRunTimeSelectionTable
            (
                daughterSizeDistributionModel,
                uniformBinary,
                dictionary
            );
        }
    }
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::diameterModels::daughterSizeDistributionModels::uniformBinary::
uniformBinary
(
    const breakupModel& breakup,
    const dictionary& dict
)
    :
    daughterSizeDistributionModel(breakup, dict)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::diameterModels::daughterSizeDistributionModels::uniformBinary::
~uniformBinary()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::dimensionedScalar
tnbLib::diameterModels::daughterSizeDistributionModels::uniformBinary::calcNik
(
    const label i,
    const label k
) const
{
    const dimensionedScalar& xi = breakup_.popBal().sizeGroups()[i].x();
    const dimensionedScalar& xk = breakup_.popBal().sizeGroups()[k].x();
    const UPtrList<sizeGroup>& sizeGroups = breakup_.popBal().sizeGroups();

    if (i == 0)
    {
        return (sizeGroups[i + 1].x() - xi) / xk;
    }
    else if (i == k)
    {
        return (xi - sizeGroups[i - 1].x()) / xk;
    }
    else
    {
        return (sizeGroups[i + 1].x() - xi) / xk + (xi - sizeGroups[i - 1].x()) / xk;
    }
}


// ************************************************************************* //
