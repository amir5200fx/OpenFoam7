#include <ReactingMultiphaseParcel.hxx>

#include <IOstreams.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

template<class ParcelType>
tnbLib::string tnbLib::ReactingMultiphaseParcel<ParcelType>::propertyList_ =
tnbLib::ReactingMultiphaseParcel<ParcelType>::propertyList();

template<class ParcelType>
const std::size_t tnbLib::ReactingMultiphaseParcel<ParcelType>::sizeofFields_
(
	0
);


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class ParcelType>
tnbLib::ReactingMultiphaseParcel<ParcelType>::ReactingMultiphaseParcel
(
	const polyMesh& mesh,
	Istream& is,
	bool readFields
)
	:
	ParcelType(mesh, is, readFields),
	YGas_(0),
	YLiquid_(0),
	YSolid_(0),
	canCombust_(0)
{
	if (readFields)
	{
		DynamicList<scalar> Yg;
		DynamicList<scalar> Yl;
		DynamicList<scalar> Ys;

		is >> Yg >> Yl >> Ys;

		YGas_.transfer(Yg);
		YLiquid_.transfer(Yl);
		YSolid_.transfer(Ys);

		// scale the mass fractions
		const scalarField& YMix = this->Y_;
		YGas_ /= YMix[GAS] + rootVSmall;
		YLiquid_ /= YMix[LIQ] + rootVSmall;
		YSolid_ /= YMix[SLD] + rootVSmall;
	}

	// Check state of Istream
	is.check
	(
		"ReactingMultiphaseParcel<ParcelType>::ReactingMultiphaseParcel"
		"("
		"const polyMesh&, "
		"Istream&, "
		"bool"
		")"
	);
}


template<class ParcelType>
template<class CloudType>
void tnbLib::ReactingMultiphaseParcel<ParcelType>::readFields(CloudType& c)
{
	ParcelType::readFields(c);
}


template<class ParcelType>
template<class CloudType, class CompositionType>
void tnbLib::ReactingMultiphaseParcel<ParcelType>::readFields
(
	CloudType& c,
	const CompositionType& compModel
)
{
	bool valid = c.size();

	ParcelType::readFields(c, compModel);

	// Get names and sizes for each Y...
	const label idGas = compModel.idGas();
	const wordList& gasNames = compModel.componentNames(idGas);
	const label idLiquid = compModel.idLiquid();
	const wordList& liquidNames = compModel.componentNames(idLiquid);
	const label idSolid = compModel.idSolid();
	const wordList& solidNames = compModel.componentNames(idSolid);
	const wordList& stateLabels = compModel.stateLabels();

	// Set storage for each Y... for each parcel
	forAllIter(typename Cloud<ReactingMultiphaseParcel<ParcelType>>, c, iter)
	{
		ReactingMultiphaseParcel<ParcelType>& p = iter();
		p.YGas_.setSize(gasNames.size(), 0.0);
		p.YLiquid_.setSize(liquidNames.size(), 0.0);
		p.YSolid_.setSize(solidNames.size(), 0.0);
	}

	// Populate YGas for each parcel
	forAll(gasNames, j)
	{
		IOField<scalar> YGas
		(
			c.fieldIOobject
			(
				"Y" + gasNames[j] + stateLabels[idGas],
				IOobject::MUST_READ
			),
			valid
		);

		label i = 0;
		forAllIter
		(
			typename Cloud<ReactingMultiphaseParcel<ParcelType>>,
			c,
			iter
		)
		{
			ReactingMultiphaseParcel<ParcelType>& p = iter();
			p.YGas_[j] = YGas[i++] / (p.Y()[GAS] + rootVSmall);
		}
	}
	// Populate YLiquid for each parcel
	forAll(liquidNames, j)
	{
		IOField<scalar> YLiquid
		(
			c.fieldIOobject
			(
				"Y" + liquidNames[j] + stateLabels[idLiquid],
				IOobject::MUST_READ
			),
			valid
		);

		label i = 0;
		forAllIter
		(
			typename Cloud<ReactingMultiphaseParcel<ParcelType>>,
			c,
			iter
		)
		{
			ReactingMultiphaseParcel<ParcelType>& p = iter();
			p.YLiquid_[j] = YLiquid[i++] / (p.Y()[LIQ] + rootVSmall);
		}
	}
	// Populate YSolid for each parcel
	forAll(solidNames, j)
	{
		IOField<scalar> YSolid
		(
			c.fieldIOobject
			(
				"Y" + solidNames[j] + stateLabels[idSolid],
				IOobject::MUST_READ
			),
			valid
		);

		label i = 0;
		forAllIter
		(
			typename Cloud<ReactingMultiphaseParcel<ParcelType>>,
			c,
			iter
		)
		{
			ReactingMultiphaseParcel<ParcelType>& p = iter();
			p.YSolid_[j] = YSolid[i++] / (p.Y()[SLD] + rootVSmall);
		}
	}
}


template<class ParcelType>
template<class CloudType>
void tnbLib::ReactingMultiphaseParcel<ParcelType>::writeFields(const CloudType& c)
{
	ParcelType::writeFields(c);
}


template<class ParcelType>
template<class CloudType, class CompositionType>
void tnbLib::ReactingMultiphaseParcel<ParcelType>::writeFields
(
	const CloudType& c,
	const CompositionType& compModel
)
{
	ParcelType::writeFields(c, compModel);

	label np = c.size();

	// Write the composition fractions
	{
		const wordList& stateLabels = compModel.stateLabels();

		const label idGas = compModel.idGas();
		const wordList& gasNames = compModel.componentNames(idGas);
		forAll(gasNames, j)
		{
			IOField<scalar> YGas
			(
				c.fieldIOobject
				(
					"Y" + gasNames[j] + stateLabels[idGas],
					IOobject::NO_READ
				),
				np
			);

			label i = 0;
			forAllConstIter
			(
				typename Cloud<ReactingMultiphaseParcel<ParcelType>>,
				c,
				iter
			)
			{
				const ReactingMultiphaseParcel<ParcelType>& p0 = iter();
				YGas[i++] = p0.YGas()[j] * p0.Y()[GAS];
			}

			YGas.write(np > 0);
		}

		const label idLiquid = compModel.idLiquid();
		const wordList& liquidNames = compModel.componentNames(idLiquid);
		forAll(liquidNames, j)
		{
			IOField<scalar> YLiquid
			(
				c.fieldIOobject
				(
					"Y" + liquidNames[j] + stateLabels[idLiquid],
					IOobject::NO_READ
				),
				np
			);

			label i = 0;
			forAllConstIter
			(
				typename Cloud<ReactingMultiphaseParcel<ParcelType>>,
				c,
				iter
			)
			{
				const ReactingMultiphaseParcel<ParcelType>& p0 = iter();
				YLiquid[i++] = p0.YLiquid()[j] * p0.Y()[LIQ];
			}

			YLiquid.write(np > 0);
		}

		const label idSolid = compModel.idSolid();
		const wordList& solidNames = compModel.componentNames(idSolid);
		forAll(solidNames, j)
		{
			IOField<scalar> YSolid
			(
				c.fieldIOobject
				(
					"Y" + solidNames[j] + stateLabels[idSolid],
					IOobject::NO_READ
				),
				np
			);

			label i = 0;
			forAllConstIter
			(
				typename Cloud<ReactingMultiphaseParcel<ParcelType>>,
				c,
				iter
			)
			{
				const ReactingMultiphaseParcel<ParcelType>& p0 = iter();
				YSolid[i++] = p0.YSolid()[j] * p0.Y()[SLD];
			}

			YSolid.write(np > 0);
		}
	}
}


// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

template<class ParcelType>
tnbLib::Ostream& tnbLib::operator<<
(
	Ostream& os,
	const ReactingMultiphaseParcel<ParcelType>& p
	)
{
	scalarField YGasLoc(p.YGas()*p.Y()[0]);
	scalarField YLiquidLoc(p.YLiquid()*p.Y()[1]);
	scalarField YSolidLoc(p.YSolid()*p.Y()[2]);
	if (os.format() == IOstream::ASCII)
	{
		os << static_cast<const ParcelType&>(p)
			<< token::SPACE << YGasLoc
			<< token::SPACE << YLiquidLoc
			<< token::SPACE << YSolidLoc;
	}
	else
	{
		os << static_cast<const ParcelType&>(p);
		os << YGasLoc << YLiquidLoc << YSolidLoc;
	}

	// Check state of Ostream
	os.check
	(
		"Ostream& operator<<"
		"("
		"Ostream&, "
		"const ReactingMultiphaseParcel<ParcelType>&"
		")"
	);

	return os;
}


// ************************************************************************* //