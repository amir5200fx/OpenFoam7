#pragma once
#ifndef _RanzMarshall_Header
#define _RanzMarshall_Header

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
	tnbLib::RanzMarshall

Description
	The Ranz-Marshall correlation for heat transfer

\*---------------------------------------------------------------------------*/

#include <HeatTransferModelTemplate.hxx>

#ifdef FoamLagrangian_EXPORT_DEFINE
#define FoamRanzMarshall_EXPORT __declspec(dllexport)
#else
#ifdef FoamRanzMarshall_EXPORT_DEFINE
#define FoamRanzMarshall_EXPORT __declspec(dllexport)
#else
#define FoamRanzMarshall_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							 Class RanzMarshall Declaration
	\*---------------------------------------------------------------------------*/

	template<class CloudType>
	class RanzMarshall
		:
		public HeatTransferModel<CloudType>
	{

	public:

		//- Runtime type information
		//TypeName("RanzMarshall");
		static const char* typeName_() { return "RanzMarshall"; }
		static FoamRanzMarshall_EXPORT const ::tnbLib::word typeName;
		static FoamRanzMarshall_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from dictionary
		RanzMarshall(const dictionary& dict, CloudType& cloud);

		//- Construct copy
		RanzMarshall(const RanzMarshall<CloudType>& im);

		//- Construct and return a clone
		virtual autoPtr<HeatTransferModel<CloudType>> clone() const
		{
			return autoPtr<HeatTransferModel<CloudType>>
				(
					new RanzMarshall<CloudType>(*this)
					);
		}


		//- Destructor
		virtual ~RanzMarshall();


		// Member Functions

			// Evaluation

				//- Nusselt number
		virtual scalar Nu
		(
			const scalar Re,
			const scalar Pr
		) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <RanzMarshallI.hxx>

//#ifdef NoRepository
//#include <RanzMarshall.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_RanzMarshall_Header
