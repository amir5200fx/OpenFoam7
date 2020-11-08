#pragma once
#ifndef _dynamicInkJetFvMesh_Header
#define _dynamicInkJetFvMesh_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2011-2019 OpenFOAM Foundation
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
	tnbLib::dynamicInkJetFvMesh

Description
	Mesh motion specifically for the "pumping" system of an ink-jet
	injector.

	The set of points in the "pumping" region are compressed and expanded
	sinusoidally to impose a sinusoidal variation of the flow at the
	nozzle exit.

SourceFiles
	dynamicInkJetFvMesh.C

\*---------------------------------------------------------------------------*/

#include <dynamicFvMesh.hxx>
#include <dictionary.hxx>
#include <pointIOField.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class dynamicInkJetFvMesh Declaration
	\*---------------------------------------------------------------------------*/

	class dynamicInkJetFvMesh
		:
		public dynamicFvMesh
	{
		// Private Data

		dictionary dynamicMeshCoeffs_;

		scalar amplitude_;
		scalar frequency_;
		scalar refPlaneX_;

		pointIOField stationaryPoints_;

		//- Optional list of vectorFields to update for mesh motion
		//  For modern solvers using Uf and correctPhi to update the flux
		//  after motion it is not necessary to specify a "velocityFields" list
		velocityMotionCorrection velocityMotionCorrection_;


	public:

		//- Runtime type information
		//TypeName("dynamicInkJetFvMesh");
		static const char* typeName_() { return "dynamicInkJetFvMesh"; }
		static FoamDynamicMesh_EXPORT const ::tnbLib::word typeName;
		static FoamDynamicMesh_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from IOobject
		FoamDynamicMesh_EXPORT dynamicInkJetFvMesh(const IOobject& io);

		//- Disallow default bitwise copy construction
		FoamDynamicMesh_EXPORT dynamicInkJetFvMesh(const dynamicInkJetFvMesh&) = delete;


		//- Destructor
		FoamDynamicMesh_EXPORT ~dynamicInkJetFvMesh();


		// Member Functions

			//- Update the mesh for both mesh motion and topology change
		FoamDynamicMesh_EXPORT virtual bool update();


		// Member Operators

			//- Disallow default bitwise assignment
		void operator=(const dynamicInkJetFvMesh&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_dynamicInkJetFvMesh_Header
