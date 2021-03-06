#pragma once
#ifndef _SingleMixtureFraction_Header
#define _SingleMixtureFraction_Header

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
	tnbLib::SingleMixtureFraction

Description
	Templated parcel multi-phase, multi-component class

SourceFiles
	SingleMixtureFraction.C

\*---------------------------------------------------------------------------*/

#include <CompositionModel.hxx>

#ifdef FoamLagrangian_EXPORT_DEFINE
#define FoamSingleMixtureFraction_EXPORT __declspec(dllexport)
#else
#ifdef FoamSingleMixtureFraction_EXPORT_DEFINE
#define FoamSingleMixtureFraction_EXPORT __declspec(dllexport)
#else
#define FoamSingleMixtureFraction_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						  Class SingleMixtureFraction Declaration
	\*---------------------------------------------------------------------------*/

	template<class CloudType>
	class SingleMixtureFraction
		:
		public CompositionModel<CloudType>
	{
		// Private Data

			// Indices of the phases

				//- Gas
		label idGas_;

		//- Liquid
		label idLiquid_;

		//- Solid
		label idSolid_;


		// Mixture properties

			 //- Phase component total fractions
		scalarField YMixture0_;


		// Private Member Functions

			//- Construct the indices and check correct specification of
			//  1 gas, 1 liquid and 1 solid
		void constructIds();


	public:

		//- Runtime type information
		//TypeName("singleMixtureFraction");
		static const char* typeName_() { return "singleMixtureFraction"; }
		static FoamSingleMixtureFraction_EXPORT const ::tnbLib::word typeName;
		static FoamSingleMixtureFraction_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from dictionary
		SingleMixtureFraction(const dictionary& dict, CloudType& owner);

		//- Construct copy
		SingleMixtureFraction(const SingleMixtureFraction<CloudType>& cm);

		//- Construct and return a clone
		virtual autoPtr<CompositionModel<CloudType>> clone() const
		{
			return autoPtr<CompositionModel<CloudType>>
				(
					new SingleMixtureFraction<CloudType>(*this)
					);
		}


		//- Destructor
		virtual ~SingleMixtureFraction();


		// Member Functions

			// Access

				// Mixture properties

					//- Return the list of mixture mass fractions
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


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <SingleMixtureFractionI.hxx>

//#ifdef NoRepository
//#include <SingleMixtureFraction.cxx>
//#endif

#endif // !_SingleMixtureFraction_Header
