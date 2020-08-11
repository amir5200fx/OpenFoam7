#include <basicMultiComponentMixture.hxx>

#include <Time.hxx>  // added by amir

// * * * * * * * * * * * * * Static Member Functions * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(basicMultiComponentMixture, 0);
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::basicMultiComponentMixture::basicMultiComponentMixture
(
	const dictionary& thermoDict,
	const wordList& specieNames,
	const fvMesh& mesh,
	const word& phaseName
)
	:
	basicMixture(thermoDict, mesh, phaseName),
	species_(specieNames),
	active_(species_.size(), true),
	Y_(species_.size())
{
	tmp<volScalarField> tYdefault;

	forAll(species_, i)
	{
		IOobject header
		(
			IOobject::groupName(species_[i], phaseName),
			mesh.time().timeName(),
			mesh,
			IOobject::NO_READ
		);

		// check if field exists and can be read
		if (header.typeHeaderOk<volScalarField>(true))
		{
			Y_.set
			(
				i,
				new volScalarField
				(
					IOobject
					(
						IOobject::groupName(species_[i], phaseName),
						mesh.time().timeName(),
						mesh,
						IOobject::MUST_READ,
						IOobject::AUTO_WRITE
					),
					mesh
				)
			);
		}
		else
		{
			// Read Ydefault if not already read
			if (!tYdefault.valid())
			{
				word YdefaultName(IOobject::groupName("Ydefault", phaseName));

				IOobject timeIO
				(
					YdefaultName,
					mesh.time().timeName(),
					mesh,
					IOobject::MUST_READ,
					IOobject::NO_WRITE
				);

				IOobject constantIO
				(
					YdefaultName,
					mesh.time().constant(),
					mesh,
					IOobject::MUST_READ,
					IOobject::NO_WRITE
				);

				IOobject time0IO
				(
					YdefaultName,
					Time::timeName(0),
					mesh,
					IOobject::MUST_READ,
					IOobject::NO_WRITE
				);

				if (timeIO.typeHeaderOk<volScalarField>(true))
				{
					tYdefault = new volScalarField(timeIO, mesh);
				}
				else if (constantIO.typeHeaderOk<volScalarField>(true))
				{
					tYdefault = new volScalarField(constantIO, mesh);
				}
				else
				{
					tYdefault = new volScalarField(time0IO, mesh);
				}
			}

			Y_.set
			(
				i,
				new volScalarField
				(
					IOobject
					(
						IOobject::groupName(species_[i], phaseName),
						mesh.time().timeName(),
						mesh,
						IOobject::NO_READ,
						IOobject::AUTO_WRITE
					),
					tYdefault()
				)
			);
		}
	}

	// Do not enforce constraint of sum of mass fractions to equal 1 here
	// - not applicable to all models
}


// ************************************************************************* //