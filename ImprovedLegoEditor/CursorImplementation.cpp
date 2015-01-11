/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  CursorImplementation.cpp
*  Contains the function definitions for the CursorImplementation class.
*/

# include "CursorImplementation.h"


CursorImplementation::CursorImplementation() : m_pVertexBuffer( nullptr ), 
											   m_pIndexBuffer( nullptr ), 
										       m_vertexCount( 0 ), 
										       m_indexCount( 0 )
{
}


//--------------------------------------------------------------------------------------
// Creates vertices for the cursor given the following parameters:
//		- size		-> width (= length) of the grid in gridUnits
//		- gridUnit	-> determines the distance between each line
//		- colour	-> the grid is displayed in this colour
// Creates vertex and index buffers for the cursor.
//--------------------------------------------------------------------------------------
HRESULT CursorImplementation::Initialise( ID3D11Device* pDevice, XMFLOAT3 position, XMFLOAT3 extents )
{
	HRESULT hr;

	// Set the vertex and index count (cursor will always be cubic and is made up of lines)
	m_vertexCount =  8;
	m_indexCount  = 36;

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
	
	pVertices[0].m_position.x = position.x;
	pVertices[0].m_position.y = position.y;
	pVertices[0].m_position.z = position.z;

	pVertices[1].m_position.x = position.x + extents.x;
	pVertices[1].m_position.y = position.y;
	pVertices[1].m_position.z = position.z;

	pVertices[2].m_position.x = position.x;
	pVertices[2].m_position.y = position.y;
	pVertices[2].m_position.z = position.z + extents.z;

	pVertices[3].m_position.x = position.x + extents.x;
	pVertices[3].m_position.y = position.y;
	pVertices[3].m_position.z = position.z + extents.z;

	pVertices[4].m_position.x = position.x;
	pVertices[4].m_position.y = position.y + extents.y;
	pVertices[4].m_position.z = position.z;

	pVertices[5].m_position.x = position.x + extents.x;
	pVertices[5].m_position.y = position.y + extents.y;
	pVertices[5].m_position.z = position.z;

	pVertices[6].m_position.x = position.x;
	pVertices[6].m_position.y = position.y + extents.y;
	pVertices[6].m_position.z = position.z + extents.z;

	pVertices[7].m_position.x = position.x + extents.x;
	pVertices[7].m_position.y = position.y + extents.y;
	pVertices[7].m_position.z = position.z + extents.z;

	pIndices[0]  = 0;
	pIndices[1]  = 1;
	pIndices[2]  = 0;
	pIndices[3]  = 2;
	pIndices[4]  = 1;
	pIndices[5]  = 3;
	pIndices[6]  = 2;
	pIndices[7]  = 3;

	pIndices[8]  = 0;
	pIndices[9]  = 4;
	pIndices[10] = 1;
	pIndices[11] = 5;
	pIndices[12] = 2;
	pIndices[13] = 6;
	pIndices[14] = 3;
	pIndices[15] = 7;

	pIndices[16] = 4;
	pIndices[17] = 5;
	pIndices[18] = 4;
	pIndices[19] = 6;
	pIndices[20] = 5;
	pIndices[21] = 7;
	pIndices[22] = 7;
	pIndices[23] = 6;

	// Setup description of the vertex buffer

	D3D11_BUFFER_DESC vertexBufferDesc;
	ZeroMemory( &vertexBufferDesc, sizeof(vertexBufferDesc) );

	D3D11_SUBRESOURCE_DATA vertexData;
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
HRESULT CursorImplementation::Cleanup()
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
// Render the cursor
//--------------------------------------------------------------------------------------
void CursorImplementation::Render( ID3D11DeviceContext* pDeviceContext )
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


