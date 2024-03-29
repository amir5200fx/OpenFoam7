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
    noise

Description
    Utility to perform noise analysis of pressure data using the noiseFFT
    library.

    Control settings are read from the $FOAM_CASE/system/noiseDict dictionary,
    or user-specified dictionary using the -dict option.  Pressure data is
    read using a CSV reader:

Usage
    \verbatim
    pRef        101325;
    N           65536;
    nw          100;
    f1          25;
    fU          10000;
    graphFormat raw;

    pressureData
    {
        file                "pressureData";
        nHeaderLine         1;          // number of header lines
        refColumn           0;          // reference column index
        componentColumns    (1);        // component column indices
        separator           " ";        // optional (defaults to ",")
        mergeSeparators     no;         // merge multiple separators
        outOfBounds         clamp;      // optional out-of-bounds handling
        interpolationScheme linear;     // optional interpolation scheme
    }
    \endverbatim

    where
    \table
        Property    | Description                   | Required  | Default value
        pRef        | Reference pressure            | no        | 0
        N           | Number of samples in sampling window | no | 65536
        nw          | Number of sampling windows    | no        | 100
        fl          | Lower frequency band          | no        | 25
        fU          | Upper frequency band          | no        | 10000
        graphFormat | Output graph format          | no        | raw
    \endtable

    Current graph outputs include:
    - FFT of the pressure data
    - narrow-band PFL (pressure-fluctuation level) spectrum
    - one-third-octave-band PFL spectrum
    - one-third-octave-band pressure spectrum

See also
    CSV.H
    noiseFFT.H

\*---------------------------------------------------------------------------*/

#include <includeAllModules.hxx>

#include <noiseFFT.hxx>
#include <argList.hxx>
#include <Time.hxx>
#include <CSV.hxx>
#include <IOdictionary.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

using namespace tnbLib;

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

tnbLib::scalar checkUniformTimeStep(const scalarField& t)
{
    // check that a uniform time step has been applied
    scalar deltaT = -1.0;
    if (t.size() > 1)
    {
        for (label i = 1; i < t.size(); i++)
        {
            scalar dT = t[i] - t[i - 1];
            if (deltaT < 0)
            {
                deltaT = dT;
            }

            if (mag(deltaT - dT) > small)
            {
                FatalErrorInFunction
                    << "Unable to process data with a variable time step"
                    << exit(FatalError);
            }
        }
    }
    else
    {
        FatalErrorInFunction
            << "Unable to create FFT with a single value"
            << exit(FatalError);
    }

    return deltaT;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char* argv[])
{
    argList::noParallel();
#include <addDictOption.lxx>
#include <setRootCase.lxx>
#include <createTime.lxx>

//#include "createFields.lxx"

	word dictName("noiseDict");
	if (args.optionFound("dict"))
	{
		dictName = args["dict"];
	}

	IOdictionary dict
	(
		IOobject
		(
			dictName,
			runTime.system(),
			runTime,
			IOobject::MUST_READ
		)
	);

	// reference pressure
	scalar pRef = dict.lookupOrDefault("pRef", 0.0);

	// number of samples in sampling window
	label N = dict.lookupOrDefault("N", 65536);

	// number of sampling windows
	label nw = dict.lookupOrDefault("nw", 100);

	// lower frequency of frequency band
	scalar f1 = dict.lookupOrDefault("f1", 25.0);

	// upper frequency of frequency band
	scalar fU = dict.lookupOrDefault("fU", 10000.0);

	// graph format
	word graphFormat = dict.lookupOrDefault<word>("graphFormat", "raw");

    Info << "Reading data file" << endl;
    FieldFunction1<Function1Types::CSV<scalar>> pData
    (
        "pressure",
        dict.subDict("pressureData")
    );

    // time history data
    const scalarField t(pData.x());

    // pressure data
    const scalarField p(pData.y());

    if (t.size() < N)
    {
        FatalErrorInFunction
            << "Block size N = " << N
            << " is larger than number of data = " << t.size()
            << exit(FatalError);
    }

    Info << "    read " << t.size() << " values" << nl << endl;


    Info << "Creating noise FFT" << endl;
    noiseFFT nfft(checkUniformTimeStep(t), p);

    nfft -= pRef;

    fileName baseFileName(pData.fName().lessExt());

    graph Pf(nfft.RMSmeanPf(N, min(nfft.size() / N, nw)));
    Info << "    Creating graph for " << Pf.title() << endl;
    Pf.write(baseFileName + graph::wordify(Pf.title()), graphFormat);

    graph Lf(nfft.Lf(Pf));
    Info << "    Creating graph for " << Lf.title() << endl;
    Lf.write(baseFileName + graph::wordify(Lf.title()), graphFormat);

    graph Ldelta(nfft.Ldelta(Lf, f1, fU));
    Info << "    Creating graph for " << Ldelta.title() << endl;
    Ldelta.write(baseFileName + graph::wordify(Ldelta.title()), graphFormat);

    graph Pdelta(nfft.Pdelta(Pf, f1, fU));
    Info << "    Creating graph for " << Pdelta.title() << endl;
    Pdelta.write(baseFileName + graph::wordify(Pdelta.title()), graphFormat);

    Info << nl << "End\n" << endl;

    return 0;
}


// ************************************************************************* //
