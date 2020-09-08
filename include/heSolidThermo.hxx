#pragma once
#ifndef _heSolidThermo_Header
#define _heSolidThermo_Header

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
	tnbLib::heSolidThermo

Description
	Energy for a solid mixture

SourceFiles
	heSolidThermo.C

\*---------------------------------------------------------------------------*/

#include <heThermo.hxx>
#include <typeInfo.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							Class heSolidThermo Declaration
	\*---------------------------------------------------------------------------*/

	template<class BasicSolidThermo, class MixtureType>
	class heSolidThermo
		:
		public heThermo<BasicSolidThermo, MixtureType>
	{
		// Private Member Functions

			//- Calculate the thermo variables
		void calculate();

		//- Construct as copy (not implemented)
		heSolidThermo(const heSolidThermo<BasicSolidThermo, MixtureType>&);


	public:

		//- Runtime type information
		TypeName("heSolidThermo");


		// Constructors

			//- Construct from mesh and phase name
		heSolidThermo
		(
			const fvMesh&,
			const word& phaseName
		);

		//- Construct from mesh, dictionary and phase name
		heSolidThermo
		(
			const fvMesh&,
			const dictionary&,
			const word& phaseName
		);


		//- Destructor
		virtual ~heSolidThermo();


		// Member Functions

			//- Update properties
		virtual void correct();


		// Derived thermal properties

			//- Anisotropic thermal conductivity [W/m/K]
		virtual tmp<volVectorField> Kappa() const;

		//- Return true if thermal conductivity is isotropic
		virtual bool isotropic() const
		{
			return MixtureType::thermoType::isotropic;
		}


		// Per patch calculation

			//- Anisotropic thermal conductivity [W/m/K]
		virtual tmp<vectorField> Kappa(const label patchi) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <heSolidThermoI.hxx>

//#ifdef NoRepository
//#include <heSolidThermo.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_heSolidThermo_Header
