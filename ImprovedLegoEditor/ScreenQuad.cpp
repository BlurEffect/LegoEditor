/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  ScreenQuad.cpp
*  Contains the function definitions for the ScreenQuad class.
*/

# include "ScreenQuad.h"


ScreenQuad::ScreenQuad() : m_pVertexBuffer( nullptr ), 
						   m_pIndexBuffer( nullptr ), 
						   m_vertexCount( 0 ), 
						   m_indexCount( 0 )
{
}


//--------------------------------------------------------------------------------------
// Creates vertex and index buffers for the quad.
//--------------------------------------------------------------------------------------
HRESULT ScreenQuad::Initialise( ID3D11Device* pDevice )
{
	HRESULT hr;

	// Set the vertex and index count 
	m_vertexCount = 4;
	m_indexCount  = 6;

	// Create arrays to hold vertex and index data (the data will be moved to the respective buffer later on)

	QuadVertex* pVertices = new QuadVertex[m_vertexCount];
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
	
	pVertices[0].m_position.x = -1.0f; // bottom left corner
	pVertices[0].m_position.y = -1.0f;
	pVertices[0].m_position.z = 0.0f;
	pVertices[0].m_texCoord.x = 0.0f;
	pVertices[0].m_texCoord.y = 1.0f;

	pVertices[1].m_position.x = -1.0f; // top left corner
	pVertices[1].m_position.y = 1.0f;
	pVertices[1].m_position.z = 0.0f;
	pVertices[1].m_texCoord.x = 0.0f;
	pVertices[1].m_texCoord.y = 0.0f;

	pVertices[2].m_position.x = 1.0f; // bottom right corner
	pVertices[2].m_position.y = -1.0f;
	pVertices[2].m_position.z = 0.0f;
	pVertices[2].m_texCoord.x = 1.0f;
	pVertices[2].m_texCoord.y = 1.0f;

	pVertices[3].m_position.x = 1.0f; // top right corner
	pVertices[3].m_position.y = 1.0f;
	pVertices[3].m_position.z = 0.0f;
	pVertices[3].m_texCoord.x = 1.0f;
	pVertices[3].m_texCoord.y = 0.0f;

	pIndices[0]  = 0;
	pIndices[1]  = 1;
	pIndices[2]  = 2;
	pIndices[3]  = 2;
	pIndices[4]  = 1;
	pIndices[5]  = 3;
	

	// Setup description of the vertex buffer

	D3D11_BUFFER_DESC vertexBufferDesc;
	ZeroMemory( &vertexBufferDesc, sizeof(vertexBufferDesc) );

	D3D11_SUBRESOURCE_DATA vertexData;
	ZeroMemory( &vertexData, sizeof(vertexData) );

	// Set up the description of the static vertex buffer.
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(QuadVertex) * m_vertexCount;
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
HRESULT ScreenQuad::Cleanup()
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
void ScreenQuad::Render( ID3D11DeviceContext* pDeviceContext )
{
	// Put the vertex and index buffers on the graphics pipeline to prepare them for drawing.
	
	unsigned int stride;
	unsigned int offset;

	// Set vertex buffer stride and offset.
	stride = sizeof(QuadVertex); 
	offset = 0;
    
	// Set the vertex buffer to active in the input assembler so it can be rendered.
	pDeviceContext -> IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);

	// Set the index buffer to active in the input assembler so it can be rendered.
	pDeviceContext -> IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

	// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	pDeviceContext -> IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	pDeviceContext -> DrawIndexed( m_indexCount, 0, 0);
}


