#pragma once
#ifndef _bladeModel_Header
#define _bladeModel_Header

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
	tnbLib::bladeModel

Description
	Blade model class calculates:
		Linear interpolated blade twist and chord based on radial position
		Interpolation factor (for interpolating profile performance)

	Input in list format:

		data
		(
			(profile1 (radius1 twist1 chord1))
			(profile1 (radius2 twist2 chord2))
		);

	where:
		radius [m]
		twist [deg], converted to [rad] internally
		chord [m]

SourceFiles
	bladeModel.C

\*---------------------------------------------------------------------------*/

#include <List.hxx>
#include <dictionary.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							 Class bladeModel Declaration
	\*---------------------------------------------------------------------------*/

	class bladeModel
	{

	protected:

		// Protected data

			//- Corresponding profile name per section
		List<word> profileName_;

		//- Corresponding profile ID per section
		List<label> profileID_;

		//- Radius [m]
		List<scalar> radius_;

		//- Twist [deg] on input, converted to [rad]
		List<scalar> twist_;

		//- Chord [m]
		List<scalar> chord_;

		//- File name (optional)
		fileName fName_;


		// Protected Member Functions

			//- Return true if file name is set
		FoamFvOptions_EXPORT bool readFromFile() const;

		//- Return the interpolation indices and gradient
		FoamFvOptions_EXPORT void interpolateWeights
		(
			const scalar& xIn,
			const List<scalar>& values,
			label& i1,
			label& i2,
			scalar& ddx
		) const;


	public:

		//- Constructor
		FoamFvOptions_EXPORT bladeModel(const dictionary& dict);


		//- Destructor
		FoamFvOptions_EXPORT virtual ~bladeModel();


		// Member Functions

			// Access

				//- Return const access to the profile name list
		FoamFvOptions_EXPORT const List<word>& profileName() const;

		//- Return const access to the profile ID list
		FoamFvOptions_EXPORT const List<label>& profileID() const;

		//- Return const access to the radius list
		FoamFvOptions_EXPORT const List<scalar>& radius() const;

		//- Return const access to the twist list
		FoamFvOptions_EXPORT const List<scalar>& twist() const;

		//- Return const access to the chord list
		FoamFvOptions_EXPORT const List<scalar>& chord() const;


		// Edit

			//- Return non-const access to the profile ID list
		FoamFvOptions_EXPORT List<label>& profileID();


		// Evaluation

			//- Return the twist and chord for a given radius
		FoamFvOptions_EXPORT virtual void interpolate
		(
			const scalar radius,
			scalar& twist,
			scalar& chord,
			label& i1,
			label& i2,
			scalar& invDr
		) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_bladeModel_Header
