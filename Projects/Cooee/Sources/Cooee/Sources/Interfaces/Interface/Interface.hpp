#pragma once

#include "../../Includes/Includes.hpp"

class Interface : public NEObject
{
public:
	bool operator==(const Interface& source) const;
	bool operator!=(const Interface& source) const;
	
public:
	virtual type_result run(NETStringSet& parameter) = 0;
	virtual const NETString& getName() const = 0;
	virtual const NETString& getNickName() const = 0;

public:
	virtual void release();
	virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const;
	virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);
	virtual type_result isValid() const;
};
