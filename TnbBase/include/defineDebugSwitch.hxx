#pragma once
#ifndef _defineDebugSwitch_Header
#define _defineDebugSwitch_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2012-2018 OpenFOAM Foundation
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

Description
	Macro definitions for debug switches.

\*---------------------------------------------------------------------------*/

#include <simpleRegIOobject.hxx>
#include <tnbDebug.hxx>
#include <label.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	//- Define the debug information, lookup as \a Name
	template<class Type>
	class RegisterDebugSwitch
		:
		public ::tnbLib::simpleRegIOobject
	{
	public:

		//- The unique RegisterDebugSwitch object
		static const RegisterDebugSwitch registerDebugSwitch;

		RegisterDebugSwitch(const char* name)
			:
			::tnbLib::simpleRegIOobject(tnbLib::debug::addDebugObject, name)
		{}

		virtual ~RegisterDebugSwitch()
		{}

		virtual void readData(tnbLib::Istream& is)
		{
			Type::debug = readLabel(is);
		}

		virtual void writeData(tnbLib::Ostream& os) const
		{
			os << Type::debug;
		}
	};

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#define registerTemplateDebugSwitchWithName(Type,Name)                         \
    template<>                                                                 \
    const tnbLib::RegisterDebugSwitch<Type>                                      \
        tnbLib::RegisterDebugSwitch<Type>::registerDebugSwitch(Name)


//- Define the debug information, lookup as \a Name
#define registerDebugSwitchWithName(Type,Tag,Name)                             \
    class add##Tag##ToDebug                                                    \
    :                                                                          \
        public ::tnbLib::simpleRegIOobject                                       \
    {                                                                          \
    public:                                                                    \
        add##Tag##ToDebug(const char* name)                                    \
        :                                                                      \
            ::tnbLib::simpleRegIOobject(tnbLib::debug::addDebugObject, name)       \
        {}                                                                     \
        virtual ~add##Tag##ToDebug()                                           \
        {}                                                                     \
        virtual void readData(tnbLib::Istream& is)                               \
        {                                                                      \
            Type::debug = readLabel(is);                                       \
        }                                                                      \
        virtual void writeData(tnbLib::Ostream& os) const                        \
        {                                                                      \
            os << Type::debug;                                                 \
        }                                                                      \
    };                                                                         \
    add##Tag##ToDebug add##Tag##ToDebug_(Name)


//- Define the debug information, lookup as \a Name
#define defineDebugSwitchWithName(Type, Name, DebugSwitch)                     \
    int Type::debug(::tnbLib::debug::debugSwitch(Name, DebugSwitch))

//- Define the debug information
#define defineDebugSwitch(Type, DebugSwitch)                                   \
    defineDebugSwitchWithName(Type, Type::typeName_(), DebugSwitch);           \
    registerDebugSwitchWithName(Type, Type, Type::typeName_())

//- Define the debug information for templates, lookup as \a Name
#define defineTemplateDebugSwitchWithName(Type, Name, DebugSwitch)             \
    template<>                                                                 \
    defineDebugSwitchWithName(Type, Name, DebugSwitch);                        \
    registerTemplateDebugSwitchWithName(Type, Name)

//- Define the debug information for templates sub-classes, lookup as \a Name
#define defineTemplate2DebugSwitchWithName(Type, Name, DebugSwitch)            \
    template<>                                                                 \
    defineDebugSwitchWithName(Type, Name, DebugSwitch);                        \
    registerTemplateDebugSwitchWithName(Type, Name)

//- Define the debug information for templates
//  Useful with typedefs
#define defineTemplateDebugSwitch(Type, DebugSwitch)                           \
    defineTemplateDebugSwitchWithName(Type, #Type, DebugSwitch)

//- Define the debug information directly for templates
#define defineNamedTemplateDebugSwitch(Type, DebugSwitch)                      \
    defineTemplateDebugSwitchWithName(Type, Type::typeName_(), DebugSwitch)


//- Define the debug information for templates
//  Useful with typedefs
#define defineTemplate2DebugSwitch(Type, DebugSwitch)                          \
    defineTemplate2DebugSwitchWithName(Type, #Type, DebugSwitch)

//- Define the debug information directly for templates
#define defineNamedTemplate2DebugSwitch(Type, DebugSwitch)                     \
    defineTemplate2DebugSwitchWithName(Type, Type::typeName_(), DebugSwitch)


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_defineDebugSwitch_Header
