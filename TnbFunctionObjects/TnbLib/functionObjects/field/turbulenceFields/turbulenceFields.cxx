#include <turbulenceFields.hxx>

#include <turbulentTransportModel.hxx>
#include <turbulentFluidThermoModel.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionObjects
	{
		defineTypeNameAndDebug(turbulenceFields, 0);

		addToRunTimeSelectionTable
		(
			functionObject,
			turbulenceFields,
			dictionary
		);
	}
}

template<>
const char* tnbLib::NamedEnum
<
	tnbLib::functionObjects::turbulenceFields::compressibleField,
	9
>::names[] =
{
	"k",
	"epsilon",
	"omega",
	"mut",
	"muEff",
	"alphat",
	"alphaEff",
	"R",
	"devRhoReff"
};

const tnbLib::NamedEnum
<
	tnbLib::functionObjects::turbulenceFields::compressibleField,
	9
> tnbLib::functionObjects::turbulenceFields::compressibleFieldNames_;

template<>
const char* tnbLib::NamedEnum
<
	tnbLib::functionObjects::turbulenceFields::incompressibleField,
	7
>::names[] =
{
	"k",
	"epsilon",
	"omega",
	"nut",
	"nuEff",
	"R",
	"devReff"
};

const tnbLib::NamedEnum
<
	tnbLib::functionObjects::turbulenceFields::incompressibleField,
	7
> tnbLib::functionObjects::turbulenceFields::incompressibleFieldNames_;


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::functionObjects::turbulenceFields::turbulenceFields
(
	const word& name,
	const Time& runTime,
	const dictionary& dict
)
	:
	fvMeshFunctionObject(name, runTime, dict),
	fieldSet_()
{
	read(dict);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::functionObjects::turbulenceFields::~turbulenceFields()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

const tnbLib::word& tnbLib::functionObjects::turbulenceFields::modelName()
{
	return tnbLib::turbulenceModel::propertiesName;
}


bool tnbLib::functionObjects::turbulenceFields::read(const dictionary& dict)
{
	if (dict.found("field"))
	{
		fieldSet_.insert(word(dict.lookup("field")));
	}
	else
	{
		fieldSet_.insert(wordList(dict.lookup("fields")));
	}

	if (dict.lookupOrDefault<Switch>("prefix", false))
	{
		prefix_ = modelName() + ':';
	}
	else
	{
		prefix_ = word::null;
	}

	Info << type() << " " << name() << ": ";
	if (fieldSet_.size())
	{
		Info << "storing fields:" << nl;
		forAllConstIter(wordHashSet, fieldSet_, iter)
		{
			Info << "    " << prefix_ + iter.key() << nl;
		}
		Info << endl;
	}
	else
	{
		Info << "no fields requested to be stored" << nl << endl;
	}

	return true;
}


bool tnbLib::functionObjects::turbulenceFields::execute()
{
	if (obr_.foundObject<compressible::turbulenceModel>(modelName()))
	{
		const compressible::turbulenceModel& model =
			obr_.lookupObject<compressible::turbulenceModel>(modelName());

		forAllConstIter(wordHashSet, fieldSet_, iter)
		{
			const word& f = iter.key();
			switch (compressibleFieldNames_[f])
			{
			case compressibleField::k:
			{
				processField<scalar>(f, model.k());
				break;
			}
			case compressibleField::epsilon:
			{
				processField<scalar>(f, model.epsilon());
				break;
			}
			case compressibleField::omega:
			{
				processField<scalar>(f, omega(model));
				break;
			}
			case compressibleField::mut:
			{
				processField<scalar>(f, model.mut());
				break;
			}
			case compressibleField::muEff:
			{
				processField<scalar>(f, model.muEff());
				break;
			}
			case compressibleField::alphat:
			{
				processField<scalar>(f, model.alphat());
				break;
			}
			case compressibleField::alphaEff:
			{
				processField<scalar>(f, model.alphaEff());
				break;
			}
			case compressibleField::R:
			{
				processField<symmTensor>(f, model.R());
				break;
			}
			case compressibleField::devRhoReff:
			{
				processField<symmTensor>(f, model.devRhoReff());
				break;
			}
			default:
			{
				FatalErrorInFunction
					<< "Invalid field selection" << exit(FatalError);
			}
			}
		}
	}
	else if (obr_.foundObject<compressibleTurbulenceModel>(modelName()))
	{
		const compressibleTurbulenceModel& model =
			obr_.lookupObject<compressibleTurbulenceModel>(modelName());

		forAllConstIter(wordHashSet, fieldSet_, iter)
		{
			const word& f = iter.key();
			switch (compressibleFieldNames_[f])
			{
			case compressibleField::k:
			{
				processField<scalar>(f, model.k());
				break;
			}
			case compressibleField::epsilon:
			{
				processField<scalar>(f, model.epsilon());
				break;
			}
			case compressibleField::omega:
			{
				processField<scalar>(f, omega(model));
				break;
			}
			case compressibleField::mut:
			{
				processField<scalar>(f, model.mut());
				break;
			}
			case compressibleField::muEff:
			{
				processField<scalar>(f, model.muEff());
				break;
			}
			case compressibleField::R:
			{
				processField<symmTensor>(f, model.R());
				break;
			}
			case compressibleField::devRhoReff:
			{
				processField<symmTensor>(f, model.devRhoReff());
				break;
			}
			default:
			{
				FatalErrorInFunction
					<< "Invalid field selection" << exit(FatalError);
			}
			}
		}
	}
	else if (obr_.foundObject<incompressible::turbulenceModel>(modelName()))
	{
		const incompressible::turbulenceModel& model =
			obr_.lookupObject<incompressible::turbulenceModel>(modelName());

		forAllConstIter(wordHashSet, fieldSet_, iter)
		{
			const word& f = iter.key();
			switch (incompressibleFieldNames_[f])
			{
			case incompressibleField::k:
			{
				processField<scalar>(f, model.k());
				break;
			}
			case incompressibleField::epsilon:
			{
				processField<scalar>(f, model.epsilon());
				break;
			}
			case incompressibleField::omega:
			{
				processField<scalar>(f, omega(model));
				break;
			}
			case incompressibleField::nut:
			{
				processField<scalar>(f, model.nut());
				break;
			}
			case incompressibleField::nuEff:
			{
				processField<scalar>(f, model.nuEff());
				break;
			}
			case incompressibleField::R:
			{
				processField<symmTensor>(f, model.R());
				break;
			}
			case incompressibleField::devReff:
			{
				processField<symmTensor>(f, model.devReff());
				break;
			}
			default:
			{
				FatalErrorInFunction
					<< "Invalid field selection" << exit(FatalError);
			}
			}
		}
	}
	else
	{
		FatalErrorInFunction
			<< "Turbulence model not found in database, deactivating"
			<< exit(FatalError);
	}

	return true;
}


bool tnbLib::functionObjects::turbulenceFields::write()
{
	forAllConstIter(wordHashSet, fieldSet_, iter)
	{
		const word fieldName = prefix_ + iter.key();
		writeObject(fieldName);
	}

	return true;
}


// ************************************************************************* //