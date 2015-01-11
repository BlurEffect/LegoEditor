/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  ShaderDataStructures.h
*  Contains data structures used in the communication between renderer
*  and shaders in order to set/update the parameters of latter ones.
*/

#ifndef SHADER_DATA_STRUCTURES_H
#define SHADER_DATA_STRUCTURES_H

#include <Windows.h>
#include <xnamath.h>
#include <string>

// forward declarations
class VertexShader;
class PixelShader;

//--------------------------------------------------------------------------------------
// Contains all data that could be required by a shader to update its per-scene 
// constant buffer.
//--------------------------------------------------------------------------------------
struct PerSceneData
{
	XMFLOAT4   m_diffuseLightColor;
	XMFLOAT4   m_edgeColour;
	XMFLOAT3   m_lightDirection;

	// for Toon Shading 01
	float	   m_vertexOffset01;

	// for Toon Shading 02
	float	   m_vertexOffset02;

	// for Toon Shading 03
	float	   m_edgeThreshold;		

	// for Toon Shading 04
	float	   m_moveBias;			// move backface vertices by this much towards the viewpoint to create outlines

	// for Toon Shading 05
	float	   m_outlineWidth;

	// for Toon Shading 06
	float m_viewportWidth;
	float m_viewportHeight;
	float m_thickness;
	float m_thresholdNormalsEdges;
	float m_thresholdDepthEdges;
};

//--------------------------------------------------------------------------------------
// Contains all data that could be required by a shader to update its per-frame
// constant buffer.
//--------------------------------------------------------------------------------------
struct PerFrameData
{
	XMFLOAT4X4 m_viewProjection;
	XMFLOAT4X4 m_viewMatrix;
	XMFLOAT4X4 m_projectionMatrix;
	XMFLOAT3   m_viewPosition;
};

//--------------------------------------------------------------------------------------
// Contains all data that could be required by a shader to update its per-object 
// constant buffer.
//--------------------------------------------------------------------------------------
struct PerObjectData
{
	XMFLOAT4X4  m_WVP;
	XMFLOAT4	m_colour;
};

//--------------------------------------------------------------------------------------
// Bundles a vertex and a pixel shader to be used together.
//--------------------------------------------------------------------------------------
struct ShaderPass
{
	VertexShader* m_vertexShader;
	PixelShader*  m_pixelShader;
};

//--------------------------------------------------------------------------------------
// Bundles a group of shaders to be used together.
//--------------------------------------------------------------------------------------
struct ShaderGroup
{
	ShaderGroup( void ) : m_numberOfPasses( 0 ), m_pShaderPasses( nullptr ){}
	
	bool Initialise( int numOfPasses )
	{
		m_numberOfPasses = numOfPasses;
		m_pShaderPasses = new ShaderPass[numOfPasses];
		return ( m_pShaderPasses != nullptr );
	}

	int m_numberOfPasses;
	ShaderPass* m_pShaderPasses;

	void Cleanup( void )
	{
		delete[] m_pShaderPasses;
	}
};

//--------------------------------------------------------------------------------------
// Holds identifiers for the different shaders used by the application. Used as index
// into an array holding the shader objects
//--------------------------------------------------------------------------------------
enum Shaders
{
	// todo: at the moment some shaders below are identical which was chosen deliberately to be more flexible if it comes
	// to changes to a shader (-> no other shaders impacted), reuse might be better though

	EditorGeometryVS,		// Standard transformations of vertex input (different vertex input than SimpleVS)
	EditorGeometryPS,		// Simply return vertex colour as final colour (no lighting)
	SimpleVS,				// Standard transformations of vertex input
	SimplePS,				// Simply return vertex colour as final colour
	LightedVS,				// Standard transformations of vertex input
	LightedPS,				// Simple diffuse lighting for one directional light
	ToonColour01VS,			// Standard transformations
	ToonColour01PS,			// Calculates light intensity and uses it to select one of several shades (defined in the code) to light the pixel in
	ToonEdges01VS,			// Moves vertices along their normal
	ToonEdges01PS,			// Simply renders everything in a specified outline colour
	ToonColour02VS,			// Standard transformations
	ToonColour02PS,			// Calculates light intensity and uses it to select one of several shades (by a texture lookup) to light the pixel in
	ToonEdges02VS,			// Moves vertices along the average normal they share with other vertices in the same position
	ToonEdges02PS,			// Simply renders everything in a specified outline colour
	Toon03VS,				// Use dot product between view vector and vertex normal to determine edge proximity
	Toon03PS,				// Uses edge proximity to determine whether to shade a pixel (as in the colour pass of Toon02) or to draw it in an outline colour
	ToonColour04VS,			// Standard transformations
	ToonColour04PS,			// Calculates light intensity and uses it to select one of several shades (by a texture lookup) to light the pixel in
	ToonEdges04VS,			// Moves vertices along the screen-z axis by a certain bias
	ToonEdges04PS,			// Simply renders everything in a specified outline colour
	ToonColour05VS,			// Standard transformations
	ToonColour05PS,			// Calculates light intensity and uses it to select one of several shades (by a texture lookup) to light the pixel in
	ToonEdges05VS,			// Move vertices along the x and y axis by a certain offset after transforming them to screen space
	ToonEdges05PS,			// Simply renders everything in a specified outline colour
	CreateMapsToon06VS,		// Standard transformations and forwards depth/normal information.
	CreateMapsToon06PS,		// Determines final colour as in Toon02 and renders it a first render target while rendering normal (currently disabled) and depth information to a second target
	ComposeImageToon06VS,	// Forwards input without transformation
	ComposeImageToon06PS,	// Applies a Sobel filter on a given texture (with normal/depth values) to render edge pixels in an outline colour 
	NumberOfShaders
};

//--------------------------------------------------------------------------------------
// Holds identifiers for the different shaders groups used by the application. Used as index
// into an array holding the shader group objects
//--------------------------------------------------------------------------------------
enum ShaderGroups
{
	GroupEditorGeometry,			// Simple unlit shading for editor geometry
	GroupSimple,					// Simple shading without lighting, one pass
	GroupLighted,					// Simple lighted shading, one pass
	GroupToon01,				    // Toon shading with colour quantization in code and two passes (edges by drawing backfaces)
	GroupToon02,					// Toon shading with colour quantization by texture and two passes (edges by drawing backfaces)
	GroupToon03,					// Toon shading as shown in Dot3 Cel Shading in ShaderX3, one pass
	GroupToon04,					// Move backfaces towards viewer by a certain bias to create outlines
	GroupToon05,					// Unity's Cel Shading
	GroupToon06,					// Image based, Sobel filter
	NumberOfShaderGroups
};

static const std::string ShaderGroupNames[NumberOfShaderGroups] = 
{
	"Solid Colour (editor)",
	"No Lighting",
	"Simple Lighting",
	"Cel Shading 1",
	"Cel Shading 2",
	"Cel Shading 3",
	"Cel Shading 4",
	"Cel Shading 5",
	"Cel Shading 6"
};



#endif