#pragma once
#ifndef _BasicChemistryModelTemplate_Header
#define _BasicChemistryModelTemplate_Header

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

Class
	tnbLib::BasicChemistryModel

Description
	Basic chemistry model templated on thermodynamics

SourceFiles
	BasicChemistryModelI.H
	BasicChemistryModel.C

\*---------------------------------------------------------------------------*/

#include <basicChemistryModel.hxx>
#include <autoPtr.hxx>
#include <runTimeSelectionTables.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of classes
	class fvMesh;

	/*---------------------------------------------------------------------------*\
						 class BasicChemistryModel Declaration
	\*---------------------------------------------------------------------------*/

	template<class ReactionThermo>
	class BasicChemistryModel
		:
		public basicChemistryModel
	{
	protected:

		// Protected data

			//- Thermo
		ReactionThermo& thermo_;


	public:

		//- Runtime type information
		TypeName("BasicChemistryModel");


		//- Thermo type
		typedef ReactionThermo reactionThermo;


		//- Declare run-time constructor selection tables
		declareRunTimeSelectionTable
		(
			autoPtr,
			BasicChemistryModel,
			thermo,
			(ReactionThermo& thermo),
			(thermo)
		);


		// Constructors

			//- Construct from thermo
		BasicChemistryModel(ReactionThermo& thermo);


		//- Selector
		static autoPtr<BasicChemistryModel<ReactionThermo>> New
		(
			ReactionThermo& thermo
		);


		//- Destructor
		virtual ~BasicChemistryModel();


		// Member Functions

			//- Return access to the thermo package
		inline ReactionThermo& thermo();

		//- Return const access to the thermo package
		inline const ReactionThermo& thermo() const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
#include <BasicChemistryModelTemplate.cxx>
#endif

#include <BasicChemistryModelTemplateI.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_BasicChemistryModelTemplate_Header
