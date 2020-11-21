#pragma once
#include <volFields.hxx>
#include <fvcVolumeIntegrate.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<class ChemistryModelType>
void tnbLib::functionObjects::specieReactionRates<ChemistryModelType>::
writeFileHeader
(
	const label i
)
{
	writeHeader(file(), "Specie reaction rates");
	volRegion::writeFileHeader(*this, file());
	writeHeaderValue(file(), "nSpecie", chemistryModel_.nSpecie());
	writeHeaderValue(file(), "nReaction", chemistryModel_.nReaction());

	writeCommented(file(), "Time");
	writeTabbed(file(), "Reaction");

	const wordList& speciesNames =
		chemistryModel_.thermo().composition().species();

	forAll(speciesNames, si)
	{
		writeTabbed(file(), speciesNames[si]);
	}

	file() << endl;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class ChemistryModelType>
tnbLib::functionObjects::specieReactionRates<ChemistryModelType>::
specieReactionRates
(
	const word& name,
	const Time& runTime,
	const dictionary& dict
)
	:
	fvMeshFunctionObject(name, runTime, dict),
	volRegion(fvMeshFunctionObject::mesh_, dict),
	logFiles(obr_, name),
	chemistryModel_
	(
		fvMeshFunctionObject::mesh_.lookupObject<ChemistryModelType>
		(
			"chemistryProperties"
			)
	)
{
	resetName("specieReactionRates");
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class ChemistryModelType>
tnbLib::functionObjects::specieReactionRates<ChemistryModelType>::
~specieReactionRates()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class ChemistryModelType>
bool tnbLib::functionObjects::specieReactionRates<ChemistryModelType>::read
(
	const dictionary& dict
)
{
	regionFunctionObject::read(dict);

	return true;
}


template<class ChemistryModelType>
bool tnbLib::functionObjects::specieReactionRates<ChemistryModelType>::execute()
{
	return true;
}


template<class ChemistryModelType>
bool tnbLib::functionObjects::specieReactionRates<ChemistryModelType>::write()
{
	logFiles::write();

	const label nSpecie = chemistryModel_.nSpecie();
	const label nReaction = chemistryModel_.nReaction();

	// Region volume
	const scalar V = this->V();

	for (label ri = 0; ri < nReaction; ri++)
	{
		if (Pstream::master())
		{
			writeTime(file());
			file() << token::TAB << ri;
		}

		for (label si = 0; si < nSpecie; si++)
		{
			volScalarField::Internal RR
			(
				chemistryModel_.calculateRR(ri, si)
			);

			scalar sumVRRi = 0;

			if (isNull(cellIDs()))
			{
				sumVRRi = fvc::domainIntegrate(RR).value();
			}
			else
			{
				sumVRRi = gSum
				(
					scalarField(fvMeshFunctionObject::mesh_.V() * RR, cellIDs())
				);
			}

			if (Pstream::master())
			{
				file() << token::TAB << sumVRRi / V;
			}
		}

		if (Pstream::master())
		{
			file() << nl;
		}
	}

	if (Pstream::master())
	{
		file() << nl << endl;
	}

	return true;
}