#include <MRFZoneList.hxx>

#include <volFields.hxx>
#include <surfaceFields.hxx>  // added by amir
#include <fixedValueFvsPatchFields.hxx>

#include <FieldReuseFunctions.hxx>  // added by amir
#include <FieldFieldReuseFunctions.hxx>  // added by amir
#include <GeometricFieldReuseFunctions.hxx>  // added by amir

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::MRFZoneList::MRFZoneList
(
	const fvMesh& mesh,
	const dictionary& dict
)
	:
	PtrList<MRFZone>(),
	mesh_(mesh)
{
	reset(dict);

	active(true);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::MRFZoneList::~MRFZoneList()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::MRFZoneList::active(const bool warn) const
{
	bool a = false;
	forAll(*this, i)
	{
		a = a || this->operator[](i).active();
	}

	if (warn && this->size() && !a)
	{
		Info << "    No MRF zones active" << endl;
	}

	return a;
}


void tnbLib::MRFZoneList::reset(const dictionary& dict)
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

			Info << "    creating MRF zone: " << name << endl;

			this->set
			(
				i++,
				new MRFZone(name, mesh_, modelDict)
			);
		}
	}
}


bool tnbLib::MRFZoneList::read(const dictionary& dict)
{
	bool allOk = true;
	forAll(*this, i)
	{
		MRFZone& pm = this->operator[](i);
		bool ok = pm.read(dict.subDict(pm.name()));
		allOk = (allOk && ok);
	}
	return allOk;
}


bool tnbLib::MRFZoneList::writeData(Ostream& os) const
{
	forAll(*this, i)
	{
		os << nl;
		this->operator[](i).writeData(os);
	}

	return os.good();
}


void tnbLib::MRFZoneList::addAcceleration
(
	const volVectorField& U,
	volVectorField& ddtU
) const
{
	forAll(*this, i)
	{
		operator[](i).addCoriolis(U, ddtU);
	}
}


void tnbLib::MRFZoneList::addAcceleration(fvVectorMatrix& UEqn) const
{
	forAll(*this, i)
	{
		operator[](i).addCoriolis(UEqn);
	}
}


void tnbLib::MRFZoneList::addAcceleration
(
	const volScalarField& rho,
	fvVectorMatrix& UEqn
) const
{
	forAll(*this, i)
	{
		operator[](i).addCoriolis(rho, UEqn);
	}
}


tnbLib::tmp<tnbLib::volVectorField> tnbLib::MRFZoneList::DDt
(
	const volVectorField& U
) const
{
	tmp<volVectorField> tacceleration
	(
		volVectorField::New
		(
			"MRFZoneList:acceleration",
			U.mesh(),
			dimensionedVector(U.dimensions() / dimTime, Zero)
		)
	);
	volVectorField& acceleration = tacceleration.ref();

	forAll(*this, i)
	{
		operator[](i).addCoriolis(U, acceleration);
	}

	return tacceleration;
}


tnbLib::tmp<tnbLib::volVectorField> tnbLib::MRFZoneList::DDt
(
	const volScalarField& rho,
	const volVectorField& U
) const
{
	return rho * DDt(U);
}


void tnbLib::MRFZoneList::makeRelative(volVectorField& U) const
{
	forAll(*this, i)
	{
		operator[](i).makeRelative(U);
	}
}


void tnbLib::MRFZoneList::makeRelative(surfaceScalarField& phi) const
{
	forAll(*this, i)
	{
		operator[](i).makeRelative(phi);
	}
}


tnbLib::tmp<tnbLib::surfaceScalarField> tnbLib::MRFZoneList::relative
(
	const tmp<surfaceScalarField>& tphi
) const
{
	if (size())
	{
		tmp<surfaceScalarField> rphi
		(
			New
			(
				tphi,
				"relative(" + tphi().name() + ')',
				tphi().dimensions(),
				true
			)
		);

		makeRelative(rphi.ref());

		tphi.clear();

		return rphi;
	}
	else
	{
		return tmp<surfaceScalarField>(tphi, true);
	}
}


tnbLib::tmp<tnbLib::FieldField<tnbLib::fvsPatchField, tnbLib::scalar>>
tnbLib::MRFZoneList::relative
(
	const tmp<FieldField<fvsPatchField, scalar>>& tphi
) const
{
	if (size())
	{
		tmp<FieldField<fvsPatchField, scalar>> rphi(New(tphi, true));

		forAll(*this, i)
		{
			operator[](i).makeRelative(rphi.ref());
		}

		tphi.clear();

		return rphi;
	}
	else
	{
		return tmp<FieldField<fvsPatchField, scalar>>(tphi, true);
	}
}


tnbLib::tmp<tnbLib::Field<tnbLib::scalar>>
tnbLib::MRFZoneList::relative
(
	const tmp<Field<scalar>>& tphi,
	const label patchi
) const
{
	if (size())
	{
		tmp<Field<scalar>> rphi(New(tphi, true));

		forAll(*this, i)
		{
			operator[](i).makeRelative(rphi.ref(), patchi);
		}

		tphi.clear();

		return rphi;
	}
	else
	{
		return tmp<Field<scalar>>(tphi, true);
	}
}


void tnbLib::MRFZoneList::makeRelative
(
	const surfaceScalarField& rho,
	surfaceScalarField& phi
) const
{
	forAll(*this, i)
	{
		operator[](i).makeRelative(rho, phi);
	}
}


void tnbLib::MRFZoneList::makeAbsolute(volVectorField& U) const
{
	forAll(*this, i)
	{
		operator[](i).makeAbsolute(U);
	}
}


void tnbLib::MRFZoneList::makeAbsolute(surfaceScalarField& phi) const
{
	forAll(*this, i)
	{
		operator[](i).makeAbsolute(phi);
	}
}


tnbLib::tmp<tnbLib::surfaceScalarField> tnbLib::MRFZoneList::absolute
(
	const tmp<surfaceScalarField>& tphi
) const
{
	if (size())
	{
		tmp<surfaceScalarField> rphi
		(
			New
			(
				tphi,
				"absolute(" + tphi().name() + ')',
				tphi().dimensions(),
				true
			)
		);

		makeAbsolute(rphi.ref());

		tphi.clear();

		return rphi;
	}
	else
	{
		return tmp<surfaceScalarField>(tphi, true);
	}
}


void tnbLib::MRFZoneList::makeAbsolute
(
	const surfaceScalarField& rho,
	surfaceScalarField& phi
) const
{
	forAll(*this, i)
	{
		operator[](i).makeAbsolute(rho, phi);
	}
}


void tnbLib::MRFZoneList::correctBoundaryVelocity(volVectorField& U) const
{
	forAll(*this, i)
	{
		operator[](i).correctBoundaryVelocity(U);
	}
}


void tnbLib::MRFZoneList::correctBoundaryFlux
(
	const volVectorField& U,
	surfaceScalarField& phi
) const
{
	FieldField<fvsPatchField, scalar> Uf
	(
		relative(mesh_.Sf().boundaryField() & U.boundaryField())
	);


	surfaceScalarField::Boundary& phibf = phi.boundaryFieldRef();

	forAll(mesh_.boundary(), patchi)
	{
		if
			(
				isA<fixedValueFvsPatchScalarField>(phibf[patchi])
				)
		{
			phibf[patchi] == Uf[patchi];
		}
	}
}


void tnbLib::MRFZoneList::update()
{
	if (mesh_.topoChanging())
	{
		forAll(*this, i)
		{
			operator[](i).update();
		}
	}
}


// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

tnbLib::Ostream& tnbLib::operator<<
(
	Ostream& os,
	const MRFZoneList& models
	)
{
	models.writeData(os);
	return os;
}


// ************************************************************************* //