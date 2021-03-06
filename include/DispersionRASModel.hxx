#pragma once
#ifndef _DispersionRASModel_Header
#define _DispersionRASModel_Header

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
	tnbLib::DispersionRASModel

Description
	Base class for particle dispersion models based on RAS turbulence.

\*---------------------------------------------------------------------------*/

#include <DispersionModel.hxx>

#include <tmp.hxx>  // added by amir
#include <volFieldsFwd.hxx>  // added by amir

#ifdef FoamLagrangian_EXPORT_DEFINE
#define FoamDispersionRASModel_EXPORT __declspec(dllexport)
#else
#ifdef FoamDispersionRASModel_EXPORT_DEFINE
#define FoamDispersionRASModel_EXPORT __declspec(dllexport)
#else
#define FoamDispersionRASModel_EXPORT __declspec(dllimport)
#endif
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						   Class DispersionRASModel Declaration
	\*---------------------------------------------------------------------------*/

	template<class CloudType>
	class DispersionRASModel
		:
		public DispersionModel<CloudType>
	{
	protected:

		// Protected data

			// Locally cached turbulence fields

				//- Turbulence k
		const volScalarField* kPtr_;

		//- Take ownership of the k field
		mutable bool ownK_;

		//- Turbulence epsilon
		const volScalarField* epsilonPtr_;

		//- Take ownership of the epsilon field
		mutable bool ownEpsilon_;


		// Protected Functions

			//- Return the k field from the turbulence model
		tmp<volScalarField> kModel() const;

		//- Return the epsilon field from the turbulence model
		tmp<volScalarField> epsilonModel() const;


	public:

		//- Runtime type information
		//TypeName("dispersionRASModel");
		static const char* typeName_() { return "dispersionRASModel"; }
		static FoamDispersionRASModel_EXPORT const ::tnbLib::word typeName;
		static FoamDispersionRASModel_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Constructors

			//- Construct from components
		DispersionRASModel(const dictionary& dict, CloudType& owner);

		//- Construct copy
		DispersionRASModel(const DispersionRASModel<CloudType>& dm);

		//- Construct and return a clone
		virtual autoPtr<DispersionModel<CloudType>> clone() const = 0;


		//- Destructor
		virtual ~DispersionRASModel();


		// Member Functions

			//- Update (disperse particles)
		virtual vector update
		(
			const scalar dt,
			const label celli,
			const vector& U,
			const vector& Uc,
			vector& UTurb,
			scalar& tTurb
		) = 0;

		//- Cache carrier fields
		virtual void cacheFields(const bool store);


		// I-O

			//- Write
		virtual void write(Ostream& os) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <DispersionRASModelI.hxx>

//#ifdef NoRepository
//#include <DispersionRASModel.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_DispersionRASModel_Header
