#include <wideBand.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <basicSpecieMixture.hxx>
#include <unitConversion.hxx>

#include <Time.hxx>  // added by amir

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace radiationModels
	{
		namespace absorptionEmissionModels
		{
			defineTypeNameAndDebug(wideBand, 0);

			addToRunTimeSelectionTable
			(
				absorptionEmissionModel,
				wideBand,
				dictionary
			);
		}
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::radiationModels::absorptionEmissionModels::wideBand::wideBand
(
	const dictionary& dict,
	const fvMesh& mesh,
	const word& modelName
)
	:
	absorptionEmissionModel(dict, mesh),
	coeffsDict_(dict.subDict(modelName + "Coeffs")),
	speciesNames_(0),
	specieIndex_(label(0)),
	lookUpTablePtr_(),
	thermo_(mesh.lookupObject<fluidThermo>(basicThermo::dictName)),
	Yj_(nSpecies_),
	totalWaveLength_(0)
{
	label nBand = 0;
	forAllConstIter(dictionary, coeffsDict_, iter)
	{
		if (!iter().isDict()) continue;

		const dictionary& dict = iter().dict();
		dict.lookup("bandLimits") >> iBands_[nBand];
		totalWaveLength_ += iBands_[nBand][1] - iBands_[nBand][0];

		label nSpec = 0;
		forAllConstIter(dictionary, dict, iter)
		{
			if (!iter().isDict()) continue;

			const word& key = iter().keyword();
			if (nBand == 0)
			{
				speciesNames_.insert(key, nSpec);
			}
			else
			{
				if (!speciesNames_.found(key))
				{
					FatalErrorInFunction
						<< "specie: " << key << " is not in all the bands"
						<< nl << exit(FatalError);
				}
			}
			coeffs_[nBand][nSpec].initialise(dict.subDict(key));
			nSpec++;
		}
		nBand++;
	}
	nBands_ = nBand;

	if (coeffsDict_.found("lookUpTableFileName"))
	{
		const word name = coeffsDict_.lookup("lookUpTableFileName");
		if (name != "none")
		{
			lookUpTablePtr_.set
			(
				new interpolationLookUpTable<scalar>
				(
					fileName(coeffsDict_.lookup("lookUpTableFileName")),
					mesh.time().constant(),
					mesh
					)
			);

			if (!mesh.foundObject<volScalarField>("ft"))
			{
				FatalErrorInFunction
					<< "specie ft is not present to use with "
					<< "lookUpTableFileName " << nl
					<< exit(FatalError);
			}
		}
	}

	// Check that all the species on the dictionary are present in the
	// look-up table and save the corresponding indices of the look-up table

	label j = 0;
	forAllConstIter(HashTable<label>, speciesNames_, iter)
	{
		if (!lookUpTablePtr_.empty())
		{
			if (lookUpTablePtr_().found(iter.key()))
			{
				const label index =
					lookUpTablePtr_().findFieldIndex(iter.key());

				Info << "specie: " << iter.key() << " found on look-up table "
					<< " with index: " << index << endl;

				specieIndex_[iter()] = index;
			}
			else if (mesh.foundObject<volScalarField>(iter.key()))
			{
				Yj_.set(j, &mesh.lookupObjectRef<volScalarField>(iter.key()));
				specieIndex_[iter()] = 0;
				j++;
				Info << "specie: " << iter.key() << " is being solved" << endl;
			}
			else
			{
				FatalErrorInFunction
					<< "specie: " << iter.key()
					<< " is neither in look-up table: "
					<< lookUpTablePtr_().tableName()
					<< " nor is being solved" << nl
					<< exit(FatalError);
			}
		}
		else if (mesh.foundObject<volScalarField>(iter.key()))
		{
			Yj_.set(j, &mesh.lookupObjectRef<volScalarField>(iter.key()));
			specieIndex_[iter()] = 0;
			j++;
		}
		else
		{
			FatalErrorInFunction
				<< " there is no lookup table and the specie" << nl
				<< iter.key() << nl
				<< " is not found " << nl
				<< exit(FatalError);

		}
	}
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::radiationModels::absorptionEmissionModels::wideBand::~wideBand()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::volScalarField>
tnbLib::radiationModels::absorptionEmissionModels::wideBand::aCont
(
	const label bandi
) const
{
	const basicSpecieMixture& mixture =
		dynamic_cast<const basicSpecieMixture&>(thermo_);

	const volScalarField& T = thermo_.T();
	const volScalarField& p = thermo_.p();

	tmp<volScalarField> ta
	(
		volScalarField::New
		(
			"a",
			mesh(),
			dimensionedScalar(dimless / dimLength, 0)
		)
	);

	scalarField& a = ta.ref().primitiveFieldRef();

	forAll(a, celli)
	{
		forAllConstIter(HashTable<label>, speciesNames_, iter)
		{
			const label n = iter();
			scalar Xipi = 0;
			if (specieIndex_[n] != 0)
			{
				const volScalarField& ft =
					mesh_.lookupObject<volScalarField>("ft");

				const List<scalar>& Ynft = lookUpTablePtr_().lookUp(ft[celli]);

				// moles*pressure [atm]
				Xipi = Ynft[specieIndex_[n]] * paToAtm(p[celli]);
			}
			else
			{
				scalar invWt = 0;
				forAll(mixture.Y(), s)
				{
					invWt += mixture.Y(s)[celli] / mixture.Wi(s);
				}

				const label index = mixture.species()[iter.key()];

				const scalar Xk =
					mixture.Y(index)[celli] / (mixture.Wi(index)*invWt);

				Xipi = Xk * paToAtm(p[celli]);
			}

			scalar Ti = T[celli];

			const absorptionCoeffs::coeffArray& b =
				coeffs_[bandi][n].coeffs(T[celli]);

			if (coeffs_[bandi][n].invTemp())
			{
				Ti = 1.0 / T[celli];
			}

			a[celli] +=
				Xipi
				* (
				((((b[5] * Ti + b[4])*Ti + b[3])*Ti + b[2])*Ti + b[1])*Ti
					+ b[0]
					);
		}
	}

	return ta;
}


tnbLib::tmp<tnbLib::volScalarField>
tnbLib::radiationModels::absorptionEmissionModels::wideBand::eCont
(
	const label bandi
) const
{
	return aCont(bandi);
}


tnbLib::tmp<tnbLib::volScalarField>
tnbLib::radiationModels::absorptionEmissionModels::wideBand::ECont
(
	const label bandi
) const
{
	return absorptionEmissionModel::ECont(bandi);
}


void tnbLib::radiationModels::absorptionEmissionModels::wideBand::correct
(
	volScalarField& a,
	PtrList<volScalarField>& aLambda
) const
{
	a = dimensionedScalar(dimless / dimLength, 0);

	for (label j = 0; j < nBands_; j++)
	{
		aLambda[j].primitiveFieldRef() = this->a(j);

		a.primitiveFieldRef() +=
			aLambda[j].primitiveField()
			*(iBands_[j][1] - iBands_[j][0])
			/ totalWaveLength_;
	}

}


// ************************************************************************* //