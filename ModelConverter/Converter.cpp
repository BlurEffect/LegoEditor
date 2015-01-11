/* 
*  Kevin Meergans, Improved Lego Editor - Model Converter, 2014
*  Converter.cpp
*  Contains definitions for the converter functions.
*/

// todo: Converter starts accumulating an error after one go -> something probably isn't getting reset properly

#include "Converter.h"

Converter::Converter( void ) : m_pVertices( nullptr ),
							   m_pTexCoords( nullptr ),
							   m_pNormals( nullptr ),
							   m_pRecalculatedNormals( nullptr ),
							   m_pFaces( nullptr ),
							   m_vertexCount( 0 ),
							   m_texCoordCount( 0 ),
							   m_normalCount( 0 ),
							   m_faceCount( 0 )
{
}

//--------------------------------------------------------------------------------------
// Convert the source file from its original format into the lego editor format and
// store it under the given destination
//--------------------------------------------------------------------------------------
HRESULT Converter::Convert( const std::string& sourceFileName, const std::string& destinationFileName )
{
	HRESULT hr;
	
	hr = ReadFromSourceFile( sourceFileName );
	if( FAILED( hr ))
	{
		Cleanup();
		return hr;
	}

	ComputeNormals();

	hr = WriteToDestinationFile( destinationFileName );
	if( FAILED( hr ))
	{
		Cleanup();
		return hr;
	}

	Cleanup();
	return S_OK;
}


//--------------------------------------------------------------------------------------
// Read in the model data using a proper function for the given source format
//--------------------------------------------------------------------------------------
HRESULT Converter::ReadFromSourceFile( const std::string& sourceFileName )
{
	
	// todo: might not always produce correct results. Use an existing function?

	std::string fileExtension = sourceFileName.substr( sourceFileName.find_last_of( "." ) + 1 );

	// todo: use function pointers/factory here?

	if( fileExtension == "obj" )
	{
		return ReadDataFromObjFile( sourceFileName );
	}else
	{
		// unsupported source format
		return E_FAIL;
	}
}


//--------------------------------------------------------------------------------------
// Write the stored model data to a destination file with the proper format for the
// lego editor
//--------------------------------------------------------------------------------------
HRESULT Converter::WriteToDestinationFile( const std::string& destinationFileName )
{
	std::vector<Vertex> vertices;
	std::vector<long> indices;

	int vIndex = 0;
	int	tIndex = 0;
	int	nIndex = 0;

	Vertex newVertex;
	long index = 0;

	for( int i = 0; i < m_faceCount; ++i )
	{
		// First vertex of the face 

		vIndex = m_pFaces[i].m_vertexIndex1 - 1;
		tIndex = m_pFaces[i].m_texCoordIndex1 - 1;
		nIndex = m_pFaces[i].m_normalIndex1 - 1;

		newVertex.m_position.x = m_pVertices[vIndex].x;
		newVertex.m_position.y = m_pVertices[vIndex].y;
		newVertex.m_position.z = m_pVertices[vIndex].z;

		newVertex.m_normal.x = m_pNormals[nIndex].x;
		newVertex.m_normal.y = m_pNormals[nIndex].y;
		newVertex.m_normal.z = m_pNormals[nIndex].z;

		//newVertex.m_normal.x = m_pRecalculatedNormals[vIndex].x;
		//newVertex.m_normal.y = m_pRecalculatedNormals[vIndex].y;
		//newVertex.m_normal.z = m_pRecalculatedNormals[vIndex].z;

		newVertex.m_texCoord.x = m_pTexCoords[tIndex].x;
		newVertex.m_texCoord.y = m_pTexCoords[tIndex].y;

		std::vector<Vertex>::iterator foundIt = std::find( vertices.begin(), vertices.end(), newVertex );

		if( foundIt != vertices.end() )
		{
			// vertex already contained -> add the correct index
			index = std::distance( vertices.begin(), foundIt );
		}else
		{
			index = vertices.size();
			vertices.push_back( newVertex );
		}

		indices.push_back( index );

		// Second vertex of the face 

		vIndex = m_pFaces[i].m_vertexIndex2 - 1;
		tIndex = m_pFaces[i].m_texCoordIndex2 - 1;
		nIndex = m_pFaces[i].m_normalIndex2 - 1;

		newVertex.m_position.x = m_pVertices[vIndex].x;
		newVertex.m_position.y = m_pVertices[vIndex].y;
		newVertex.m_position.z = m_pVertices[vIndex].z;

		newVertex.m_normal.x = m_pNormals[nIndex].x;
		newVertex.m_normal.y = m_pNormals[nIndex].y;
		newVertex.m_normal.z = m_pNormals[nIndex].z;

		//newVertex.m_normal.x = m_pRecalculatedNormals[vIndex].x;
		//newVertex.m_normal.y = m_pRecalculatedNormals[vIndex].y;
		//newVertex.m_normal.z = m_pRecalculatedNormals[vIndex].z;

		newVertex.m_texCoord.x = m_pTexCoords[tIndex].x;
		newVertex.m_texCoord.y = m_pTexCoords[tIndex].y;

		foundIt = std::find( vertices.begin(), vertices.end(), newVertex );

		if( foundIt != vertices.end() )
		{
			// vertex already contained -> add the correct index
			index = std::distance( vertices.begin(), foundIt );
		}else
		{
			index = vertices.size();
			vertices.push_back( newVertex );
		}

		indices.push_back( index );

		// Third vertex of the face 

		vIndex = m_pFaces[i].m_vertexIndex3 - 1;
		tIndex = m_pFaces[i].m_texCoordIndex3 - 1;
		nIndex = m_pFaces[i].m_normalIndex3 - 1;

		newVertex.m_position.x = m_pVertices[vIndex].x;
		newVertex.m_position.y = m_pVertices[vIndex].y;
		newVertex.m_position.z = m_pVertices[vIndex].z;

		newVertex.m_normal.x = m_pNormals[nIndex].x;
		newVertex.m_normal.y = m_pNormals[nIndex].y;
		newVertex.m_normal.z = m_pNormals[nIndex].z;

		//newVertex.m_normal.x = m_pRecalculatedNormals[vIndex].x;
		//newVertex.m_normal.y = m_pRecalculatedNormals[vIndex].y;
		//newVertex.m_normal.z = m_pRecalculatedNormals[vIndex].z;

		newVertex.m_texCoord.x = m_pTexCoords[tIndex].x;
		newVertex.m_texCoord.y = m_pTexCoords[tIndex].y;

		foundIt = std::find( vertices.begin(), vertices.end(), newVertex );

		if( foundIt != vertices.end() )
		{
			// vertex already contained -> add the correct index
			index = std::distance( vertices.begin(), foundIt );
		}else
		{
			index = vertices.size();
			vertices.push_back( newVertex );
		}

		indices.push_back( index );
	}

	
	std::ofstream out;

	// Open the destination file
	out.open( destinationFileName );
	
	// Write the header to the destination file
	out << "Vertex Count: " << vertices.size() << '\n';
	out << "Index Count: " << indices.size() << '\n';
	out << '\n';
	out << "Data:" << '\n';
	out << '\n';


	// Write the vertices to the file
	
	for( std::vector<Vertex>::iterator it = vertices.begin(); it != vertices.end(); ++it )
	{
		out << 'v' << ' ';
		out << it->m_position.x	<< ' ' << it->m_position.y  << ' ' << it->m_position.z << ' '
		    << it->m_texCoord.x << ' ' << it->m_texCoord.y << ' '
		    << it->m_normal.x	<< ' ' << it->m_normal.y   << ' ' << it->m_normal.z  << std::endl;
	}

	out << '\n';
	
	for( std::vector<long>::iterator it = indices.begin(); it != indices.end(); ++it )
	{
		out << 'i' << ' ';
		out << *it << std::endl;
	}

	out << '\n';

	
	/* Original code
	std::ofstream out;

	// Open the destination file
	out.open( destinationFileName );
	
	// Write the header to the destination file
	out << "Vertex Count: " << ( m_faceCount * 3 ) << std::endl;
	out << std::endl;
	out << "Data:" << std::endl;
	out << std::endl;

	// Helpers, necessary as vertices/texture coordinates/normals in model files are indexed starting from one 
	// while the first element in the m_pVertices/m_pTexCoords/m_pNormals arrays has index 0
	int vIndex = 0;
	int tIndex = 0;
	int nIndex = 0;

	// Output each face with its three vertices to the file
	for( int i = 0; i < m_faceCount; ++i )
	{
		vIndex = m_pFaces[i].m_vertexIndex1 - 1;
		tIndex = m_pFaces[i].m_texCoordIndex1 - 1;
		nIndex = m_pFaces[i].m_normalIndex1 - 1;

		out << m_pVertices[vIndex].m_x	<< ' ' << m_pVertices[vIndex].m_y  << ' ' << m_pVertices[vIndex].m_z << ' '
		    << m_pTexCoords[tIndex].m_x << ' ' << m_pTexCoords[tIndex].m_y << ' '
		    << m_pNormals[nIndex].m_x	<< ' ' << m_pNormals[nIndex].m_y   << ' ' << m_pNormals[nIndex].m_z  << std::endl;

		vIndex = m_pFaces[i].m_vertexIndex2 - 1;
		tIndex = m_pFaces[i].m_texCoordIndex2 - 1;
		nIndex = m_pFaces[i].m_normalIndex2 - 1;

		out << m_pVertices[vIndex].m_x  << ' ' << m_pVertices[vIndex].m_y  << ' ' << m_pVertices[vIndex].m_z << ' '
		    << m_pTexCoords[tIndex].m_x << ' ' << m_pTexCoords[tIndex].m_y << ' '
		    << m_pNormals[nIndex].m_x   << ' ' << m_pNormals[nIndex].m_y   << ' ' << m_pNormals[nIndex].m_z  << std::endl;

		vIndex = m_pFaces[i].m_vertexIndex3 - 1;
		tIndex = m_pFaces[i].m_texCoordIndex3 - 1;
		nIndex = m_pFaces[i].m_normalIndex3 - 1;

		out << m_pVertices[vIndex].m_x  << ' ' << m_pVertices[vIndex].m_y  << ' ' << m_pVertices[vIndex].m_z << ' '
		    << m_pTexCoords[tIndex].m_x << ' ' << m_pTexCoords[tIndex].m_y << ' '
		    << m_pNormals[nIndex].m_x   << ' ' << m_pNormals[nIndex].m_y   << ' ' << m_pNormals[nIndex].m_z  << std::endl;
	}

	// Close the output file
	out.close();

	return S_OK;
	*/
	out.close();
	return S_OK;
}


//--------------------------------------------------------------------------------------
// Release all ressources
//--------------------------------------------------------------------------------------
HRESULT Converter::Cleanup( void )
{
	if( m_pVertices )	{ delete[] m_pVertices;  m_pVertices  = nullptr; }
	if( m_pTexCoords )	{ delete[] m_pTexCoords; m_pTexCoords = nullptr; }
	if( m_pNormals )	{ delete[] m_pNormals;	 m_pNormals   = nullptr; }
	if( m_pRecalculatedNormals) { delete[] m_pRecalculatedNormals;	 m_pRecalculatedNormals   = nullptr; }
	if( m_pFaces )		{ delete[] m_pFaces;	 m_pFaces     = nullptr; }

	return S_OK;
}


//--------------------------------------------------------------------------------------
// Read in the model data from an .obj source file and store it in the members of the object
//--------------------------------------------------------------------------------------
HRESULT Converter::ReadDataFromObjFile( const std::string& sourceFileName )
{
	std::ifstream in;
	char input;

	// Open the file
	in.open( sourceFileName );

	// Check if it was successful in opening the file.
	if( in.fail() )
	{
		return E_FAIL;
	}

	// Read the contents of the file and accumulate vertex, texture coordinate, normal and face counts
	// (needed to allocate the proper amount of dynamic memory to store the model data)
	
	in.get(input);

	while( !in.eof() )
	{
		// Line starts with a 'v' -> vertex data
		if( input == 'v' )
		{
			in.get( input );

			if( input == ' ' )
				++m_vertexCount;

			if( input == 't' )
				++m_texCoordCount;

			if( input == 'n' )
				++m_normalCount;
		}

		// Line starts with a 'f' -> face data
		if( input == 'f' )
		{
			in.get( input );
			if( input == ' ' )
				++m_faceCount;
		}
		
		// Skip the line if no useful data contained
		while( input != '\n' )
		{
			in.get( input );
		}

		// Next line
		in.get( input );
	}

	// Allocate enough dynamic memory to store all vertex and face data contained
	// in the source file

	m_pVertices = new XMFLOAT3[m_vertexCount];
	if(!m_pVertices)
	{
		return E_FAIL;
	}
	
	m_pRecalculatedNormals = new XMFLOAT3[m_vertexCount];
	if(!m_pRecalculatedNormals)
	{
		return E_FAIL;
	}
	
	m_pTexCoords = new XMFLOAT3[m_texCoordCount];
	if(!m_pTexCoords)
	{
		return E_FAIL;
	}
	
	m_pNormals = new XMFLOAT3[m_normalCount];
	if(!m_pNormals)
	{
		return E_FAIL;
	}
	
	m_pFaces = new Face[m_faceCount];
	if(!m_pFaces)
	{
		return E_FAIL;
	}

	// Read in the actual data

	// Maintain indices to write the data to the proper place in the previously allocated memory
	int vertexIndex		= 0;
	int texCoordIndex	= 0;
	int normalIndex		= 0;
	int faceIndex		= 0;

	// Additionally needed for reading in faces (to hold the '/' between data)
	char input2;

	// set the stream back to the beginning of the file
	in.clear();
	in.seekg(0, std::ios_base::beg);

	// todo: account for modeling software that also has a left-handed coordinate system

	// Read in vertices, texture coordinates, normals and faces into the data structures.
	in.get( input );
	while( !in.eof() )
	{
		if( input == 'v' )
		{
			in.get( input );

			// Read in vertices
			if( input == ' ' ) 
			{ 
				in >> m_pVertices[vertexIndex].x >> m_pVertices[vertexIndex].y >> m_pVertices[vertexIndex].z;

				// Invert the z vertex to change from right-handed coordinate system (Maya, 3ds Max) to left-handed system (DirectX)
				m_pVertices[vertexIndex].z = m_pVertices[vertexIndex].z * -1.0f;
				++vertexIndex; 
			}

			// Read in texture coordinates
			if( input == 't' ) 
			{ 
				in >> m_pTexCoords[texCoordIndex].x >> m_pTexCoords[texCoordIndex].y;

				// Invert the v texture coordinate to account for left-handed coordinate system of DirectX
				m_pTexCoords[texCoordIndex].y = 1.0f - m_pTexCoords[texCoordIndex].y;
				++texCoordIndex; 
			}

			// Read in normals
			if( input == 'n' ) 
			{ 
				in >> m_pNormals[normalIndex].x >> m_pNormals[normalIndex].y >> m_pNormals[normalIndex].z;

				// Invert the z normal to account for left-handed coordinate system of DirectX
				m_pNormals[normalIndex].z = m_pNormals[normalIndex].z * -1.0f;
				++normalIndex; 
			}
		}

		// Read in the faces
		if( input == 'f' ) 
		{
			in.get( input );
			if( input == ' ' )
			{
				// Read in the face data backwards to convert it from a right-handed coordinate system to a left-handed system 
				in >> m_pFaces[faceIndex].m_vertexIndex3 >> input2 >> m_pFaces[faceIndex].m_texCoordIndex3 >> input2 >> m_pFaces[faceIndex].m_normalIndex3
				   >> m_pFaces[faceIndex].m_vertexIndex2 >> input2 >> m_pFaces[faceIndex].m_texCoordIndex2 >> input2 >> m_pFaces[faceIndex].m_normalIndex2
				   >> m_pFaces[faceIndex].m_vertexIndex1 >> input2 >> m_pFaces[faceIndex].m_texCoordIndex1 >> input2 >> m_pFaces[faceIndex].m_normalIndex1;
				faceIndex++;
			}
		}

		// Read in the remainder of the line
		while( input != '\n' )
		{
			in.get( input );
		}

		// Next line
		in.get( input );
	}

	// Close the file
	in.close();

	return S_OK;
}

//--------------------------------------------------------------------------------------
// Recalculate vertex normals as an average of the associated face normals.
// Mostly taken from: http://braynzarsoft.net/index.php?p=D3D11OBJMODEL
//--------------------------------------------------------------------------------------
void Converter::ComputeNormals( void )
{
	std::vector<XMFLOAT3> tempNormal;

	//normalized and unnormalized normals
	XMFLOAT3 unnormalized = XMFLOAT3(0.0f, 0.0f, 0.0f);

	//Used to get vectors (sides) from the position of the verts
	float vecX, vecY, vecZ;

	//Two edges of our triangle
	XMVECTOR edge1 = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	XMVECTOR edge2 = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);

	int vIndex = 0;

	//Compute face normals
	for(int i = 0; i < m_faceCount; ++i)
	{
		int vIndex1 = m_pFaces[i].m_vertexIndex1 - 1;
		int vIndex2 = m_pFaces[i].m_vertexIndex2 - 1;
		int vIndex3 = m_pFaces[i].m_vertexIndex3 - 1;

		//Get the vector describing one edge of our triangle (edge 0,2)
		vecX = m_pVertices[vIndex1].x - m_pVertices[vIndex3].x;
		vecY = m_pVertices[vIndex1].y - m_pVertices[vIndex3].y;
		vecZ = m_pVertices[vIndex1].z - m_pVertices[vIndex3].z;		
		edge1 = XMVectorSet(vecX, vecY, vecZ, 0.0f);	//Create our first edge

		XMFLOAT3 v = m_pVertices[vIndex + 2];

		//Get the vector describing another edge of our triangle (edge 2,1)
		vecX = m_pVertices[vIndex3].x - m_pVertices[vIndex2].x;
		vecY = m_pVertices[vIndex3].y - m_pVertices[vIndex2].y;
		vecZ = m_pVertices[vIndex3].z - m_pVertices[vIndex2].z;		
		edge2 = XMVectorSet(vecX, vecY, vecZ, 0.0f);	//Create our second edge

		//Cross multiply the two edge vectors to get the un-normalized face normal
		XMStoreFloat3(&unnormalized, XMVector3Cross(edge1, edge2) );
		tempNormal.push_back(unnormalized);			//Save unormalized normal (for normal averaging)
	}


	//Compute vertex normals (normal Averaging)
	XMVECTOR normalSum = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	int facesUsing = 0;
	float tX;
	float tY;
	float tZ;

	//Go through each vertex
	for(int i = 0; i < m_vertexCount; ++i)
	{
		//Check which triangles use this vertex
		for(int j = 0; j < m_faceCount; ++j)
		{
			if(m_pFaces[j].m_vertexIndex1 -1 == i ||
				m_pFaces[j].m_vertexIndex2 -1 == i ||
				m_pFaces[j].m_vertexIndex3 -1 == i)
			{
				tX = XMVectorGetX(normalSum) + tempNormal[j].x;
				tY = XMVectorGetY(normalSum) + tempNormal[j].y;
				tZ = XMVectorGetZ(normalSum) + tempNormal[j].z;

				normalSum = XMVectorSet(tX, tY, tZ, 0.0f);	//If a face is using the vertex, add the unormalized face normal to the normalSum
				facesUsing++;
			}
		}

		//Get the actual normal by dividing the normalSum by the number of faces sharing the vertex
		normalSum = normalSum / static_cast<float>( facesUsing );

		//Normalize the normalSum vector
		normalSum = XMVector3Normalize(normalSum);

		//Store the normal in our current vertex

		XMStoreFloat3( &m_pRecalculatedNormals[i], normalSum);

		//m_pRecalculatedNormals[i].x = XMVectorGetX(normalSum);
		//m_pRecalculatedNormals[i].y = XMVectorGetY(normalSum);
		//m_pRecalculatedNormals[i].z = XMVectorGetZ(normalSum);

		//Clear normalSum and facesUsing for next vertex
		normalSum = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
		facesUsing = 0;
	}
}