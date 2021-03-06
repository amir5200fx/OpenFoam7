#pragma once
#ifndef _singleRegionSolutionControl_Header
#define _singleRegionSolutionControl_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2018-2019 OpenFOAM Foundation
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
	tnbLib::singleRegionSolutionControl

Description
	Single-region-specific derivation of the solution control class

SourceFiles
	singleRegionSolutionControlI.H
	singleRegionSolutionControl.C
	singleRegionSolutionControlTemplates.C

\*---------------------------------------------------------------------------*/

#include <fvMesh.hxx>
#include <solutionControl.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							 Class singleRegionSolutionControl Declaration
	\*---------------------------------------------------------------------------*/

	class singleRegionSolutionControl
		:
		public solutionControl
	{
	protected:

		// Protected data

		//- Reference to the mesh
		fvMesh& mesh_;


		// Protected Member Functions

		//- Store previous iteration for fields
		template<class Type>
		void storePrevIterTypeFields() const;


	public:

		// Static Data Members

		//- Run-time type information
		//TypeName("singleRegionSolutionControl");
		static const char* typeName_() { return "singleRegionSolutionControl"; }
		static FoamFiniteVolume_EXPORT const ::tnbLib::word typeName;
		static FoamFiniteVolume_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

		//- Construct from a mesh and the name of the algorithm
		FoamFiniteVolume_EXPORT singleRegionSolutionControl(fvMesh& mesh, const word& algorithmName);


		//- Destructor
		FoamFiniteVolume_EXPORT virtual ~singleRegionSolutionControl();


		// Member Functions

		// Access

		//- Return the mesh
		inline const fvMesh& mesh() const;

		//- Return the mesh
		inline fvMesh& mesh();

		//- Return the solution dictionary
		FoamFiniteVolume_EXPORT virtual const dictionary& dict() const;

		//- Flag to indicate whether in final state
		FoamFiniteVolume_EXPORT virtual bool isFinal() const;


		// Evolution

		//- Update the mesh data for the final state
		FoamFiniteVolume_EXPORT void updateFinal() const;

		//- Store previous iteration for fields
		FoamFiniteVolume_EXPORT void storePrevIterFields();
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <singleRegionSolutionControlTemplatesI.hxx>

//#ifdef NoRepository
//#include <singleRegionSolutionControlTemplates.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <singleRegionSolutionControlI.hxx>

#endif // !_singleRegionSolutionControl_Header
