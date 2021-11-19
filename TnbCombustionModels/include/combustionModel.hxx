#pragma once
#ifndef _combustionModel_Header
#define _combustionModel_Header

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
	tnbLib::combustionModel

Description
	Base class for combustion models

SourceFiles
	combustionModel.C

\*---------------------------------------------------------------------------*/

#include <CombustionModels_Module.hxx>
#include <IOdictionary.hxx>
#include <turbulentFluidThermoModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						 Class combustionModel Declaration
	\*---------------------------------------------------------------------------*/

	class combustionModel
		:
		public IOdictionary
	{
		// Private Member Functions

			//- Construct the base IO object
		IOobject createIOobject
		(
			basicThermo& thermo,
			const word& combustionProperties
		) const;


	protected:

		// Protected data

			//- Reference to the mesh database
		const fvMesh& mesh_;

		//- Reference to the turbulence model
		const compressibleTurbulenceModel& turb_;

		//- Dictionary of the model
		dictionary coeffs_;

		//- Model type
		const word modelType_;


	public:

		//- Runtime type information
		//TypeName("combustionModel");
		static const char* typeName_() { return "combustionModel"; }
		static FoamCombustionModels_EXPORT const ::tnbLib::word typeName;
		static FoamCombustionModels_EXPORT int debug;
		virtual const word& type() const { return typeName; };

		//- Default combustionProperties dictionary name
		static FoamCombustionModels_EXPORT const word combustionPropertiesName;


		// Constructors

			//- Construct from components
		FoamCombustionModels_EXPORT combustionModel
		(
			const word& modelType,
			basicThermo& thermo,
			const compressibleTurbulenceModel& turb,
			const word& combustionProperties = combustionPropertiesName
		);

		//- Disallow default bitwise copy construction
		FoamCombustionModels_EXPORT combustionModel(const combustionModel&);


		// Selectors

			//- Generic New for each of the related chemistry model
		template<class CombustionModel>
		static autoPtr<CombustionModel> New
		(
			typename CombustionModel::reactionThermo& thermo,
			const compressibleTurbulenceModel& turb,
			const word& combustionProperties
		);


		//- Destructor
		virtual ~combustionModel();


		// Member Functions

			//- Return const access to the mesh database
		inline const fvMesh& mesh() const;

		//- Return access to turbulence
		inline const compressibleTurbulenceModel& turbulence() const;

		//- Return const access to rho
		inline const volScalarField& rho() const;

		//- Return const access to phi
		inline tmp<surfaceScalarField> phi() const;

		//- Return const dictionary of the model
		inline const dictionary& coeffs() const;

		//- Correct combustion rate
		virtual void correct() = 0;

		//- Fuel consumption rate matrix, i.e. source term for fuel equation
		virtual tmp<fvScalarMatrix> R(volScalarField& Y) const = 0;

		//- Heat release rate [kg/m/s^3]
		virtual tmp<volScalarField> Qdot() const = 0;

		//- Update properties from given dictionary
		FoamCombustionModels_EXPORT virtual bool read();


		// Member Operators

			//- Disallow default bitwise assignment
		void operator=(const combustionModel&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <combustionModelI.hxx>
#include <combustionModelTemplatesI.hxx>

//#ifdef NoRepository
//#include "combustionModelTemplates.cxx"
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_combustionModel_Header
