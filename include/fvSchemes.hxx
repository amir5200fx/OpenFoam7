#pragma once
#ifndef _fvSchemes_Header
#define _fvSchemes_Header

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
	tnbLib::fvSchemes

Description
	Selector class for finite volume differencing schemes.
	fvMesh is derived from fvShemes so that all fields have access to the
	fvSchemes from the mesh reference they hold.

SourceFiles
	fvSchemes.C

\*---------------------------------------------------------------------------*/

#include <IOdictionary.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class fvSchemes Declaration
	\*---------------------------------------------------------------------------*/

	class fvSchemes
		:
		public IOdictionary
	{
		// Private Data

		dictionary ddtSchemes_;
		ITstream defaultDdtScheme_;

		dictionary d2dt2Schemes_;
		ITstream defaultD2dt2Scheme_;

		dictionary interpolationSchemes_;
		ITstream defaultInterpolationScheme_;

		dictionary divSchemes_;
		ITstream defaultDivScheme_;

		dictionary gradSchemes_;
		ITstream defaultGradScheme_;

		dictionary snGradSchemes_;
		ITstream defaultSnGradScheme_;

		dictionary laplacianSchemes_;
		ITstream defaultLaplacianScheme_;

		mutable dictionary fluxRequired_;
		bool defaultFluxRequired_;

		//- Steady-state run indicator
		//  Set true if the default ddtScheme is steadyState
		bool steady_;


		// Private Member Functions

			//- Clear the dictionaries and streams before reading
		void clear();

		//- Read settings from the dictionary
		void read(const dictionary&);


	public:

		//- Debug switch
		static int debug;


		// Constructors

			//- Construct for objectRegistry
		fvSchemes(const objectRegistry& obr);

		//- Disallow default bitwise copy construction
		fvSchemes(const fvSchemes&) = delete;


		// Member Functions

			// Access

		const dictionary& schemesDict() const;

		ITstream& ddtScheme(const word& name) const;

		ITstream& d2dt2Scheme(const word& name) const;

		ITstream& interpolationScheme(const word& name) const;

		ITstream& divScheme(const word& name) const;

		ITstream& gradScheme(const word& name) const;

		ITstream& snGradScheme(const word& name) const;

		ITstream& laplacianScheme(const word& name) const;

		void setFluxRequired(const word& name) const;

		bool fluxRequired(const word& name) const;

		//- Return true if the default ddtScheme is steadyState
		bool steady() const
		{
			return steady_;
		}

		//- Return true if the default ddtScheme is not steadyState
		bool transient() const
		{
			return !steady_;
		}


		// Read

			//- Read the fvSchemes
		bool read();


		// Member Operators

			//- Disallow default bitwise assignment
		void operator=(const fvSchemes&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_fvSchemes_Header
