/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  MeshImplementation.cpp
*  Contains the function definitions for the MeshImplementation class.
*/

# include "MeshImplementation.h"


MeshImplementation::MeshImplementation() : m_pMesh(nullptr), 
										   m_pVertexBuffer( nullptr ), 
										   m_pIndexBuffer( nullptr ),
										   m_pInstanceBuffer( nullptr ),
										   m_vertexCount( 0 ), 
										   m_indexCount( 0 )
{
}


//--------------------------------------------------------------------------------------
// Create index and vertex buffers for the mesh
//--------------------------------------------------------------------------------------
HRESULT MeshImplementation::Initialise( ID3D11Device* pDevice, std::string filename, int maxNumberOfInstances )
{
	HRESULT hr;

	hr = LoadMesh( filename );
	if(FAILED( hr ) )
	{
		return hr;
	}

	CalculateAverageNormals();

	// Create arrays to hold vertex and index data (the data will be moved to the respective buffer later on)

	Vertex* pVertices = new Vertex[m_vertexCount];
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
	for(int i = 0; i < m_vertexCount; ++i)
	{
		pVertices[i].m_position.x = m_pMesh[i].m_positionX;
		pVertices[i].m_position.y = m_pMesh[i].m_positionY;
		pVertices[i].m_position.z = m_pMesh[i].m_positionZ;
		
		pVertices[i].m_texCoord.x = m_pMesh[i].m_texCoordU;
		pVertices[i].m_texCoord.y = m_pMesh[i].m_texCoordV;

		pVertices[i].m_normal.x = m_pMesh[i].m_normalX;
		pVertices[i].m_normal.y = m_pMesh[i].m_normalY;
		pVertices[i].m_normal.z = m_pMesh[i].m_normalZ;

		pVertices[i].m_sharedNormal.x = m_pMesh[i].m_avgNormalX;
		pVertices[i].m_sharedNormal.y = m_pMesh[i].m_avgNormalY;
		pVertices[i].m_sharedNormal.z = m_pMesh[i].m_avgNormalZ;
	}

	for(int i = 0; i < m_indexCount; ++i)
	{
		pIndices[i] = m_pIndices[i];
	}


	// Setup description of the vertex buffer

	D3D11_BUFFER_DESC			vertexBufferDesc;
	ZeroMemory( &vertexBufferDesc, sizeof(vertexBufferDesc) );

	D3D11_SUBRESOURCE_DATA		vertexData;
	ZeroMemory( &vertexData, sizeof(vertexData) );

	// Set up the description of the static vertex buffer.
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(Vertex) * m_vertexCount;
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

	D3D11_BUFFER_DESC			indexBufferDesc;
	ZeroMemory( &indexBufferDesc, sizeof(indexBufferDesc) );

	D3D11_SUBRESOURCE_DATA		indexData;
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

	// create an instance buffer
	D3D11_BUFFER_DESC instanceBufferDesc;	
	ZeroMemory( &instanceBufferDesc, sizeof( instanceBufferDesc ) );

	instanceBufferDesc.Usage		  = D3D11_USAGE_DYNAMIC;
	instanceBufferDesc.ByteWidth      = sizeof( Instance ) * maxNumberOfInstances;
	instanceBufferDesc.BindFlags	  = D3D11_BIND_VERTEX_BUFFER;
	instanceBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	instanceBufferDesc.MiscFlags	  = 0;

	hr = pDevice -> CreateBuffer( &instanceBufferDesc, NULL, &m_pInstanceBuffer);
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
// Loads mesh data from the given filename.
// Vertices in the file to load have to:
//		- match the left-handed coordinate system of DirectX 11
//		- be listed in clockwise order
//--------------------------------------------------------------------------------------
HRESULT MeshImplementation::LoadMesh( std::string filename )
{
	// Create a file input stream to read in the mesh data
	std::ifstream in;
	// Read in data to this variable
	char input;

	// Open the file
	in.open( filename );
	
	// Check whether the file could be opened successfully
	if(in.fail())
	{
		return E_FAIL;
	}

	// Read up to the vertex count
	in.get( input );
	while( input != ':' )
	{
		in.get( input );
	}

	// Read in the vertex count
	in >> m_vertexCount;

	in.get( input );
	while( input != ':' )
	{
		in.get( input );
	}

	in >> m_indexCount;
	
	// Set the number of indices to be the same as the vertex count
	//m_indexCount = m_vertexCount;

	// Create the mesh data
	m_pMesh = new MeshType[m_vertexCount];
	// Check if dynamic memory allocation failed
	if( !m_pMesh )
	{
		return E_FAIL;
	}

	m_pIndices = new long[m_indexCount];
	// Check if dynamic memory allocation failed
	if( !m_pIndices )
	{
		return E_FAIL;
	} 

	// Read up to the beginning of the vertex data
	in.get( input );
	while( input != ':' )
	{
		in.get( input );
	}

	in.get( input );
	in.get( input );

	// Read in the vertices
	for( int i = 0; i < m_vertexCount; ++i )
	{
		in.get( input ); // get the 'v'
		in >> m_pMesh[i].m_positionX >> m_pMesh[i].m_positionY >> m_pMesh[i].m_positionZ;
		in >> m_pMesh[i].m_texCoordU >> m_pMesh[i].m_texCoordV;
		in >> m_pMesh[i].m_normalX	 >> m_pMesh[i].m_normalY   >> m_pMesh[i].m_normalZ;
		in.get( input ); // get the '\n'
	}

	//in.get( input );
	//in.get( input );

	in.get( input );

	// Read in the indices
	for( int i = 0; i < m_indexCount; ++i )
	{
		in.get( input ); // get the 'i'
		in >> m_pIndices[i];
		in.get( input ); // get the '\n'
	}

	// Close the file
	in.close();

	return S_OK;
}

//--------------------------------------------------------------------------------------
// Release the index and vertex buffers
//--------------------------------------------------------------------------------------
HRESULT MeshImplementation::Cleanup()
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

	if(m_pInstanceBuffer)
	{
		m_pInstanceBuffer -> Release();
		m_pInstanceBuffer  = nullptr;
	}

	ReleaseMesh();

	return S_OK;
}

//--------------------------------------------------------------------------------------
// Release the mesh
//--------------------------------------------------------------------------------------
HRESULT MeshImplementation::ReleaseMesh()
{
	if(m_pMesh)
	{
		delete [] m_pMesh;
		m_pMesh = nullptr;
	}

	return S_OK;
}

//--------------------------------------------------------------------------------------
// Render the mesh
//--------------------------------------------------------------------------------------
void MeshImplementation::Render( ID3D11DeviceContext* pDeviceContext, const Instance* const pInstances, int instanceCount )
{
	// Put the vertex and index buffers on the graphics pipeline to prepare them for drawing.
	
	//unsigned int stride;
	//unsigned int offset;

	// Set vertex buffer stride and offset.
	//stride = sizeof(Vertex); 
	//offset = 0;
    
	// update instance buffer
	//pDeviceContext->UpdateSubresource( m_pInstanceBuffer, 0, NULL, &pInstances[0], 0, 0 );

	
	D3D11_MAPPED_SUBRESOURCE resource;
    pDeviceContext->Map(m_pInstanceBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &resource);
    memcpy(resource.pData, &pInstances[0], sizeof(Instance) * instanceCount ); //NUMBER_OF_BRICKS_PER_TYPE);
   
	// check for contents
	//Instance* dataView = reinterpret_cast<Instance*>(resource.pData);

	pDeviceContext->Unmap(m_pInstanceBuffer, 0);
	



	unsigned int strides[2];
	unsigned int offsets[2];
	ID3D11Buffer* bufferPointers[2];

	// Set the buffer strides.
	strides[0] = sizeof(Vertex); 
	strides[1] = sizeof(Instance); 

	// Set the buffer offsets.
	offsets[0] = 0;
	offsets[1] = 0;

	// Set the array of pointers to the vertex and instance buffers.
	bufferPointers[0] = m_pVertexBuffer;	
	bufferPointers[1] = m_pInstanceBuffer;

	// Set the vertex buffer to active in the input assembler so it can be rendered.
	pDeviceContext->IASetVertexBuffers(0, 2, bufferPointers, strides, offsets);

	// Set the vertex buffer to active in the input assembler so it can be rendered.
	//pDeviceContext -> IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);

	// Set the index buffer to active in the input assembler so it can be rendered.
	pDeviceContext -> IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

	// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	pDeviceContext -> IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	pDeviceContext -> DrawIndexedInstanced( m_indexCount, instanceCount, 0, 0, 0);
}

//--------------------------------------------------------------------------------------
// For vertices in the same position, calculate an additional average normal (used for some of the cel shaders)
//--------------------------------------------------------------------------------------
void MeshImplementation::CalculateAverageNormals()
{

	for(int i = 0; i < m_vertexCount; ++i)
	{
		std::vector<MeshType*> vertices;

		// only compute an average normal if not already done so
		if( m_pMesh[i].m_avgNormalX == 0.0f && m_pMesh[i].m_avgNormalY == 0.0f && m_pMesh[i].m_avgNormalZ == 0.0f )
		{
			// find all vertices with the same position
			for( int j = 0; j < m_vertexCount; ++j )
			{
				if( m_pMesh[j].m_positionX == m_pMesh[i].m_positionX &&
					m_pMesh[j].m_positionY == m_pMesh[i].m_positionY &&
					m_pMesh[j].m_positionZ == m_pMesh[i].m_positionZ )
				{
					vertices.push_back( &m_pMesh[j] );
				}
			}

			// only unique normalised normals
			XMFLOAT3 sumOfNormals( 0.0f, 0.0f, 0.0f );;

			// Used to make sure no normal is included twice into the calculation
			std::vector<XMFLOAT3> normals;

			// Calculate the average normal for the vertices in the same position
			for( std::vector<MeshType*>::iterator it = vertices.begin(); it != vertices.end(); ++it )
			{
				// normalise the normal
				XMFLOAT3 normal( (*it)->m_normalX, (*it)->m_normalY, (*it)->m_normalZ );
				XMFLOAT3 normalisedNormal( 0.0f, 0.0f, 0.0f );
				XMStoreFloat3( &normalisedNormal, XMVector3Normalize( XMLoadFloat3( &normal ) ) );
				
				// Check if this normal is already included
				if( std::find_if( normals.begin(), normals.end(), FindFloat3ByValue(normal) ) == normals.end() )
				{
					// If this is a new normal, add it to the vector and sum
					normals.push_back( normalisedNormal );
					sumOfNormals.x += normalisedNormal.x;
					sumOfNormals.y += normalisedNormal.y;
					sumOfNormals.z += normalisedNormal.z;
				}
			}

			// Get the average normal and normalise it as well
			XMFLOAT3 averageNormal( 0.0f, 0.0f, 0.0f );
			averageNormal.x = sumOfNormals.x / normals.size();
			averageNormal.y = sumOfNormals.y / normals.size();
			averageNormal.z = sumOfNormals.z / normals.size();

			XMStoreFloat3( &averageNormal, XMVector3Normalize( XMLoadFloat3( &averageNormal ) ) );

			// Set the average normal as the average normal for all associated vertices
			for( std::vector<MeshType*>::iterator it = vertices.begin(); it != vertices.end(); ++it )
			{
				(*it)->m_avgNormalX = averageNormal.x;
				(*it)->m_avgNormalY = averageNormal.y;
				(*it)->m_avgNormalZ = averageNormal.z;
			}
		}
	}
}


