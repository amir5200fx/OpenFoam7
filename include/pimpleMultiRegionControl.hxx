#pragma once
#ifndef _pimpleMultiRegionControl_Header
#define _pimpleMultiRegionControl_Header

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
	tnbLib::pimpleMultiRegionControl

Description
	Pimple multi-region control class. As tnbLib::pimpleControl, but for a multi-
	region simulation comprising pimple and solid regions. More region types
	could be added.

SourceFiles
	pimpleMultiRegionControlI.H
	pimpleMultiRegionControl.C

\*---------------------------------------------------------------------------*/

#include <multiRegionSolutionControl.hxx>
#include <pimpleLoop.hxx>
#include <convergenceControl.hxx>
#include <correctorConvergenceControl.hxx>
#include <pimpleNoLoopControl.hxx>
#include <solidNoLoopControl.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
					   Class pimpleMultiRegionControl Declaration
	\*---------------------------------------------------------------------------*/

	class pimpleMultiRegionControl
		:
		public multiRegionSolutionControl,
		public pimpleLoop,
		public convergenceControl,
		public correctorConvergenceControl
	{
	protected:

		// Protected data

		//- The per-region pimple controls
		PtrList<pimpleNoLoopControl> pimpleControls_;

		//- The per-region solid controls
		PtrList<solidNoLoopControl> solidControls_;


		// Protected Static Functions

		//- Get the time from the region meshes
		static FoamFiniteVolume_EXPORT const Time& time
		(
			const PtrList<fvMesh>& pimpleMeshes,
			const PtrList<fvMesh>& solidMeshes
		);


	public:

		// Static Data Members

		//- Run-time type information
		//TypeName("pimpleMultiRegionControl");
		static const char* typeName_() { return "pimpleMultiRegionControl"; }
		static FoamFiniteVolume_EXPORT const ::tnbLib::word typeName;
		static FoamFiniteVolume_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from meshes and the algorithm name
		FoamFiniteVolume_EXPORT pimpleMultiRegionControl
		(
			PtrList<fvMesh>& pimpleMeshes,
			PtrList<fvMesh>& solidMeshes,
			const word& algorithmName = "PIMPLE"
		);


		//- Destructor
		FoamFiniteVolume_EXPORT virtual ~pimpleMultiRegionControl();


		// Member Functions

			// IO

				//- Read controls
		FoamFiniteVolume_EXPORT virtual bool read();

		// Access

			//- Access the i-th pimple control
		inline pimpleNoLoopControl& pimple(const label i);

		//- Access the i-th solid control
		inline solidNoLoopControl& solid(const label i);

		//- Flag to indicate whether to solve the turbulence
		inline bool pimpleTurbCorr(const label i) const;

		// Evolution

			//- Return true if residual controls are present
		FoamFiniteVolume_EXPORT virtual bool hasResidualControls() const;

		//- Return true if corrector residual controls are present
		FoamFiniteVolume_EXPORT virtual bool hasCorrResidualControls() const;

		//- Return true if all convergence checks are satisfied
		FoamFiniteVolume_EXPORT virtual bool criteriaSatisfied() const;

		//- Return true if all correction convergence checks are satisfied
		FoamFiniteVolume_EXPORT virtual bool corrCriteriaSatisfied() const;

		//- Reset the solve index in the correction residual control data
		FoamFiniteVolume_EXPORT virtual void resetCorrSolveIndex();

		//- Update the solve index in the correction residual control data
		FoamFiniteVolume_EXPORT virtual void updateCorrSolveIndex();

		//- Pimple loop
		FoamFiniteVolume_EXPORT bool loop();

		//- Time run loop
		FoamFiniteVolume_EXPORT bool run(Time& time);

		//- Time loop loop
		FoamFiniteVolume_EXPORT bool loop(Time& time);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <pimpleMultiRegionControlI.hxx>

#endif // !_pimpleMultiRegionControl_Header
