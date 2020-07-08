#pragma once
#include <tnbVersion.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Name>
inline tnbLib::word tnbLib::IOobject::groupName(Name name, const word& group)
{
	if (group != word::null)
	{
		return name + ('.' + group);
	}
	else
	{
		return name;
	}
}


template<class Stream>
inline Stream& tnbLib::IOobject::writeBanner(Stream& os, bool noHint)
{
	static bool spacesSet(false);
	static char spaces[40];

	if (!spacesSet)
	{
		memset(spaces, ' ', 40);

		size_t len = strlen(tnbLib::FOAMversion);
		if (len < 38)
		{
			spaces[38 - len] = '\0';
		}
		else
		{
			spaces[0] = '\0';
		}
		spacesSet = true;
	}

	if (noHint)
	{
		os <<
			"/*--------------------------------------"
			"-------------------------------------*\\\n";
	}
	else
	{
		os <<
			"/*--------------------------------*- C++ "
			"-*----------------------------------*\\\n";
	}

	os <<
		"  =========                 |\n"
		"  \\\\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox\n"
		"   \\\\    /   O peration     | Website:  https://openfoam.org\n"
		"    \\\\  /    A nd           | Version:  " << FOAMversion << "\n"
		"     \\\\/     M anipulation  |\n"
		"\\*-----------------------------------------"
		"----------------------------------*/\n";

	return os;
}


template<class Stream>
inline Stream& tnbLib::IOobject::writeDivider(Stream& os)
{
	os <<
		"// * * * * * * * * * * * * * * * * * "
		"* * * * * * * * * * * * * * * * * * * * //\n";

	return os;
}

template<class Stream>
inline Stream& tnbLib::IOobject::writeEndDivider(Stream& os)
{
	os << "\n\n"
		"// *****************************************"
		"******************************** //\n";

	return os;
}


// ************************************************************************* //