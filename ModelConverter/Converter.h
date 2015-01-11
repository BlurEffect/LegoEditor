/* 
*  Kevin Meergans, Improved Lego Editor - Model Converter, 2014
*  Converter.h
*  Offers functions to convert a 3d model from its source format into the format 
*  used by the Lego Editor.
*/

#ifndef CONVERTER_H
#define CONVERTER_H

#include <Windows.h>
#include <string>
#include <fstream>
#include "ConverterDataStructures.h"
#include <xnamath.h>
#include <vector>
#include <algorithm>

class Converter
{
public:
	Converter( void );
	HRESULT Convert( const std::string& sourceFileName, const std::string& destinationFileName );
private:
	//HRESULT ConvertObj(const std::string& sourceFile, const std::string& destinationFile);
	HRESULT ReadFromSourceFile( const std::string& sourceFileName );
	HRESULT ReadDataFromObjFile( const std::string& sourceFileName );
	void ComputeNormals( void );
	HRESULT WriteToDestinationFile( const std::string& destinationFileName );
	HRESULT Cleanup( void );

	XMFLOAT3* m_pVertices;	
	XMFLOAT3* m_pTexCoords;
	XMFLOAT3* m_pNormals;
	XMFLOAT3* m_pRecalculatedNormals;
	Face*	m_pFaces;

	int m_vertexCount;
	int m_texCoordCount;
	int m_normalCount;
	int m_faceCount;
};

#endif