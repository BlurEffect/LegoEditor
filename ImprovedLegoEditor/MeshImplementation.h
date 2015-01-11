/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  MeshImplementation.h
*  Implementation part of the Mesh class.The public interface of this class
*  and the one of the Mesh class have to be kept consistent. 
*/

// todo: make this a template class?

#ifndef MESH_IMPLEMENTATION_H
#define MESH_IMPLEMENTATION_H

#include <windows.h>


#include <d3d11.h>
#include <d3d10.h>
#include <dxgi.h>

#include <memory>
#include <fstream>		// for reading in the mesh data from a file
#include <string>
#include "MeshDataStructures.h"
#include "Settings.h"
#include <vector>
#include <algorithm>
#include "Helpers.h"


class MeshImplementation
{
public:
	MeshImplementation();

	HRESULT Initialise( ID3D11Device* pDevice, std::string filename, int maxNumberOfInstances );
	HRESULT Cleanup();
	void Render( ID3D11DeviceContext* pDeviceContext, const Instance* const pInstances, int instanceCount );

private:

	HRESULT LoadMesh( std::string filename );
	HRESULT ReleaseMesh();
	void CalculateAverageNormals();

	MeshType*		m_pMesh;				// the mesh data read from a file is stored in this structure
	long*			m_pIndices;				// the index data read in from the file
	ID3D11Buffer*	m_pVertexBuffer;	
	ID3D11Buffer*	m_pIndexBuffer;		
	ID3D11Buffer*	m_pInstanceBuffer;		
	int				m_vertexCount;
	int				m_indexCount;

};

#endif

