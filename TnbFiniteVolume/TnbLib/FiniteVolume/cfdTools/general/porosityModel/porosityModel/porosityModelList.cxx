#include <porosityModelList.hxx>

#include <volFields.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::porosityModelList::porosityModelList
(
	const fvMesh& mesh,
	const dictionary& dict
)
	:
	PtrList<porosityModel>(),
	mesh_(mesh)
{
	reset(dict);

	active(true);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::porosityModelList::~porosityModelList()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::porosityModelList::active(const bool warn) const
{
	bool a = false;
	forAll(*this, i)
	{
		a = a || this->operator[](i).active();
	}

	if (warn && this->size() && !a)
	{
		Info << "No porosity models active" << endl;
	}

	return a;
}


void tnbLib::porosityModelList::reset(const dictionary& dict)
{
	label count = 0;
	forAllConstIter(dictionary, dict, iter)
	{
		if (iter().isDict())
		{
			count++;
		}
	}

	this->setSize(count);
	label i = 0;
	forAllConstIter(dictionary, dict, iter)
	{
		if (iter().isDict())
		{
			const word& name = iter().keyword();
			const dictionary& modelDict = iter().dict();

			this->set
			(
				i++,
				porosityModel::New(name, mesh_, modelDict)
			);
		}
	}
}


bool tnbLib::porosityModelList::read(const dictionary& dict)
{
	bool allOk = true;
	forAll(*this, i)
	{
		porosityModel& pm = this->operator[](i);
		bool ok = pm.read(dict.subDict(pm.name()));
		allOk = (allOk && ok);
	}
	return allOk;
}


bool tnbLib::porosityModelList::writeData(Ostream& os) const
{
	forAll(*this, i)
	{
		os << nl;
		this->operator[](i).writeData(os);
	}

	return os.good();
}


void tnbLib::porosityModelList::addResistance
(
	fvVectorMatrix& UEqn
)
{
	forAll(*this, i)
	{
		this->operator[](i).addResistance(UEqn);
	}
}


void tnbLib::porosityModelList::addResistance
(
	fvVectorMatrix& UEqn,
	const volScalarField& rho,
	const volScalarField& mu
)
{
	forAll(*this, i)
	{
		this->operator[](i).addResistance(UEqn, rho, mu);
	}
}


void tnbLib::porosityModelList::addResistance
(
	const fvVectorMatrix& UEqn,
	volTensorField& AU,
	bool correctAUprocBC
)
{
	forAll(*this, i)
	{
		this->operator[](i).addResistance(UEqn, AU, correctAUprocBC);
	}
}


// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

FoamFiniteVolume_EXPORT tnbLib::Ostream& tnbLib::operator<<
(
	Ostream& os,
	const porosityModelList& models
	)
{
	models.writeData(os);
	return os;
}


// ************************************************************************* //