/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  Mesh.cpp
*  Contains the function definitions for the Mesh class. Calls to these
*  functions will be forwarded to the implementation part of the mesh class
*  "MeshImplementation".
*/

#include "Mesh.h"
#include "MeshImplementation.h"

Mesh::Mesh() : m_pImplementation( new MeshImplementation() )
{
}

HRESULT Mesh::Initialise( ID3D11Device* pDevice, std::string filename, int maxNumberOfInstances )
{
	return m_pImplementation -> Initialise( pDevice, filename, maxNumberOfInstances );
}

HRESULT Mesh::Cleanup()
{
	return m_pImplementation -> Cleanup();
}

void Mesh::Render( ID3D11DeviceContext* pDeviceContext, const Instance* const pInstances, int instanceCount )
{
	m_pImplementation -> Render( pDeviceContext, pInstances, instanceCount );
}

