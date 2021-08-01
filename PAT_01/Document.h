#pragma once

class Document;


// interface for file format specification
class DocumentFileSpec
{
protected:
	Document* parent;

public:
	DocumentFileSpec(Document* parent);
	// transform parent document int raw binary data
	virtual unsigned getSaveData(void* buffer) = 0;
};


// interface for document rendering
class DocumentRenderer
{
protected:
	Document* parent;
	//RenderingContext context;

public:
	DocumentRenderer(Document* parent);
	// draw parent document on screen
	virtual int draw() = 0;
};


// interface for document editing
class DocumentEditor
{
protected:
	Document* parent;
public:
	DocumentEditor(Document* parent);
	// edit contents of parent document depending on recieved input
	virtual int editDocument() = 0;
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

	DocumentFileSpec* getFileSpec();
	DocumentRenderer* getRenderer();
	DocumentEditor* getEditor();
};

