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

#include <ignition.hxx>

#include <fvMesh.hxx>


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::ignition::igniting() const
{
    if (!ignite())
    {
        return false;
    }

    bool igning = false;

    forAll(ignSites_, i)
    {
        if (ignSites_[i].igniting())
        {
            igning = true;
        }
    }

    return igning;
}


bool tnbLib::ignition::ignited() const
{
    if (!ignite())
    {
        return false;
    }

    bool igned = false;

    forAll(ignSites_, i)
    {
        if (ignSites_[i].ignited())
        {
            igned = true;
        }
    }

    return igned;
}


// ************************************************************************* //
