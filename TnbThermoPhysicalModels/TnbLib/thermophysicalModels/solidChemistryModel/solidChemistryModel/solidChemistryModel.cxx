#include <solidChemistryModel.hxx>

#include <reactingMixture.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CompType, class SolidThermo>
tnbLib::solidChemistryModel<CompType, SolidThermo>::solidChemistryModel
(
	typename CompType::reactionThermo& thermo
)
	:
	CompType(thermo),
	ODESystem(),
	Ys_(this->solidThermo().composition().Y()),
	reactions_
	(
		dynamic_cast<const reactingMixture<SolidThermo>&>
		(
			this->solidThermo()
			)
	),
	solidThermo_
	(
		dynamic_cast<const reactingMixture<SolidThermo>&>
		(
			this->solidThermo()
			).speciesData()
	),
	nSolids_(Ys_.size()),
	nReaction_(reactions_.size()),
	RRs_(nSolids_),
	reactingCells_(this->mesh().nCells(), true)
{
	// create the fields for the chemistry sources
	forAll(RRs_, fieldi)
	{
		RRs_.set
		(
			fieldi,
			new volScalarField::Internal
			(
				IOobject
				(
					"RRs." + Ys_[fieldi].name(),
					this->mesh().time().timeName(),
					this->mesh(),
					IOobject::NO_READ,
					IOobject::NO_WRITE
				),
				this->mesh(),
				dimensionedScalar(dimMass / dimVolume / dimTime, 0)
			)
		);
	}
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class CompType, class SolidThermo>
tnbLib::solidChemistryModel<CompType, SolidThermo>::
~solidChemistryModel()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CompType, class SolidThermo>
tnbLib::scalar tnbLib::solidChemistryModel<CompType, SolidThermo>::solve
(
	const scalarField& deltaT
)
{
	NotImplemented;
	return 0;
}


template<class CompType, class SolidThermo>
tnbLib::tmp<tnbLib::volScalarField>
tnbLib::solidChemistryModel<CompType, SolidThermo>::tc() const
{
	NotImplemented;
	return volScalarField::null();
}


template<class CompType, class SolidThermo>
tnbLib::tmp<tnbLib::volScalarField>
tnbLib::solidChemistryModel<CompType, SolidThermo>::Qdot() const
{
	tmp<volScalarField> tQdot
	(
		volScalarField::New
		(
			"Qdot",
			this->mesh_,
			dimensionedScalar(dimEnergy / dimVolume / dimTime, 0)
		)
	);

	if (this->chemistry_)
	{
		scalarField& Qdot = tQdot.ref();

		forAll(Ys_, i)
		{
			forAll(Qdot, celli)
			{
				scalar hf = solidThermo_[i].Hc();
				Qdot[celli] -= hf * RRs_[i][celli];
			}
		}
	}

	return tQdot;
}


template<class CompType, class SolidThermo>
void tnbLib::solidChemistryModel<CompType, SolidThermo>::setCellReacting
(
	const label celli,
	const bool active
)
{
	reactingCells_[celli] = active;
}

// ************************************************************************* //