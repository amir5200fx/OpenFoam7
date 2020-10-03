#include <fieldExpression.hxx>

#include <dictionary.hxx>

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2016-2018 OpenFOAM Foundation
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

\*---------------------------------------------------------------------------*/

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionObjects
	{
		defineTypeNameAndDebug(fieldExpression, 0);
	}
}


// * * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * //

void tnbLib::functionObjects::fieldExpression::setResultName
(
	const word& typeName,
	const word& defaultArg
)
{
	if (fieldName_.empty())
	{
		fieldName_ = defaultArg;
	}

	if (resultName_.empty())
	{
		if (fieldName_ != defaultArg)
		{
			resultName_ = typeName + '(' + fieldName_ + ')';
		}
		else
		{
			resultName_ = typeName;
		}
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::functionObjects::fieldExpression::fieldExpression
(
	const word& name,
	const Time& runTime,
	const dictionary& dict,
	const word& fieldName,
	const word& resultName
)
	:
	fvMeshFunctionObject(name, runTime, dict),
	fieldName_(fieldName),
	resultName_(resultName)
{
	read(dict);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::functionObjects::fieldExpression::~fieldExpression()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::functionObjects::fieldExpression::read(const dictionary& dict)
{
	fvMeshFunctionObject::read(dict);

	if (fieldName_.empty() || dict.found("field"))
	{
		dict.lookup("field") >> fieldName_;
	}

	if (dict.found("result"))
	{
		dict.lookup("result") >> resultName_;
	}

	return true;
}


bool tnbLib::functionObjects::fieldExpression::execute()
{
	if (!calc())
	{
		Warning
			<< "    functionObjects::" << type() << " " << name()
			<< " failed to execute." << endl;

		// Clear the result field from the objectRegistry if present
		clear();

		return false;
	}
	else
	{
		return true;
	}
}


bool tnbLib::functionObjects::fieldExpression::write()
{
	return writeObject(resultName_);
}


bool tnbLib::functionObjects::fieldExpression::clear()
{
	return clearObject(resultName_);
}


// ************************************************************************* //