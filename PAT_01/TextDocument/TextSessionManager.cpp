#include "TextSessionManager.h"

#include "TextDocument.h"
#include "TextDocumentFactory.h"
#include "../UserInputManager.h"
#include "../UserInterface.h"
#include "../DocumentIO.h"

#include <string>
#include <stdio.h>


// print help message
int c_help(const char*)
{
	printf("help!!!\n");
	return 0;
}

int c_exit(const char*)
{
	TextSessionManager::getInstance()->stopSession();
	return 0;
}

// switch session selected document to given one
// arg - name of the document to select
int c_selectDocument(const char* arg)
{
	if (arg == nullptr)
		return 1;

	printf("selecting document \"%s\"...\n", arg);

	TextSessionManager::getInstance()->selectDocument(arg);
	return 0;
}

// open document and select it
// arg - name of the document to open
int c_openDocument(const char* arg)
{
	if (arg == nullptr)
		return 1;

	printf("opening document \"%s\"...\n", arg);

	TextDocument* newDoc = new TextDocument(arg);

	SessionManager* instance = TextSessionManager::getInstance();
	instance->getDocumentFactory()->openDocument(arg, newDoc->getFileSpec());
	instance->selectDocument(arg);

	return 0;
}

// set name of the selected document
// arg - new document name
int c_setDocumentName(const char* arg)
{
	if (arg == nullptr)
		return 1;

	TextSessionManager::getInstance()->getSelectedDocument()->setName(arg);

	return 0;
}

// close selected session document and select first open document
int c_closeDocument(const char*) 
{
	SessionManager* instance = TextSessionManager::getInstance();
	instance->getDocumentFactory()->closeDocument(instance->getSelectedDocument()->getName());
	instance->selectDocument(instance->getDocumentFactory()->getDocumentByIndex(0)->getName());
	return 0;
}

// save selected document to given path
// arg - path to save document
int c_saveDocument(const char*)
{
	Document* selected = SessionManager::getInstance()->getSelectedDocument();
	DiskIOManager::getInstance()->saveDocument(selected->getName(), selected->getFileSpec()); 

	return 0;
}


SessionManager* SessionManager::instance = nullptr;

TextSessionManager::TextSessionManager() : SessionManager()
{
	if (instance != nullptr)
		return;

	instance = this;

	sessionCommands = new std::map<std::string, int(*)(const char*)>();
	documentFactory = new TextDocumentFactory();

	(*sessionCommands)["help"] = c_help;
	(*sessionCommands)["exit"] = c_exit;
	(*sessionCommands)["select"] = c_selectDocument;
	(*sessionCommands)["open"] = c_openDocument;
	(*sessionCommands)["setname"] = c_setDocumentName;
	(*sessionCommands)["close"] = c_closeDocument;
	(*sessionCommands)["save"] = c_saveDocument;

	selectedDocument = documentFactory->createDocument("new");
}

TextSessionManager::~TextSessionManager()
{
	delete sessionCommands;
}

int TextSessionManager::update()
{
	int success = 0;
# 	define update_assert(func) \
		success = func; \
		if (success) return success
	
	UserInputManager::getInstance()->recieveInput();
	char userInput = UserInputManager::getInstance()->lastInput();

	if (processInput(userInput) == 0)
	{
		if (selectedDocument != nullptr)
			update_assert(selectedDocument->getEditor()->editDocument(userInput));
	}
	
	update_assert(UserInterface::getInstance()->draw());

	if (selectedDocument != nullptr)
		update_assert(selectedDocument->getRenderer()->draw());

	return 0;
}

int TextSessionManager::processInput(char input)
{
	switch (input)
	{
	case '/':
		if (processCommand() != 0)
			printf("error during command processing\n");
		return 1;
	default:
		return 0;
	}

	return 0;
}

int TextSessionManager::processCommand()
{
	char comBuff[256] {};
	char argBuff[256] {};
	char* currBuff = comBuff;
	char lastInput = -1;

	UserInputManager* uim = UserInputManager::getInstance();

	for (unsigned i = 0;; i++)
	{
		uim->recieveInput();
		lastInput = uim->lastInput();

		if (lastInput == 13 || lastInput == 10)
			break;

		if (lastInput == ' ')
		{
			currBuff = argBuff;
			i = -1;
			putchar(' ');
			continue;
		}
		else if (lastInput == 127)
		{
			i = (i <= 1) ? -1 : i - 2;
			currBuff[i + 2] = '\0';
			printf("\b \b");
			continue;
		}

		currBuff[i] = lastInput;

		putchar(currBuff[i]);
	} 

	printf("\nprocessed command, buffers - \"%s\", \"%s\"\n", comBuff, argBuff);

	int (*callback)(const char*) = (*sessionCommands)[comBuff];

	if (callback == nullptr)
		return 1;

	return callback(argBuff);
}

int TextSessionManager::startSession()
{
	int exitcode = 0;

	
	while (!shouldExit)
		exitcode = update();

	return exitcode;
}

