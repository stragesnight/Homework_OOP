#include "UserInterface.h"

UserInterface* UserInterface::instance = nullptr;

UserInterface::UserInterface()
{
	if (instance == nullptr)
		instance = this;
}

UserInterface::~UserInterface()
{}

UserInterface* UserInterface::getInstance()
{
	return instance;
}

