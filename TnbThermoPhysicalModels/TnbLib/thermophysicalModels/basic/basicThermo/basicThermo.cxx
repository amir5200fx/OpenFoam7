#include <basicThermo.hxx>

#include <zeroGradientFvPatchFields.hxx>
#include <fixedEnergyFvPatchScalarField.hxx>
#include <gradientEnergyFvPatchScalarField.hxx>
#include <mixedEnergyFvPatchScalarField.hxx>
#include <fixedJumpFvPatchFields.hxx>
#include <fixedJumpAMIFvPatchFields.hxx>
#include <energyJumpFvPatchScalarField.hxx>
#include <energyJumpAMIFvPatchScalarField.hxx>

#include <fixedEnergyFvPatchScalarField.hxx>  // added by amir
#include <gradientEnergyFvPatchScalarField.hxx>  // added by amir
#include <mixedEnergyFvPatchScalarField.hxx>  // added by amir

#include <Time.hxx> // added by amir
#include <fixedValueFvPatchFields.hxx>  // added by amir
#include <fixedGradientFvPatchFields.hxx>  // added by amir
#include <mixedFvPatchFields.hxx>  // added by amir

/* * * * * * * * * * * * * * * private static data * * * * * * * * * * * * * */

namespace tnbLib
{
	defineTypeNameAndDebug(basicThermo, 0);
	defineRunTimeSelectionTable(basicThermo, fvMesh);
}

const tnbLib::word tnbLib::basicThermo::dictName("thermophysicalProperties");


// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

tnbLib::wordList tnbLib::basicThermo::heBoundaryBaseTypes()
{
	const volScalarField::Boundary& tbf =
		this->T_.boundaryField();

	wordList hbt(tbf.size(), word::null);

	forAll(tbf, patchi)
	{
		if (isA<fixedJumpFvPatchScalarField>(tbf[patchi]))
		{
			const fixedJumpFvPatchScalarField& pf =
				dynamic_cast<const fixedJumpFvPatchScalarField&>(tbf[patchi]);

			hbt[patchi] = pf.interfaceFieldType();
		}
		else if (isA<fixedJumpAMIFvPatchScalarField>(tbf[patchi]))
		{
			const fixedJumpAMIFvPatchScalarField& pf =
				dynamic_cast<const fixedJumpAMIFvPatchScalarField&>
				(
					tbf[patchi]
					);

			hbt[patchi] = pf.interfaceFieldType();
		}
	}

	return hbt;
}


tnbLib::wordList tnbLib::basicThermo::heBoundaryTypes()
{
	const volScalarField::Boundary& tbf =
		this->T_.boundaryField();

	wordList hbt = tbf.types();

	forAll(tbf, patchi)
	{
		if (isA<fixedValueFvPatchScalarField>(tbf[patchi]))
		{
			hbt[patchi] = fixedEnergyFvPatchScalarField::typeName;
		}
		else if
			(
				isA<zeroGradientFvPatchScalarField>(tbf[patchi])
				|| isA<fixedGradientFvPatchScalarField>(tbf[patchi])
				)
		{
			hbt[patchi] = gradientEnergyFvPatchScalarField::typeName;
		}
		else if (isA<mixedFvPatchScalarField>(tbf[patchi]))
		{
			hbt[patchi] = mixedEnergyFvPatchScalarField::typeName;
		}
		else if (isA<fixedJumpFvPatchScalarField>(tbf[patchi]))
		{
			hbt[patchi] = energyJumpFvPatchScalarField::typeName;
		}
		else if (isA<fixedJumpAMIFvPatchScalarField>(tbf[patchi]))
		{
			hbt[patchi] = energyJumpAMIFvPatchScalarField::typeName;
		}
		else if (tbf[patchi].type() == "energyRegionCoupledFvPatchScalarField")
		{
			hbt[patchi] = "energyRegionCoupledFvPatchScalarField";
		}
	}

	return hbt;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::volScalarField& tnbLib::basicThermo::lookupOrConstruct
(
	const fvMesh& mesh,
	const char* name
) const
{
	if (!mesh.objectRegistry::foundObject<volScalarField>(name))
	{
		volScalarField* fPtr
		(
			new volScalarField
			(
				IOobject
				(
					name,
					mesh.time().timeName(),
					mesh,
					IOobject::MUST_READ,
					IOobject::AUTO_WRITE
				),
				mesh
			)
		);

		// Transfer ownership of this object to the objectRegistry
		fPtr->store(fPtr);
	}

	return mesh.objectRegistry::lookupObjectRef<volScalarField>(name);
}


tnbLib::basicThermo::basicThermo
(
	const fvMesh& mesh,
	const word& phaseName
)
	:
	IOdictionary
	(
		IOobject
		(
			phasePropertyName(dictName, phaseName),
			mesh.time().constant(),
			mesh,
			IOobject::MUST_READ_IF_MODIFIED,
			IOobject::NO_WRITE
		)
	),

	phaseName_(phaseName),

	p_(lookupOrConstruct(mesh, "p")),

	T_
	(
		IOobject
		(
			phasePropertyName("T"),
			mesh.time().timeName(),
			mesh,
			IOobject::MUST_READ,
			IOobject::AUTO_WRITE
		),
		mesh
	),

	alpha_
	(
		IOobject
		(
			phasePropertyName("thermo:alpha"),
			mesh.time().timeName(),
			mesh,
			IOobject::READ_IF_PRESENT,
			IOobject::NO_WRITE
		),
		mesh,
		dimensionedScalar(dimensionSet(1, -1, -1, 0, 0), Zero)
	),

	dpdt_(lookupOrDefault<Switch>("dpdt", true))
{}


tnbLib::basicThermo::basicThermo
(
	const fvMesh& mesh,
	const dictionary& dict,
	const word& phaseName
)
	:
	IOdictionary
	(
		IOobject
		(
			phasePropertyName(dictName, phaseName),
			mesh.time().constant(),
			mesh,
			IOobject::NO_READ,
			IOobject::NO_WRITE
		),
		dict
	),

	phaseName_(phaseName),

	p_(lookupOrConstruct(mesh, "p")),

	T_
	(
		IOobject
		(
			phasePropertyName("T"),
			mesh.time().timeName(),
			mesh,
			IOobject::MUST_READ,
			IOobject::AUTO_WRITE
		),
		mesh
	),

	alpha_
	(
		IOobject
		(
			phasePropertyName("thermo:alpha"),
			mesh.time().timeName(),
			mesh,
			IOobject::READ_IF_PRESENT,
			IOobject::NO_WRITE
		),
		mesh,
		dimensionedScalar(dimensionSet(1, -1, -1, 0, 0), Zero)
	)
{}


// * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::basicThermo> tnbLib::basicThermo::New
(
	const fvMesh& mesh,
	const word& phaseName
)
{
	return New<basicThermo>(mesh, phaseName);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::basicThermo::~basicThermo()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

const tnbLib::basicThermo& tnbLib::basicThermo::lookupThermo
(
	const fvPatchScalarField& pf
)
{
	if (pf.db().foundObject<basicThermo>(dictName))
	{
		return pf.db().lookupObject<basicThermo>(dictName);
	}
	else
	{
		HashTable<const basicThermo*> thermos =
			pf.db().lookupClass<basicThermo>();

		for
			(
				HashTable<const basicThermo*>::iterator iter = thermos.begin();
				iter != thermos.end();
				++iter
				)
		{
			if
				(
					&(iter()->he().internalField())
					== &(pf.internalField())
					)
			{
				return *iter();
			}
		}
	}

	return pf.db().lookupObject<basicThermo>(dictName);
}


void tnbLib::basicThermo::validate
(
	const string& app,
	const word& a
) const
{
	if (!(he().name() == phasePropertyName(a)))
	{
		FatalErrorInFunction
			<< "Supported energy type is " << phasePropertyName(a)
			<< ", thermodynamics package provides " << he().name()
			<< exit(FatalError);
	}
}

void tnbLib::basicThermo::validate
(
	const string& app,
	const word& a,
	const word& b
) const
{
	if
		(
			!(
				he().name() == phasePropertyName(a)
				|| he().name() == phasePropertyName(b)
				)
			)
	{
		FatalErrorInFunction
			<< "Supported energy types are " << phasePropertyName(a)
			<< " and " << phasePropertyName(b)
			<< ", thermodynamics package provides " << he().name()
			<< exit(FatalError);
	}
}

void tnbLib::basicThermo::validate
(
	const string& app,
	const word& a,
	const word& b,
	const word& c
) const
{
	if
		(
			!(
				he().name() == phasePropertyName(a)
				|| he().name() == phasePropertyName(b)
				|| he().name() == phasePropertyName(c)
				)
			)
	{
		FatalErrorInFunction
			<< "Supported energy types are " << phasePropertyName(a)
			<< ", " << phasePropertyName(b)
			<< " and " << phasePropertyName(c)
			<< ", thermodynamics package provides " << he().name()
			<< exit(FatalError);
	}
}

void tnbLib::basicThermo::validate
(
	const string& app,
	const word& a,
	const word& b,
	const word& c,
	const word& d
) const
{
	if
		(
			!(
				he().name() == phasePropertyName(a)
				|| he().name() == phasePropertyName(b)
				|| he().name() == phasePropertyName(c)
				|| he().name() == phasePropertyName(d)
				)
			)
	{
		FatalErrorInFunction
			<< "Supported energy types are " << phasePropertyName(a)
			<< ", " << phasePropertyName(b)
			<< ", " << phasePropertyName(c)
			<< " and " << phasePropertyName(d)
			<< ", thermodynamics package provides " << he().name()
			<< exit(FatalError);
	}
}


tnbLib::wordList tnbLib::basicThermo::splitThermoName
(
	const word& thermoName,
	const int nCmpt
)
{
	wordList cmpts(nCmpt);

	string::size_type beg = 0, end = 0, endb = 0, endc = 0;
	int i = 0;

	while
		(
		(endb = thermoName.find('<', beg)) != string::npos
			|| (endc = thermoName.find(',', beg)) != string::npos
			)
	{
		if (endb == string::npos)
		{
			end = endc;
		}
		else if ((endc = thermoName.find(',', beg)) != string::npos)
		{
			end = min(endb, endc);
		}
		else
		{
			end = endb;
		}

		if (beg < end)
		{
			cmpts[i] = thermoName.substr(beg, end - beg);
			cmpts[i++].replaceAll(">", "");

			// If the number of number of components in the name
			// is greater than nCmpt return an empty list
			if (i == nCmpt)
			{
				return wordList();
			}
		}
		beg = end + 1;
	}

	// If the number of number of components in the name is not equal to nCmpt
	// return an empty list
	if (i + 1 != nCmpt)
	{
		return wordList();
	}

	if (beg < thermoName.size())
	{
		cmpts[i] = thermoName.substr(beg, string::npos);
		cmpts[i].replaceAll(">", "");
	}

	return cmpts;
}


tnbLib::volScalarField& tnbLib::basicThermo::p()
{
	return p_;
}


const tnbLib::volScalarField& tnbLib::basicThermo::p() const
{
	return p_;
}


const tnbLib::volScalarField& tnbLib::basicThermo::T() const
{
	return T_;
}


tnbLib::volScalarField& tnbLib::basicThermo::T()
{
	return T_;
}


const tnbLib::volScalarField& tnbLib::basicThermo::alpha() const
{
	return alpha_;
}


const tnbLib::scalarField& tnbLib::basicThermo::alpha(const label patchi) const
{
	return alpha_.boundaryField()[patchi];
}


bool tnbLib::basicThermo::read()
{
	return regIOobject::read();
}


// ************************************************************************* //