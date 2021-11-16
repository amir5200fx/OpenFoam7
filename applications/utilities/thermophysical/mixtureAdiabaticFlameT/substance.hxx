#pragma once
#ifndef _substance_Header
#define _substance_Header

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
    tnbLib::substance

Description

SourceFiles
    substanceI.H
    substance.C
    substanceIO.C

\*---------------------------------------------------------------------------*/

#include <includeAllModules.hxx>

#include <scalar.hxx>
#include <word.hxx>
#include <Istream.hxx>
#include <token.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

    /*---------------------------------------------------------------------------*\
                               Class substance Declaration
    \*---------------------------------------------------------------------------*/

    class substance
    {
        // Private Data

        word name_;
        scalar volFrac_;


    public:

        // Constructors

            //- Construct null
        substance()
        {}


        // Member Functions

            // Access

        const word& name() const
        {
            return name_;
        }

        scalar volFrac() const
        {
            return volFrac_;
        }

        bool operator==(const substance& s) const
        {
            return name_ == s.name_ && volFrac_ == s.volFrac_;
        }

        bool operator!=(const substance& s) const
        {
            return !operator==(s);
        }


        // IOstream Operators

        friend Istream& operator>>(Istream& is, substance& s)
        {
            is >> s.name_ >> s.volFrac_;
            return is;
        }

        friend Ostream& operator<<(Ostream& os, const substance& s)
        {
            os << s.name_ << token::SPACE << s.volFrac_;
            return os;
        }
    };


    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
#endif // !_substance_Header
