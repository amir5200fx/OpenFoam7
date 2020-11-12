
#ifndef _makeChemistryReductionMethods_Header
#define _makeChemistryReductionMethods_Header

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

\*---------------------------------------------------------------------------*/

#include <chemistryReductionMethod.hxx>

#include <noChemistryReduction.hxx>
#include <DAC.hxx>
#include <DRG.hxx>
#include <DRGEP.hxx>
#include <EFA.hxx>
#include <PFA.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#define makeChemistryReductionMethod(SS, Comp, Thermo)                         \
                                                                               \
    typedef chemistryReductionMethods::SS<Comp, Thermo>                        \
        chemistryReductionMethod##SS##Comp##Thermo;                            \
                                                                               \
    defineTemplateTypeNameAndDebugWithName                                     \
    (                                                                          \
        chemistryReductionMethod##SS##Comp##Thermo,                            \
        (#SS"<" + word(Comp::typeName_())                                      \
      + "," + Thermo::typeName() + ">").c_str(),                               \
        0                                                                      \
    );                                                                         \
                                                                               \
    chemistryReductionMethod<Comp, Thermo>::                                   \
        adddictionaryConstructorToTable                                        \
        <chemistryReductionMethod##SS##Comp##Thermo>                           \
        add##chemistryReductionMethods##SS##Comp##Thermo##ConstructorToTable_;


#define makeChemistryReductionMethods(CompChemModel, Thermo)                   \
                                                                               \
    typedef chemistryReductionMethod<CompChemModel, Thermo>                    \
        chemistryReductionMethod##CompChemModel##Thermo;                       \
                                                                               \
    defineTemplateTypeNameAndDebugWithName                                     \
    (                                                                          \
        chemistryReductionMethod##CompChemModel##Thermo,                       \
        (word(chemistryReductionMethod##CompChemModel##Thermo::typeName_()) +  \
        '<' + word(CompChemModel::typeName_()) + "," + Thermo::typeName() + '>'\
        ).c_str(),                                                             \
        0                                                                      \
    );                                                                         \
                                                                               \
    defineTemplateRunTimeSelectionTable                                        \
    (                                                                          \
        chemistryReductionMethod##CompChemModel##Thermo,                       \
        dictionary                                                             \
    );                                                                         \
                                                                               \
    makeChemistryReductionMethod                                               \
    (                                                                          \
        none,                                                                  \
        CompChemModel,                                                         \
        Thermo                                                                 \
    );                                                                         \
                                                                               \
    makeChemistryReductionMethod                                               \
    (                                                                          \
        DAC,                                                                   \
        CompChemModel,                                                         \
        Thermo                                                                 \
    );                                                                         \
                                                                               \
    makeChemistryReductionMethod                                               \
    (                                                                          \
        DRG,                                                                   \
        CompChemModel,                                                         \
        Thermo                                                                 \
    );                                                                         \
                                                                               \
    makeChemistryReductionMethod                                               \
    (                                                                          \
        DRGEP,                                                                 \
        CompChemModel,                                                         \
        Thermo                                                                 \
    );                                                                         \
                                                                               \
    makeChemistryReductionMethod                                               \
    (                                                                          \
        EFA,                                                                   \
        CompChemModel,                                                         \
        Thermo                                                                 \
    );                                                                         \
                                                                               \
    makeChemistryReductionMethod                                               \
    (                                                                          \
        PFA,                                                                   \
        CompChemModel,                                                         \
        Thermo                                                                 \
    );                                                                         \


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_makeChemistryReductionMethods_Header

// ************************************************************************* //
