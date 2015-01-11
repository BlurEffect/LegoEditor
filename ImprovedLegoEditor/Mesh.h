/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  Mesh.h
*  Encapsulates a mesh and its vertex and index buffers as well as 
*  a function to draw the mesh.
*/

#ifndef MESH_H
#define MESH_H

#include <windows.h>
#include <d3d11.h>
#include <memory>
#include <string>

// forward declaration
class MeshImplementation;
struct Instance;

class Mesh
{
public:
	Mesh();
	HRESULT Initialise( ID3D11Device*, std::string filename, int maxNumberOfInstances );
	HRESULT Cleanup();
	void	Render( ID3D11DeviceContext* pDeviceContext, const Instance* const pInstances, int instanceCount );
private:
	std::tr1::shared_ptr<MeshImplementation> m_pImplementation;
};

#endif