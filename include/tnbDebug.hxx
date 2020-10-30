#pragma once
#ifndef _tnbDebug_Header
#define _tnbDebug_Header

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
	tnbLib::debug

Description
	Namespace for handling debugging switches.

SourceFiles
	debug.C

\*---------------------------------------------------------------------------*/

#include <includeModule.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of classes
	class dictionary;
	class Istream;
	class Ostream;
	class simpleRegIOobject;
	class simpleObjectRegistry;

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	namespace debug
	{
		//- The central control dictionary.
		//  Located in ~/.OpenFOAM/VERSION or $WM_PROJECT_DIR/etc
		//  \sa tnbLib::findEtcFile()
		FoamBase_EXPORT dictionary& controlDict();

		//- The DebugSwitches sub-dictionary in the central controlDict.
		FoamBase_EXPORT dictionary& debugSwitches();

		//- The InfoSwitches sub-dictionary in the central controlDict.
		FoamBase_EXPORT dictionary& infoSwitches();

		//- The OptimisationSwitches sub-dictionary in the central controlDict.
		FoamBase_EXPORT dictionary& optimisationSwitches();

		//- Lookup debug switch or add default value.
		FoamBase_EXPORT int debugSwitch(const char* name, const int defaultValue = 0);

		//- Lookup info switch or add default value.
		FoamBase_EXPORT int infoSwitch(const char* name, const int defaultValue = 0);

		//- Lookup optimisation switch or add default value.
		FoamBase_EXPORT int optimisationSwitch(const char* name, const int defaultValue = 0);

		//- Lookup optimisation switch or add default value.
		FoamBase_EXPORT float floatOptimisationSwitch
		(
			const char* name,
			const float defaultValue = 0
		);

		//- Internal function to lookup a sub-dictionary from controlDict.
		FoamBase_EXPORT dictionary& switchSet(const char* subDictName, dictionary*& subDictPtr);

		//- List debug switches
		FoamBase_EXPORT void listSwitches(const bool unset);


		// Registered debug switches

			//- Register debug switch read/write object
		FoamBase_EXPORT void addDebugObject(const char* name, simpleRegIOobject* obj);

		//- Register info switch read/write object
		FoamBase_EXPORT void addInfoObject(const char* name, simpleRegIOobject* obj);

		//- Register optimisation switch read/write object
		FoamBase_EXPORT void addOptimisationObject(const char* name, simpleRegIOobject* obj);

		//- Register DimensionSets read/write object
		FoamBase_EXPORT void addDimensionSetObject(const char* name, simpleRegIOobject* obj);

		//- Register DimensionedConstant read/write object
		FoamBase_EXPORT void addDimensionedConstantObject(const char* name, simpleRegIOobject*);


		//- Get access to registered debug switch objects
		FoamBase_EXPORT simpleObjectRegistry& debugObjects();

		//- Get access to registered info switch objects
		FoamBase_EXPORT simpleObjectRegistry& infoObjects();

		//- Get access to registered optimisation switch objects
		FoamBase_EXPORT simpleObjectRegistry& optimisationObjects();

		//- Get access to registered dimensionSets switch objects
		FoamBase_EXPORT simpleObjectRegistry& dimensionSetObjects();

		//- Get access to registered dimensionedConstant switch objects
		FoamBase_EXPORT simpleObjectRegistry& dimensionedConstantObjects();

		//- List registered debug switches
		FoamBase_EXPORT void listRegisteredSwitches(const bool unset);

	} // End namespace debug


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_tnbDebug_Header
