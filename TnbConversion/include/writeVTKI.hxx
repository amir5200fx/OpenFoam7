#pragma once
template<class GeoField>
tnbLib::UPtrList<const GeoField>
tnbLib::functionObjects::writeVTK::lookupFields() const
{
	DynamicList<word> allNames(obr_.toc().size());
	forAll(objectNames_, i)
	{
		wordList names(obr_.names<GeoField>(objectNames_[i]));

		if (names.size())
		{
			allNames.append(names);
		}
	}

	UPtrList<const GeoField> fields(allNames.size());

	forAll(allNames, i)
	{
		const GeoField& field = obr_.lookupObject<GeoField>(allNames[i]);
		Info << "    Writing " << GeoField::typeName
			<< " field " << field.name() << endl;
		fields.set(i, &field);
	}

	return fields;
}