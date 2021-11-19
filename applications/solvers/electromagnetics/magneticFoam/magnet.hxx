#pragma once
#ifndef _magnet_Header
#define _magnet_Header

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
    tnbLib::magnet

Description
    Class to hold the defining data for a permanent magnet, in particular
    the name, relative permeability and remanence.

SourceFiles

\*---------------------------------------------------------------------------*/

#include <includeAllModules.hxx>

#include <dimensionedVector.hxx>
#include <error.hxx>
#include <OSstream.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

    // Forward declaration of classes
    class Istream;
    class Ostream;

    // Forward declaration of friend functions and operators
    class magnet;
    //Istream& operator>>(Istream&, magnet&);
    Ostream& operator<<(Ostream&, const magnet&);

    /*---------------------------------------------------------------------------*\
                             Class magnet Declaration
    \*---------------------------------------------------------------------------*/

    class magnet
    {
        // Private Data

        word name_;
        scalar relativePermeability_;
        dimensionedScalar remanence_;
        vector orientation_;

    public:

        // Constructors

            //- Null constructor for lists
        inline magnet()
            :
            remanence_("Mr", dimensionSet(0, -1, 0, 0, 0, 1, 0), 0),
            orientation_(Zero)
        {}

        //- Construct from components
        inline magnet
        (
            const word& name,
            const scalar mur,
            const scalar Mr,
            const vector& orientation
        )
            :
            name_(name),
            relativePermeability_(mur),
            remanence_("Mr", dimensionSet(0, -1, 0, 0, 0, 1, 0), Mr),
            orientation_(orientation)
        {}

        //- Construct from Istream
        inline magnet(Istream& is)
            :
            remanence_("Mr", dimensionSet(0, -1, 0, 0, 0, 1, 0), 0),
            orientation_(Zero)
        {
            is >> *this;
        }


        // Member Functions

            //- Return name
        inline const word& name() const
        {
            return name_;
        }

        //- Return relative permeability
        inline scalar mur() const
        {
            return relativePermeability_;
        }

        //- Return remenance
        inline const dimensionedScalar& Mr() const
        {
            return remanence_;
        }

        //- Return orientation
        inline const vector& orientation() const
        {
            return orientation_;
        }

		inline const magnet& operator!=(const magnet& m) const
		{
			FatalErrorInFunction
				<< "this function is not supposed to be called!" << endl
				<< abort(FatalError);
			return *this;
		}

        // IOstream Operators

        inline friend Istream& operator>>(Istream& is, magnet& m)
        {
            is.readBegin("magnet");
            is >> m.name_
                >> m.relativePermeability_
                >> m.remanence_.value()
                >> m.orientation_;
            is.readEnd("magnet");

            // Check state of Istream
            is.check("operator>>(Istream&, magnet&)");

            return is;
        }

        inline friend Ostream& operator<<(Ostream& os, const magnet& m)
        {
            os << token::BEGIN_LIST
                << m.name_ << token::SPACE
                << m.relativePermeability_ << token::SPACE
                << m.remanence_.value()
                << m.orientation_
                << token::END_LIST;

            return os;
        }
    };


    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
#endif // !_magnet_Header
