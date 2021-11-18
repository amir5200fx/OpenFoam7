#pragma once
#ifndef _relaxationModel_Header
#define _relaxationModel_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2012-2019 OpenFOAM Foundation
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
    tnbLib::relaxationModel

Description
    Abstract base class for providing relaxation values to the cell motion
    controller

SourceFiles
    relaxationModel.C

\*---------------------------------------------------------------------------*/

#include <FoamyMesh_Module.hxx>

#include <point.hxx>
#include <Time.hxx>
#include <dictionary.hxx>
#include <autoPtr.hxx>
#include <runTimeSelectionTables.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

    /*---------------------------------------------------------------------------*\
                           Class relaxationModel Declaration
    \*---------------------------------------------------------------------------*/

    class relaxationModel
        :
        public dictionary
    {

    protected:

        // Protected data

            //- Reference to the conformalVoronoiMesh holding this cvControls object
        const Time& runTime_;

        //- Method coeffs dictionary
        dictionary coeffDict_;


    public:

        //- Runtime type information
        /*TypeName("relaxationModel");*/
        static const char* typeName_() { return "relaxationModel"; }
        static FoamFoamyMesh_EXPORT const ::tnbLib::word typeName;
        static FoamFoamyMesh_EXPORT int debug;
        virtual const word& type() const { return typeName; };


        // Declare run-time constructor selection table

        /*declareRunTimeSelectionTable
        (
            autoPtr,
            relaxationModel,
            dictionary,
            (
                const dictionary& relaxationDict,
                const Time& runTime
                ),
            (relaxationDict, runTime)
        );*/
        typedef autoPtr<relaxationModel> (*dictionaryConstructorPtr)(const dictionary& relaxationDict,
                                                                     const Time& runTime);
        typedef HashTable<dictionaryConstructorPtr, word, string::hash> dictionaryConstructorTable;
        static FoamFoamyMesh_EXPORT dictionaryConstructorTable* dictionaryConstructorTablePtr_;
        static FoamFoamyMesh_EXPORT void constructdictionaryConstructorTables();
        static FoamFoamyMesh_EXPORT void destroydictionaryConstructorTables();

        template <class relaxationModelType>
        class adddictionaryConstructorToTable
        {
        public:
	        static autoPtr<relaxationModel> New(const dictionary& relaxationDict, const Time& runTime)
	        {
		        return autoPtr<relaxationModel>(new relaxationModelType(relaxationDict, runTime));
	        }

	        adddictionaryConstructorToTable(const word& lookup = relaxationModelType::typeName)
	        {
		        constructdictionaryConstructorTables();
		        if (!dictionaryConstructorTablePtr_->insert(lookup, New))
		        {
			        std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "relaxationModel" <<
				        std::endl;
			        error::safePrintStack(std::cerr);
		        }
	        }

	        ~adddictionaryConstructorToTable() { destroydictionaryConstructorTables(); }
        };

        template <class relaxationModelType>
        class addRemovabledictionaryConstructorToTable
        {
	        const word& lookup_;
        public:
	        static autoPtr<relaxationModel> New(const dictionary& relaxationDict, const Time& runTime)
	        {
		        return autoPtr<relaxationModel>(new relaxationModelType(relaxationDict, runTime));
	        }

	        addRemovabledictionaryConstructorToTable(const word& lookup = relaxationModelType::typeName) : lookup_(
		        lookup)
	        {
		        constructdictionaryConstructorTables();
		        dictionaryConstructorTablePtr_->set(lookup, New);
	        }

	        ~addRemovabledictionaryConstructorToTable()
	        {
		        if (dictionaryConstructorTablePtr_) { dictionaryConstructorTablePtr_->erase(lookup_); }
	        }
        };;


        // Constructors

            //- Construct from components
        FoamFoamyMesh_EXPORT relaxationModel
        (
            const word& type,
            const dictionary& relaxationDict,
            const Time& runTime
        );

        //- Disallow default bitwise copy construction
        relaxationModel(const relaxationModel&) = delete;


        // Selectors

            //- Return a reference to the selected relaxationModel
        static autoPtr<relaxationModel> New
        (
            const dictionary& relaxationDict,
            const Time& runTime
        );


        //- Destructor
        FoamFoamyMesh_EXPORT virtual ~relaxationModel();


        // Member Functions

            //- Const access to the coeffs dictionary
        const dictionary& coeffDict() const
        {
            return coeffDict_;
        }

        //- Return the current relaxation coefficient
        virtual scalar relaxation() = 0;


        // Member Operators

            //- Disallow default bitwise assignment
        void operator=(const relaxationModel&) = delete;
    };


    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
#endif // !_relaxationModel_Header