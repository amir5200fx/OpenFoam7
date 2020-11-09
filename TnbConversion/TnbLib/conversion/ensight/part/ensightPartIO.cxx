#include <ensightPart.hxx>

#include <dictionary.hxx>
#include <IOstreams.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::ensightPart::writeHeader
(
	ensightFile& os,
	bool withDescription
) const
{
	os.write("part");
	os.newline();

	os.write(number() + 1);   // Ensight starts with 1
	os.newline();

	if (withDescription)
	{
		os.write(name());
		os.newline();
	}
}


void tnbLib::ensightPart::writeFieldList
(
	ensightFile& os,
	const List<scalar>& field,
	const labelUList& idList
) const
{
	if (notNull(idList))
	{
		forAll(idList, i)
		{
			if (idList[i] >= field.size() || std::isnan(field[idList[i]]))
			{
				os.writeUndef();
			}
			else
			{
				os.write(field[idList[i]]);
			}

			os.newline();
		}
	}
	else
	{
		// no idList => perNode
		forAll(field, i)
		{
			if (std::isnan(field[i]))
			{
				os.writeUndef();
			}
			else
			{
				os.write(field[i]);
			}

			os.newline();
		}
	}
}



// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::ensightPart::reconstruct(Istream& is)
{
	dictionary dict(is);
	dict.lookup("id") >> number_;
	dict.lookup("name") >> name_;

	offset_ = 0;
	dict.readIfPresent("offset", offset_);

	// populate elemLists_
	elemLists_.setSize(elementTypes().size());

	forAll(elementTypes(), elemI)
	{
		word key(elementTypes()[elemI]);

		elemLists_[elemI].clear();
		dict.readIfPresent(key, elemLists_[elemI]);

		size_ += elemLists_[elemI].size();
	}

	is.check("ensightPart::reconstruct(Istream&)");
}


bool tnbLib::ensightPart::writeSummary(Ostream& os) const
{
	os << indent << type() << nl
		<< indent << token::BEGIN_BLOCK << incrIndent << nl;

	// Ensight starts with 1
	writeEntry(os, "id", (number() + 1));
	writeEntry(os, "name", name());
	writeEntry(os, "offset", offset());
	writeEntry(os, "size", size());

	os << decrIndent << indent << token::END_BLOCK << nl << endl;

	return true;
}


bool tnbLib::ensightPart::writeData(Ostream& os) const
{
	os << indent << type() << nl
		<< indent << token::BEGIN_BLOCK << incrIndent << nl;

	writeEntry(os, "id", number());
	writeEntry(os, "name", name());
	writeEntry(os, "offset", offset());

	forAll(elementTypes(), typeI)
	{
		word key(elementTypes()[typeI]);
		if (elemLists_[typeI].size())
		{
			writeEntry(os, key, elemLists_[typeI]);
		}
	}

	os << decrIndent << indent << token::END_BLOCK << nl << endl;

	return true;
}


void tnbLib::ensightPart::writeGeometry
(
	ensightGeoFile& os,
	const pointField& points
) const
{
	if (size())
	{
		const localPoints ptList = calcLocalPoints();
		const labelUList& pointMap = ptList.list;

		writeHeader(os, true);

		// write points
		os.writeKeyword("coordinates");
		os.write(ptList.nPoints);
		os.newline();

		for (direction cmpt = 0; cmpt < point::nComponents; ++cmpt)
		{
			forAll(pointMap, ptI)
			{
				if (pointMap[ptI] > -1)
				{
					os.write(points[ptI].component(cmpt));
					os.newline();
				}
			}
		}

		// write parts
		forAll(elementTypes(), elemI)
		{
			if (elemLists_[elemI].size())
			{
				writeConnectivity
				(
					os,
					elementTypes()[elemI],
					elemLists_[elemI],
					pointMap
				);
			}
		}
	}
}


void tnbLib::ensightPart::writeScalarField
(
	ensightFile& os,
	const List<scalar>& field,
	const bool perNode
) const
{
	if (size() && field.size() && (os.allowUndef() || isFieldDefined(field)))
	{
		writeHeader(os);

		if (perNode)
		{
			os.writeKeyword("coordinates");
			writeFieldList(os, field, labelUList::null());
		}
		else
		{
			forAll(elementTypes(), elemI)
			{
				const labelUList& idList = elemLists_[elemI];

				if (idList.size())
				{
					os.writeKeyword(elementTypes()[elemI]);
					writeFieldList(os, field, idList);
				}
			}
		}
	}
}


void tnbLib::ensightPart::writeVectorField
(
	ensightFile& os,
	const List<scalar>& field0,
	const List<scalar>& field1,
	const List<scalar>& field2,
	const bool perNode
) const
{
	if (size() && field0.size() && (os.allowUndef() || isFieldDefined(field0)))
	{
		writeHeader(os);

		if (perNode)
		{
			os.writeKeyword("coordinates");
			writeFieldList(os, field0, labelUList::null());
			writeFieldList(os, field1, labelUList::null());
			writeFieldList(os, field2, labelUList::null());
		}
		else
		{
			forAll(elementTypes(), elemI)
			{
				const labelUList& idList = elemLists_[elemI];

				if (idList.size())
				{
					os.writeKeyword(elementTypes()[elemI]);
					writeFieldList(os, field0, idList);
					writeFieldList(os, field1, idList);
					writeFieldList(os, field2, idList);
				}
			}
		}
	}
}


// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

FoamConversion_EXPORT tnbLib::Ostream& tnbLib::operator<<
(
	Ostream& os,
	const ensightPart& part
	)
{
	part.writeData(os);
	return os;
}


FoamConversion_EXPORT tnbLib::ensightGeoFile& tnbLib::operator<<
(
	ensightGeoFile& os,
	const ensightPart& part
	)
{
	part.writeGeometry(os);
	return os;
}


// ************************************************************************* //