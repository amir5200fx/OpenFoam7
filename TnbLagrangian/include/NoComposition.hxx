#pragma once
#ifndef _NoComposition_Header
#define _NoComposition_Header

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
	tnbLib::NoComposition

Description
	Dummy class for 'none' option - will raise an error if any functions are
	called that require return values.

SourceFiles
	NoComposition.C

\*---------------------------------------------------------------------------*/

#include <CompositionModel.hxx>

#ifdef FoamLagrangian_EXPORT_DEFINE
#define FoamNoComposition_EXPORT __declspec(dllexport)
#else
#ifdef FoamNoComposition_EXPORT_DEFINE
#define FoamNoComposition_EXPORT __declspec(dllexport)
#else
#define FoamNoComposition_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						  Class NoComposition Declaration
	\*---------------------------------------------------------------------------*/

	template<class CloudType>
	class NoComposition
		:
		public CompositionModel<CloudType>
	{
	public:

		//- Runtime type information
		//TypeName("none");
		static const char* typeName_() { return "none"; }
		static FoamNoComposition_EXPORT const ::tnbLib::word typeName;
		static FoamNoComposition_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from dictionary
		NoComposition(const dictionary& dict, CloudType& owner);

		//- Construct copy
		NoComposition(const NoComposition<CloudType>& cm);

		//- Construct and return a clone
		virtual autoPtr<CompositionModel<CloudType>> clone() const
		{
			return autoPtr<CompositionModel<CloudType>>
				(
					new NoComposition<CloudType>(*this)
					);
		}


		//- Destructor
		virtual ~NoComposition();


		// Member Functions

			// Access

				// Mixture properties

					//- Return the list of mixture mass fractions
					//  If only 1 phase, return component fractions of that phase
		virtual const scalarField& YMixture0() const;

		// Indices of gas, liquid and solid phases in phase properties
		// list

			//- Gas id
		virtual label idGas() const;

		//- Liquid id
		virtual label idLiquid() const;

		//- Solid id
		virtual label idSolid() const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <NoCompositionI.hxx>

//#ifdef NoRepository
//#include <NoComposition.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_NoComposition_Header
