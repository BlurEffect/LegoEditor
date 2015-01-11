/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  GridImplementation.cpp
*  Contains the function definitions for the GridImplementation class.
*/

# include "GridImplementation.h"


GridImplementation::GridImplementation() : m_pVertexBuffer( nullptr ), 
										   m_pIndexBuffer( nullptr ), 
										   m_vertexCount( 0 ), 
										   m_indexCount( 0 )
{
}


//--------------------------------------------------------------------------------------
// Creates vertices for the grid given the following parameters:
//		- size		-> width (= length) of the grid in gridUnits
//		- gridUnit	-> determines the distance between each line
//		- colour	-> the grid is displayed in this colour
// Creates vertex and index buffers for the grid.
//--------------------------------------------------------------------------------------
HRESULT GridImplementation::Initialise( ID3D11Device* pDevice, XMFLOAT3 centre, int width, int length, float gridUnitX, float gridUnitZ )
{
	HRESULT hr;

	// Calculate the vertex and index count:
	// number of lines per dimension (size + 1) multiplied by 2 (2 vertices per line)
	m_vertexCount = ( width + 1 ) * 2 + ( length + 1 ) * 2;
	m_indexCount = m_vertexCount;

	// Create arrays to hold vertex and index data (the data will be moved to the respective buffer later on)

	SimpleVertex* pVertices = new SimpleVertex[m_vertexCount];
	if( !pVertices )
	{
		return E_FAIL;
	}

	unsigned long* pIndices = new unsigned long[m_indexCount];
	if( !pIndices )
	{
		return E_FAIL;
	}

	// Fill the vertex and index arrays with the mesh data to move it into the respective buffers later on
	
	// calculate the extent of the grid in one direction from the centre (= length / 2)
	float gridExtentX = ( width * gridUnitX ) * 0.5f;
	float gridExtentZ = ( length * gridUnitZ ) * 0.5f;
	
	float pos	= -gridExtentZ; // determines where the vertices are placed

	int   index = 0;		   // index of the vertices into the vertex array

	// place the lines/vertices parallel to the x-axis
	while( pos <= gridExtentZ )
	{
		pVertices[index].m_position.x = centre.x - gridExtentX;
		pVertices[index].m_position.y = centre.y;
		pVertices[index].m_position.z = centre.z + pos;
		pIndices[index] = index;
		++index;

		pVertices[index].m_position.x = centre.x + gridExtentX;
		pVertices[index].m_position.y = centre.y;
		pVertices[index].m_position.z = centre.z + pos;
		pIndices[index] = index;
		++index;

		pos += gridUnitZ;
	}

	pos	= -gridExtentX; 

	// place the lines/vertices parallel to the z-axis
	while( pos <= gridExtentX )
	{
		// vertices along the z axis

		pVertices[index].m_position.x = centre.x + pos;
		pVertices[index].m_position.y = centre.y;
		pVertices[index].m_position.z = centre.z - gridExtentZ;
		pIndices[index] = index;
		++index;

		pVertices[index].m_position.x = centre.x + pos;
		pVertices[index].m_position.y = centre.y;
		pVertices[index].m_position.z = centre.z + gridExtentZ;
		pIndices[index] = index;
		++index;

		pos += gridUnitX;
	}

	// Setup description of the vertex buffer

	D3D11_BUFFER_DESC			vertexBufferDesc;
	ZeroMemory( &vertexBufferDesc, sizeof(vertexBufferDesc) );

	D3D11_SUBRESOURCE_DATA		vertexData;
	ZeroMemory( &vertexData, sizeof(vertexData) );

	// Set up the description of the static vertex buffer.
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(SimpleVertex) * m_vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the vertex data.
	vertexData.pSysMem = pVertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	// Now create the vertex buffer.
	hr = pDevice -> CreateBuffer( &vertexBufferDesc, &vertexData, &m_pVertexBuffer );
	if(FAILED( hr ) )
	{
		return hr;
	}

	// Setup description of the index buffer

	D3D11_BUFFER_DESC indexBufferDesc;
	ZeroMemory( &indexBufferDesc, sizeof(indexBufferDesc) );

	D3D11_SUBRESOURCE_DATA indexData;
	ZeroMemory( &indexData, sizeof(indexData) );

	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof( unsigned long ) * m_indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the index data.
	indexData.pSysMem = pIndices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	// Create the index buffer.
	hr = pDevice -> CreateBuffer( &indexBufferDesc, &indexData, &m_pIndexBuffer );
	if( FAILED( hr ) )
	{
		return hr;
	}

	// Release the arrays now that the vertex and index buffers have been created and loaded.

	delete [] pVertices;
	pVertices = nullptr;

	delete [] pIndices;
	pIndices = nullptr;

	return S_OK;
}

//--------------------------------------------------------------------------------------
// Release the index and vertex buffers
//--------------------------------------------------------------------------------------
HRESULT GridImplementation::Cleanup()
{
	if(m_pIndexBuffer)
	{
		m_pIndexBuffer -> Release();
		m_pIndexBuffer  = nullptr;
	}

	if(m_pVertexBuffer)
	{
		m_pVertexBuffer -> Release();
		m_pVertexBuffer  = nullptr;
	}

	return S_OK;
}

//--------------------------------------------------------------------------------------
// Render the grid
//--------------------------------------------------------------------------------------
void GridImplementation::Render( ID3D11DeviceContext* pDeviceContext )
{
	// Put the vertex and index buffers on the graphics pipeline to prepare them for drawing.
	
	unsigned int stride;
	unsigned int offset;

	// Set vertex buffer stride and offset.
	stride = sizeof(SimpleVertex); 
	offset = 0;
    
	// Set the vertex buffer to active in the input assembler so it can be rendered.
	pDeviceContext -> IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);

	// Set the index buffer to active in the input assembler so it can be rendered.
	pDeviceContext -> IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

	// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	pDeviceContext -> IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

	pDeviceContext -> DrawIndexed( m_indexCount, 0, 0);
}


