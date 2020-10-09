#include <dsmcFields.hxx>

#include <volFields.hxx>
#include <dictionary.hxx>
#include <dsmcCloud.hxx>
#include <constants.hxx>
#include <addToRunTimeSelectionTable.hxx>

using namespace tnbLib::constant;

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionObjects
	{
		defineTypeNameAndDebug(dsmcFields, 0);

		addToRunTimeSelectionTable
		(
			functionObject,
			dsmcFields,
			dictionary
		);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::functionObjects::dsmcFields::dsmcFields
(
	const word& name,
	const Time& runTime,
	const dictionary& dict
)
	:
	fvMeshFunctionObject(name, runTime, dict)
{
	read(dict);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::functionObjects::dsmcFields::~dsmcFields()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::functionObjects::dsmcFields::read(const dictionary& dict)
{
	return true;
}


bool tnbLib::functionObjects::dsmcFields::execute()
{
	return true;
}


bool tnbLib::functionObjects::dsmcFields::write()
{
	word rhoNMeanName = "rhoNMean";
	word rhoMMeanName = "rhoMMean";
	word momentumMeanName = "momentumMean";
	word linearKEMeanName = "linearKEMean";
	word internalEMeanName = "internalEMean";
	word iDofMeanName = "iDofMean";
	word fDMeanName = "fDMean";

	const volScalarField& rhoNMean = obr_.lookupObject<volScalarField>
		(
			rhoNMeanName
			);

	const volScalarField& rhoMMean = obr_.lookupObject<volScalarField>
		(
			rhoMMeanName
			);

	const volVectorField& momentumMean = obr_.lookupObject<volVectorField>
		(
			momentumMeanName
			);

	const volScalarField& linearKEMean = obr_.lookupObject<volScalarField>
		(
			linearKEMeanName
			);

	const volScalarField& internalEMean = obr_.lookupObject<volScalarField>
		(
			internalEMeanName
			);

	const volScalarField& iDofMean = obr_.lookupObject<volScalarField>
		(
			iDofMeanName
			);

	const volVectorField& fDMean = obr_.lookupObject<volVectorField>
		(
			fDMeanName
			);

	if (min(mag(rhoNMean)).value() > vSmall)
	{
		Info << "Calculating dsmcFields." << endl;

		Info << "    Calculating UMean field." << endl;
		volVectorField UMean
		(
			IOobject
			(
				"UMean",
				obr_.time().timeName(),
				obr_,
				IOobject::NO_READ
			),
			momentumMean / rhoMMean
		);

		Info << "    Calculating translationalT field." << endl;
		volScalarField translationalT
		(
			IOobject
			(
				"translationalT",
				obr_.time().timeName(),
				obr_,
				IOobject::NO_READ
			),

			2.0 / (3.0*physicoChemical::k.value()*rhoNMean)
			*(linearKEMean - 0.5*rhoMMean*(UMean & UMean))
		);

		Info << "    Calculating internalT field." << endl;
		volScalarField internalT
		(
			IOobject
			(
				"internalT",
				obr_.time().timeName(),
				obr_,
				IOobject::NO_READ
			),
			(2.0 / physicoChemical::k.value())*(internalEMean / iDofMean)
		);

		Info << "    Calculating overallT field." << endl;
		volScalarField overallT
		(
			IOobject
			(
				"overallT",
				obr_.time().timeName(),
				obr_,
				IOobject::NO_READ
			),
			2.0 / (physicoChemical::k.value()*(3.0*rhoNMean + iDofMean))
			*(linearKEMean - 0.5*rhoMMean*(UMean & UMean) + internalEMean)
		);

		Info << "    Calculating pressure field." << endl;
		volScalarField p
		(
			IOobject
			(
				"p",
				obr_.time().timeName(),
				obr_,
				IOobject::NO_READ
			),
			physicoChemical::k.value()*rhoNMean*translationalT
		);

		volScalarField::Boundary& pBf = p.boundaryFieldRef();

		forAll(mesh_.boundaryMesh(), i)
		{
			const polyPatch& patch = mesh_.boundaryMesh()[i];

			if (isA<wallPolyPatch>(patch))
			{
				pBf[i] =
					fDMean.boundaryField()[i]
					& (patch.faceAreas() / mag(patch.faceAreas()));
			}
		}

		Info << "    mag(UMean) max/min : "
			<< max(mag(UMean)).value() << " "
			<< min(mag(UMean)).value() << endl;

		Info << "    translationalT max/min : "
			<< max(translationalT).value() << " "
			<< min(translationalT).value() << endl;

		Info << "    internalT max/min : "
			<< max(internalT).value() << " "
			<< min(internalT).value() << endl;

		Info << "    overallT max/min : "
			<< max(overallT).value() << " "
			<< min(overallT).value() << endl;

		Info << "    p max/min : "
			<< max(p).value() << " "
			<< min(p).value() << endl;

		UMean.write();

		translationalT.write();

		internalT.write();

		overallT.write();

		p.write();

		Info << "dsmcFields written." << nl << endl;

		return true;
	}
	else
	{
		Info << "Small value (" << min(mag(rhoNMean))
			<< ") found in rhoNMean field. "
			<< "Not calculating dsmcFields to avoid division by zero."
			<< endl;

		return false;
	}
}


// ************************************************************************* //