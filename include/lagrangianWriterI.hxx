#pragma once

template<class Type>
void tnbLib::lagrangianWriter::writeIOField(const wordList& objects)
{
	forAll(objects, i)
	{
		const word& object = objects[i];

		IOobject header
		(
			object,
			vMesh_.mesh().time().timeName(),
			cloud::prefix / cloudName_,
			vMesh_.mesh(),
			IOobject::MUST_READ,
			IOobject::NO_WRITE,
			false
		);

		IOField<Type> fld(header);

		os_ << object << ' ' << pTraits<Type>::nComponents << ' '
			<< fld.size() << " float" << std::endl;

		DynamicList<floatScalar> fField(pTraits<Type>::nComponents * fld.size());

		writeFuns::insert(fld, fField);

		writeFuns::write(os_, binary_, fField);
	}
}