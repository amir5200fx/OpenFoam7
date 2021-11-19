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

Application
    pdfPlot

Description
    Generates a graph of a probability distribution function.

\*---------------------------------------------------------------------------*/

#include <includeAllModules.hxx>

#include <fvCFD.hxx>
#include <distributionModel.hxx>
#include <makeGraph.hxx>
#include <OFstream.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

using namespace tnbLib;;

int main(int argc, char* argv[])
{
#include <setRootCase.lxx>
#include <createTime.lxx>

#include "createFields.lxx"

    label iCheck = 100;
    for (label i = 1; i <= nSamples; i++)
    {
        scalar ps = p->sample();
        label n = label((ps - xMin) * nIntervals / (xMax - xMin));
        samples[n]++;

        if (writeData)
        {
            filePtr() << ps << nl;
        }

        if (i % iCheck == 0)
        {
            Info << "    processed " << i << " samples" << endl;

            if (i == 10 * iCheck)
            {
                iCheck *= 10;
            }
        }
    }

    scalarField x(nIntervals);

    forAll(x, i)
    {
        x[i] = xMin + i * (xMax - xMin) / (nIntervals - 1);
    }

    makeGraph(x, samples, p->type(), pdfPath, runTime.graphFormat());

    Info << "End\n" << endl;

    return 0;
}


// ************************************************************************* //
