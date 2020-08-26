#include <greyMean.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <unitConversion.hxx>
#include <extrapolatedCalculatedFvPatchFields.hxx>
#include <basicSpecieMixture.hxx>

#include <Time.hxx>  // added by amir

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace radiationModels
	{
		namespace absorptionEmissionModels
		{
			defineTypeNameAndDebug(greyMean, 0);

			addToRunTimeSelectionTable
			(
				absorptionEmissionModel,
				greyMean,
				dictionary
			);
		}
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::radiationModels::absorptionEmissionModels::greyMean::greyMean
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
	Yj_(nSpecies_)
{
	if (!isA<basicSpecieMixture>(thermo_))
	{
		FatalErrorInFunction
			<< "Model requires a multi-component thermo package"
			<< abort(FatalError);
	}

	label nFunc = 0;
	forAllConstIter(dictionary, coeffsDict_, iter)
	{
		// safety:
		if (!iter().isDict())
		{
			continue;
		}
		const word& key = iter().keyword();
		speciesNames_.insert(key, nFunc);
		const dictionary& dict = iter().dict();
		coeffs_[nFunc].initialise(dict);
		nFunc++;
	}

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
				label index = lookUpTablePtr_().findFieldIndex(iter.key());

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
				<< " there is not lookup table and the specie" << nl
				<< iter.key() << nl
				<< " is not found " << nl
				<< exit(FatalError);

		}
	}
}

// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::radiationModels::absorptionEmissionModels::greyMean::~greyMean()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::volScalarField>
tnbLib::radiationModels::absorptionEmissionModels::greyMean::aCont
(
	const label bandI
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
			"aCont" + name(bandI),
			mesh(),
			dimensionedScalar(dimless / dimLength, 0),
			extrapolatedCalculatedFvPatchVectorField::typeName
		)
	);

	scalarField& a = ta.ref().primitiveFieldRef();

	forAll(a, celli)
	{
		forAllConstIter(HashTable<label>, speciesNames_, iter)
		{
			label n = iter();
			scalar Xipi = 0.0;
			if (specieIndex_[n] != 0)
			{
				// Specie found in the lookUpTable.
				const volScalarField& ft =
					mesh_.lookupObject<volScalarField>("ft");

				const List<scalar>& Ynft = lookUpTablePtr_().lookUp(ft[celli]);
				// moles x pressure [atm]
				Xipi = Ynft[specieIndex_[n]] * paToAtm(p[celli]);
			}
			else
			{
				scalar invWt = 0.0;
				forAll(mixture.Y(), s)
				{
					invWt += mixture.Y(s)[celli] / mixture.Wi(s);
				}

				label index = mixture.species()[iter.key()];
				scalar Xk = mixture.Y(index)[celli] / (mixture.Wi(index)*invWt);

				Xipi = Xk * paToAtm(p[celli]);
			}

			const absorptionCoeffs::coeffArray& b = coeffs_[n].coeffs(T[celli]);

			scalar Ti = T[celli];
			// negative temperature exponents
			if (coeffs_[n].invTemp())
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
	ta.ref().correctBoundaryConditions();
	return ta;
}


tnbLib::tmp<tnbLib::volScalarField>
tnbLib::radiationModels::absorptionEmissionModels::greyMean::eCont
(
	const label bandI
) const
{
	return aCont(bandI);
}


tnbLib::tmp<tnbLib::volScalarField>
tnbLib::radiationModels::absorptionEmissionModels::greyMean::ECont
(
	const label bandI
) const
{
	return absorptionEmissionModel::ECont(bandI);
}


// ************************************************************************* //