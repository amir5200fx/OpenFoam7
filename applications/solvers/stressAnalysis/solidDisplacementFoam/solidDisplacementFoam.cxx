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
    solidDisplacementFoam

Description
    Transient segregated finite-volume solver of linear-elastic,
    small-strain deformation of a solid body, with optional thermal
    diffusion and thermal stresses.

    Simple linear elasticity structural analysis code.
    Solves for the displacement vector field D, also generating the
    stress tensor field sigma.

\*---------------------------------------------------------------------------*/

#include <includeAllModules.hxx>

#include <fvCFD.hxx>
#include <fvOptions.hxx>
#include <Switch.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

using namespace tnbLib;

int main(int argc, char* argv[])
{

    {
        /*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2016-2018 OpenFOAM Foundation
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

Global
    postProcess

Description
    Execute application functionObjects to post-process existing results.

    If the "dict" argument is specified the functionObjectList is constructed
    from that dictionary otherwise the functionObjectList is constructed from
    the "functions" sub-dictionary of "system/controlDict"

    Multiple time-steps may be processed and the standard utility time
    controls are provided.

\*---------------------------------------------------------------------------*/

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifndef CREATE_TIME
#define CREATE_TIME createTime.lxx
#endif

#ifndef CREATE_MESH
#define CREATE_MESH createMesh.lxx
#endif

#ifndef CREATE_FIELDS
#define CREATE_FIELDS createFields.lxx
#endif

#ifndef CREATE_CONTROL
#define CREATE_CONTROL createControl.lxx
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#define INCLUDE_FILE(X) INCLUDE_FILE2(X)
#define INCLUDE_FILE2(X) #X

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

        tnbLib::argList::addBoolOption
        (
            argList::postProcessOptionName,
            "Execute functionObjects only"
        );

        if (argList::postProcess(argc, argv))
        {
            tnbLib::timeSelector::addOptions();
#include <addRegionOption.lxx>
#include <addFunctionObjectOptions.lxx>

            // Set functionObject post-processing mode
            functionObject::postProcess = true;

#include <setRootCase.lxx>

            if (args.optionFound("list"))
            {
                functionObjectList::list();
                return 0;
            }

#include INCLUDE_FILE(CREATE_TIME)
            tnbLib::instantList timeDirs = tnbLib::timeSelector::select0(runTime, args);
#include INCLUDE_FILE(CREATE_MESH)

#ifndef NO_CONTROL
#include INCLUDE_FILE(CREATE_CONTROL)
#endif

            forAll(timeDirs, timei)
            {
                runTime.setTime(timeDirs[timei], timei);

                Info << "Time = " << runTime.timeName() << endl;

                FatalIOError.throwExceptions();

                try
                {
#include INCLUDE_FILE(CREATE_FIELDS)

#ifdef CREATE_FIELDS_2
#include INCLUDE_FILE(CREATE_FIELDS_2)
#endif

#ifdef CREATE_FIELDS_3
#include INCLUDE_FILE(CREATE_FIELDS_3)
#endif

                    // Externally stored dictionary for functionObjectList
                    // if not constructed from runTime
                    dictionary functionsControlDict("controlDict");

                    HashSet<word> selectedFields;

                    // Construct functionObjectList
                    autoPtr<functionObjectList> functionsPtr
                    (
                        functionObjectList::New
                        (
                            args,
                            runTime,
                            functionsControlDict,
                            selectedFields
                        )
                    );

                    functionsPtr->execute();
                }
                catch (IOerror& err)
                {
                    Warning << err << endl;
                }

                // Clear the objects owned by the mesh
                mesh.objectRegistry::clear();

                Info << endl;
            }

            Info << "End\n" << endl;

            return 0;
        }


        // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#undef INCLUDE_FILE
#undef INCLUDE_FILE2

#undef CREATE_MESH
#undef CREATE_FIELDS
#undef CREATE_CONTROL

// ************************************************************************* //

    }
//#include <postProcess.lxx>

#include <setRootCaseLists.lxx>
#include <createTime.lxx>
#include <createMesh.lxx>

#include "createControls.lxx"
#include "createFields.lxx"

    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    Info << "\nCalculating displacement field\n" << endl;

    while (runTime.loop())
    {
        Info << "Iteration: " << runTime.value() << nl << endl;

#include "readSolidDisplacementFoamControls.lxx"

        int iCorr = 0;
        scalar initialResidual = 0;

        do
        {
            if (thermalStress)
            {
                volScalarField& T = Tptr();
                fvScalarMatrix TEqn
                (
                    fvm::ddt(T) == fvm::laplacian(DT, T) + fvOptions(T)
                );

                fvOptions.constrain(TEqn);

                TEqn.solve();

                fvOptions.correct(T);
            }

            {
                fvVectorMatrix DEqn
                (
                    fvm::d2dt2(D)
                    ==
                    fvm::laplacian(2 * mu + lambda, D, "laplacian(DD,D)")
                    + divSigmaExp
                    + fvOptions.d2dt2(D)
                );

                if (thermalStress)
                {
                    const volScalarField& T = Tptr();
                    DEqn += fvc::grad(threeKalpha * T);
                }

                fvOptions.constrain(DEqn);

                initialResidual = DEqn.solve().max().initialResidual();

                if (!compactNormalStress)
                {
                    divSigmaExp = fvc::div(DEqn.flux());
                }
            }

            {
                volTensorField gradD(fvc::grad(D));
                sigmaD = mu * twoSymm(gradD) + (lambda * I) * tr(gradD);

                if (compactNormalStress)
                {
                    divSigmaExp = fvc::div
                    (
                        sigmaD - (2 * mu + lambda) * gradD,
                        "div(sigmaD)"
                    );
                }
                else
                {
                    divSigmaExp += fvc::div(sigmaD);
                }
            }

        } while (initialResidual > convergenceTolerance && ++iCorr < nCorr);

#include "calculateStress.lxx"

        Info << "ExecutionTime = " << runTime.elapsedCpuTime() << " s"
            << "  ClockTime = " << runTime.elapsedClockTime() << " s"
            << nl << endl;
    }

    Info << "End\n" << endl;

    return 0;
}


// ************************************************************************* //
