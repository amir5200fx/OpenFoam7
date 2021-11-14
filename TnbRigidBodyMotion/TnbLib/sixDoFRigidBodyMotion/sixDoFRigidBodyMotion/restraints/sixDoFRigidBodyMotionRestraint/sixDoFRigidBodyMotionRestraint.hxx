#pragma once
#ifndef _sixDoFRigidBodyMotionRestraint_Header
#define _sixDoFRigidBodyMotionRestraint_Header

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

Namespace
	tnbLib::sixDoFRigidBodyMotionRestraints

Description
	Namespace for six DoF motion restraints


Class
	tnbLib::sixDoFRigidBodyMotionRestraint

Description
	Base class for defining restraints for sixDoF motions

SourceFiles
	sixDoFRigidBodyMotionRestraint.C
	sixDoFRigidBodyMotionRestraintNew.C

\*---------------------------------------------------------------------------*/

#include <RigidBodyMotion_Module.hxx>

#include <Time.hxx>
#include <dictionary.hxx>
#include <autoPtr.hxx>
#include <vector.hxx>
#include <runTimeSelectionTables.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of classes
	class sixDoFRigidBodyMotion;


	/*---------------------------------------------------------------------------*\
					Class sixDoFRigidBodyMotionRestraint Declaration
	\*---------------------------------------------------------------------------*/

	class sixDoFRigidBodyMotionRestraint
	{

	protected:

		// Protected data

			//- Name of the restraint
		word name_;

		//- Restraint model specific coefficient dictionary
		dictionary sDoFRBMRCoeffs_;


	public:

		//- Runtime type information
		TypeName("sixDoFRigidBodyMotionRestraint");


		// Declare run-time constructor selection table

		declareRunTimeSelectionTable
		(
			autoPtr,
			sixDoFRigidBodyMotionRestraint,
			dictionary,
			(const word& name, const dictionary& sDoFRBMRDict),
			(name, sDoFRBMRDict)
		);


		// Constructors

			//- Construct from the sDoFRBMRDict dictionary and Time
		sixDoFRigidBodyMotionRestraint
		(
			const word& name,
			const dictionary& sDoFRBMRDict
		);

		//- Construct and return a clone
		virtual autoPtr<sixDoFRigidBodyMotionRestraint> clone() const = 0;


		// Selectors

			//- Select constructed from the sDoFRBMRDict dictionary and Time
		static autoPtr<sixDoFRigidBodyMotionRestraint> New
		(
			const word& name,
			const dictionary& sDoFRBMRDict
		);


		//- Destructor
		virtual ~sixDoFRigidBodyMotionRestraint();


		// Member Functions

			//- Return the name
		const word& name() const
		{
			return name_;
		}

		//- Calculate the restraint position, force and moment.
		//  Global reference frame vectors.
		virtual void restrain
		(
			const sixDoFRigidBodyMotion& motion,
			vector& restraintPosition,
			vector& restraintForce,
			vector& restraintMoment
		) const = 0;

		//- Update properties from given dictionary
		virtual bool read(const dictionary& sDoFRBMRDict);

		// Access

			// Return access to sDoFRBMRCoeffs
		inline const dictionary& coeffDict() const
		{
			return sDoFRBMRCoeffs_;
		}

		//- Write
		virtual void write(Ostream&) const = 0;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_sixDoFRigidBodyMotionRestraint_Header
