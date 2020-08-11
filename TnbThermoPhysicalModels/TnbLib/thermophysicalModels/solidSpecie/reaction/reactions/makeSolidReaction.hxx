#pragma once
#ifndef _makeSolidReaction_Header
#define _makeSolidReaction_Header

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

InClass
	tnbLib::makeSolidReaction

Description
	Macros for instantiating reactions for solid

\*---------------------------------------------------------------------------*/

#include <SolidReaction.hxx>
#include <IrreversibleReaction.hxx>
#include <Reaction.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#define makeSolidReaction(ReactionType, Thermo, ReactionRate)                  \
                                                                               \
    typedef SolidReaction<Thermo> SolidReaction##Thermo;                       \
                                                                               \
    typedef Reaction<Thermo> Reaction##Thermo;                                 \
                                                                               \
    typedef ReactionType<SolidReaction, Thermo, ReactionRate>                  \
        ReactionType##Thermo##ReactionRate;                                    \
                                                                               \
    defineTemplateRunTimeSelectionTable(Reaction##Thermo, dictionary);         \
                                                                               \
    defineTemplateTypeNameAndDebug(SolidReaction##Thermo, 0);                  \
    defineTemplateTypeNameAndDebug(Reaction##Thermo, 0);                       \
                                                                               \
    template<>                                                                 \
    const word ReactionType##Thermo##ReactionRate::typeName                    \
    (                                                                          \
        ReactionType::typeName_()                                              \
      + ReactionRate::type()                                                   \
      + SolidReaction##Thermo::typeName_()                                     \
    );                                                                         \
                                                                               \
    addToRunTimeSelectionTable                                                 \
    (                                                                          \
        Reaction##Thermo,                                                      \
        ReactionType##Thermo##ReactionRate,                                    \
        dictionary                                                             \
    );

#define makeSolidIRReactions(Thermo, ReactionRate)                             \
                                                                               \
    makeSolidReaction(IrreversibleReaction, Thermo, ReactionRate)


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_makeSolidReaction_Header
