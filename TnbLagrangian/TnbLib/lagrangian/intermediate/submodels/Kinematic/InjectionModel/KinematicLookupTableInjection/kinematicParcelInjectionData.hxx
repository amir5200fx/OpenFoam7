#pragma once
#ifndef _kinematicParcelInjectionData_Header
#define _kinematicParcelInjectionData_Header

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
	tnbLib::kinematicParcelInjectionData

Description
	Container class to provide injection data for kinematic parcels

SourceFiles
	kinematicParcelInjectionData.C

\*---------------------------------------------------------------------------*/

#include <dictionary.hxx>
#include <vector.hxx>
#include <point.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of classes
	class kinematicParcelInjectionData;

	// Forward declaration of friend functions

	FoamLagrangian_EXPORT Ostream& operator<<
		(
			Ostream&,
			const kinematicParcelInjectionData&
			);

	FoamLagrangian_EXPORT Istream& operator>>
		(
			Istream&,
			kinematicParcelInjectionData&
			);

	/*---------------------------------------------------------------------------*\
				   Class kinematicParcelInjectionData Declaration
	\*---------------------------------------------------------------------------*/

	class kinematicParcelInjectionData
	{
	protected:

		// Parcel properties

			//- Position [m]
		point x_;

		//- Velocity [m/s]
		vector U_;

		//- Diameter [m]
		scalar d_;

		//- Density [kg/m^3]
		scalar rho_;

		//- Mass flow rate [kg/s]
		scalar mDot_;


	public:

		//- Runtime type information
		//TypeName("kinematicParcelInjectionData");
		static const char* typeName_() { return "kinematicParcelInjectionData"; }
		static FoamLagrangian_EXPORT const ::tnbLib::word typeName;
		static FoamLagrangian_EXPORT int debug;
		virtual const word& type() const { return typeName; };

		// Constructors

			//- Null constructor
		FoamLagrangian_EXPORT kinematicParcelInjectionData();

		//- Construct from dictionary
		FoamLagrangian_EXPORT kinematicParcelInjectionData(const dictionary& dict);

		//- Construct from Istream
		FoamLagrangian_EXPORT kinematicParcelInjectionData(Istream& is);


		//-Destructor
		FoamLagrangian_EXPORT virtual ~kinematicParcelInjectionData();


		// Access

			//- Return const access to the position
		inline const point& x() const;

		//- Return const access to the velocity
		inline const vector& U() const;

		//- Return const access to the diameter
		inline scalar d() const;

		//- Return const access to the density
		inline scalar rho() const;

		//- Return const access to the mass flow rate
		inline scalar mDot() const;


		// Edit

			//- Return access to the position
		inline point& x();

		//- Return access to the velocity
		inline vector& U();

		//- Return access to the diameter
		inline scalar& d();

		//- Return access to the density
		inline scalar& rho();

		//- Return access to the mass flow rate
		inline scalar& mDot();


		// Friend Operators

		friend bool operator==
			(
				const kinematicParcelInjectionData& a,
				const kinematicParcelInjectionData& b
				)
		{
			NotImplemented;

			return false;
		}

		friend bool operator!=
			(
				const kinematicParcelInjectionData& a,
				const kinematicParcelInjectionData& b
				)
		{
			NotImplemented;

			return false;
		}


		// I-O

			//- Ostream operator
		friend FoamLagrangian_EXPORT Ostream& operator<<
			(
				Ostream& os,
				const kinematicParcelInjectionData& data
				);

		//- Istream operator
		friend FoamLagrangian_EXPORT Istream& operator>>
			(
				Istream& is,
				kinematicParcelInjectionData& data
				);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <kinematicParcelInjectionDataI.hxx>

#endif // !_kinematicParcelInjectionData_Header
