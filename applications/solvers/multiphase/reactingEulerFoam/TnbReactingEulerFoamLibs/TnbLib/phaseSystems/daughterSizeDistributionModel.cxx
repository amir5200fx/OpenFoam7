/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2017-2018 OpenFOAM Foundation
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

#include <daughterSizeDistributionModel.hxx>

#include <breakupModelMultiphase.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
    namespace diameterModels
    {
        defineTypeNameAndDebug(daughterSizeDistributionModel, 0);
        defineRunTimeSelectionTable(daughterSizeDistributionModel, dictionary);
    }
}


// * * * * * * * * * * * * * * * * Selector  * * * * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::diameterModels::daughterSizeDistributionModel>
tnbLib::diameterModels::daughterSizeDistributionModel::New
(
    const breakupModel& breakup,
    const dictionary& dict
)
{
    word daughterSizeDistributionModelType
    (
        dict.lookup("daughterSizeDistributionModel")
    );

    dictionaryConstructorTable::iterator cstrIter =
        dictionaryConstructorTablePtr_->find(daughterSizeDistributionModelType);

    if (cstrIter == dictionaryConstructorTablePtr_->end())
    {
        FatalErrorInFunction
            << "Unknown daughter size distribution model type "
            << daughterSizeDistributionModelType << endl << endl
            << "Valid daughter size distribution model types are : " << endl
            << dictionaryConstructorTablePtr_->sortedToc()
            << exit(FatalError);
    }

    return cstrIter()(breakup, dict);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //


tnbLib::diameterModels::daughterSizeDistributionModel::
daughterSizeDistributionModel
(
    const breakupModel& breakup,
    const dictionary& dict
)
    :
    breakup_(breakup)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::diameterModels::daughterSizeDistributionModel::
~daughterSizeDistributionModel()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

const tnbLib::dimensionedScalar&
tnbLib::diameterModels::daughterSizeDistributionModel::
nik
(
    const label i,
    const label k
) const
{
    return nik_[k][i];
}


void tnbLib::diameterModels::daughterSizeDistributionModel::correct()
{
    if (nik_.size() == 0)
    {
        forAll(breakup_.popBal().sizeGroups(), k)
        {
            nik_.append(new PtrList<dimensionedScalar>());

            for (label i = 0; i <= k; i++)
            {
                nik_[k].append(new dimensionedScalar(this->calcNik(i, k)));
            }
        }
    }
}


// ************************************************************************* //
