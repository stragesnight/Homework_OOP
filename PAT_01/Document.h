#pragma once

class Document;


// interface for file format specification
class DocumentFileSpec
{
protected:
	Document* parent;
public:
	DocumentFileSpec(Document* parent) { this->parent = parent; }
	virtual ~DocumentFileSpec() {}
	// transform parent document int raw binary data
	virtual unsigned getSaveData(char*& buffer) = 0;
	// transform raw binary data into document
	virtual Document* parseData(const char* buffer) = 0;
};


// interface for document rendering
class DocumentRenderer
{
protected:
	Document* parent;
public:
	DocumentRenderer(Document* parent) { this->parent = parent; }
	virtual ~DocumentRenderer() {}
	// draw parent document on screen
	virtual int draw() = 0;
};


// interface for document editing
class DocumentEditor
{
protected:
	Document* parent;
public:
	DocumentEditor(Document* parent) { this->parent = parent; }
	virtual ~DocumentEditor() {}
	// edit contents of parent document depending on recieved input
	virtual int editDocument(char input) = 0;
	//virtual int editDocument(const EditData& editData) = 0;
};


// base document class
class Document
{
protected:
	char* name;
	DocumentFileSpec* fileSpec;
	DocumentRenderer* renderer;
	DocumentEditor* editor;
	
public:
	Document(const char* name);
	~Document();

	const char* getName();
	DocumentFileSpec* getFileSpec();
	DocumentRenderer* getRenderer();
	DocumentEditor* getEditor();
};

