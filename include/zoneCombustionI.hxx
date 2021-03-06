#pragma once
// * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * * //

template<class ReactionThermo>
tnbLib::tmp<tnbLib::fvScalarMatrix>
tnbLib::combustionModels::zoneCombustion<ReactionThermo>::filter
(
	const tmp<fvScalarMatrix>& tR
) const
{
	fvScalarMatrix& R = tR.ref();
	scalarField& Su = R.source();
	scalarField filteredField(Su.size(), 0);

	forAll(zoneNames_, zonei)
	{
		const labelList& cells = this->mesh().cellZones()[zoneNames_[zonei]];

		forAll(cells, i)
		{
			filteredField[cells[i]] = Su[cells[i]];
		}
	}

	Su = filteredField;

	if (R.hasDiag())
	{
		scalarField& Sp = R.diag();

		forAll(zoneNames_, zonei)
		{
			const labelList& cells =
				this->mesh().cellZones()[zoneNames_[zonei]];

			forAll(cells, i)
			{
				filteredField[cells[i]] = Sp[cells[i]];
			}
		}

		Sp = filteredField;
	}

	return tR;
}


template<class ReactionThermo>
tnbLib::tmp<tnbLib::volScalarField>
tnbLib::combustionModels::zoneCombustion<ReactionThermo>::filter
(
	const tmp<volScalarField>& tS
) const
{
	scalarField& S = tS.ref();
	scalarField filteredField(S.size(), 0);

	forAll(zoneNames_, zonei)
	{
		const labelList& cells = this->mesh().cellZones()[zoneNames_[zonei]];

		forAll(cells, i)
		{
			filteredField[cells[i]] = S[cells[i]];
		}
	}

	S = filteredField;

	return tS;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class ReactionThermo>
tnbLib::combustionModels::zoneCombustion<ReactionThermo>::zoneCombustion
(
	const word& modelType,
	ReactionThermo& thermo,
	const compressibleTurbulenceModel& turb,
	const word& combustionProperties
)
	:
	CombustionModel<ReactionThermo>
	(
		modelType,
		thermo,
		turb,
		combustionProperties
		),
	combustionModelPtr_
	(
		CombustionModel<ReactionThermo>::New
		(
			thermo,
			turb,
			"zoneCombustionProperties"
		)
	),
	zoneNames_(this->coeffs().lookup("zones"))
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class ReactionThermo>
tnbLib::combustionModels::zoneCombustion<ReactionThermo>::~zoneCombustion()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

template<class ReactionThermo>
ReactionThermo& tnbLib::combustionModels::zoneCombustion<ReactionThermo>::thermo()
{
	return combustionModelPtr_->thermo();
}


template<class ReactionThermo>
const ReactionThermo&
tnbLib::combustionModels::zoneCombustion<ReactionThermo>::thermo() const
{
	return combustionModelPtr_->thermo();
}


template<class ReactionThermo>
void tnbLib::combustionModels::zoneCombustion<ReactionThermo>::correct()
{
	combustionModelPtr_->correct();
}


template<class ReactionThermo>
tnbLib::tmp<tnbLib::fvScalarMatrix>
tnbLib::combustionModels::zoneCombustion<ReactionThermo>::R
(
	volScalarField& Y
) const
{
	return filter(combustionModelPtr_->R(Y));
}


template<class ReactionThermo>
tnbLib::tmp<tnbLib::volScalarField>
tnbLib::combustionModels::zoneCombustion<ReactionThermo>::Qdot() const
{
	return filter(combustionModelPtr_->Qdot());
}


template<class ReactionThermo>
bool tnbLib::combustionModels::zoneCombustion<ReactionThermo>::read()
{
	if (CombustionModel<ReactionThermo>::read())
	{
		combustionModelPtr_->read();
		return true;
	}
	else
	{
		return false;
	}
}


// ************************************************************************* //