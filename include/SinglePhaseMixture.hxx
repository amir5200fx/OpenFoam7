#pragma once
#ifndef _SinglePhaseMixture_Header
#define _SinglePhaseMixture_Header

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
	tnbLib::SinglePhaseMixture

Description
	Templated parcel single phase, multi-component class

SourceFiles
	SinglePhaseMixture.C

\*---------------------------------------------------------------------------*/

#include <CompositionModel.hxx>

#ifdef FoamLagrangian_EXPORT_DEFINE
#define FoamSinglePhaseMixture_EXPORT __declspec(dllexport)
#else
#ifdef FoamSinglePhaseMixture_EXPORT_DEFINE
#define FoamSinglePhaseMixture_EXPORT __declspec(dllexport)
#else
#define FoamSinglePhaseMixture_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						  Class SinglePhaseMixture Declaration
	\*---------------------------------------------------------------------------*/

	template<class CloudType>
	class SinglePhaseMixture
		:
		public CompositionModel<CloudType>
	{
		// Private Data

			// Indices of the phases - only 1 will be set

				//- Gas
		label idGas_;

		//- Liquid
		label idLiquid_;

		//- Solid
		label idSolid_;


		// Private Member Functions

			//- Construct the indices and check correct specification of
			//  1 gas or 1 liquid or 1 solid
		void constructIds();


	public:

		//- Runtime type information
		//TypeName("singlePhaseMixture");
		static const char* typeName_() { return "singlePhaseMixture"; }
		static FoamSinglePhaseMixture_EXPORT const ::tnbLib::word typeName;
		static FoamSinglePhaseMixture_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from dictionary
		SinglePhaseMixture(const dictionary& dict, CloudType& owner);

		//- Construct copy
		SinglePhaseMixture(const SinglePhaseMixture<CloudType>& cm);

		//- Construct and return a clone
		virtual autoPtr<CompositionModel<CloudType>> clone() const
		{
			return autoPtr<CompositionModel<CloudType>>
				(
					new SinglePhaseMixture<CloudType>(*this)
					);
		}


		//- Destructor
		virtual ~SinglePhaseMixture();


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

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <SinglePhaseMixtureI.hxx>

//#ifdef NoRepository
//#include <SinglePhaseMixture.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_SinglePhaseMixture_Header
