#pragma once
#ifndef _hePsiThermo_Header
#define _hePsiThermo_Header

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
	tnbLib::hePsiThermo

Description
	Energy for a mixture based on compressibility

SourceFiles
	hePsiThermo.C

\*---------------------------------------------------------------------------*/

#include <psiThermo.hxx>
#include <heThermo.hxx>

#ifdef FoamThermophysicalModels_EXPORT_DEFINE
#define FoamhePsiThermo_EXPORT __declspec(dllexport)
#else
#ifdef FoamhePsiThermo_EXPORT_DEFINE
#define FoamhePsiThermo_EXPORT __declspec(dllexport)
#else
#define FoamhePsiThermo_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							 Class hePsiThermo Declaration
	\*---------------------------------------------------------------------------*/

	template<class BasicPsiThermo, class MixtureType>
	class hePsiThermo
		:
		public heThermo<BasicPsiThermo, MixtureType>
	{
		// Private Member Functions

			//- Calculate the thermo variables
		void calculate();

		//- Construct as copy (not implemented)
		hePsiThermo(const hePsiThermo<BasicPsiThermo, MixtureType>&);

	public:

		//- Runtime type information
		//TypeName("hePsiThermo");
		static const char* typeName_() { return "hePsiThermo"; }
		static FoamhePsiThermo_EXPORT const ::tnbLib::word typeName;
		static FoamhePsiThermo_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from mesh and phase name
		hePsiThermo
		(
			const fvMesh&,
			const word& phaseName
		);


		//- Destructor
		virtual ~hePsiThermo();


		// Member Functions

			//- Update properties
		virtual void correct();
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <hePsiThermoI.hxx>

//#ifdef NoRepository
//#include <hePsiThermo.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_hePsiThermo_Header
