#include "Interface.hpp"

bool Interface::operator==(const Interface& source) const
{
	return true;
}

bool Interface::operator!=(const Interface& source) const
{
	return false;
}

void Interface::release()
{

}
NEBinaryFileSaver& Interface::serialize(NEBinaryFileSaver& saver) const
{
	return saver;
}
NEBinaryFileLoader& Interface::serialize(NEBinaryFileLoader& loader)
{
	return loader;
}
type_result Interface::isValid() const
{
	return RESULT_SUCCESS;
}
