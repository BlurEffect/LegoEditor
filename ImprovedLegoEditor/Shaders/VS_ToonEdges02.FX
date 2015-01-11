/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  VS_ToonEdges02.fx
*  Moves each vertex along the normal vector it shares with other vertices
*  in the same position in order to create an outline around objects without gaps
*  between the extruded faces. The new position is transformed as usual
*  and forwarded to the pixel shader.
*/

// Uncomment this line to enable scaling of the outlines to obtain a uniform outline throughout the scene.
//#define SCALING_ENABLED

// Updated once per scene
cbuffer cbPerScene
{
	float VertexOffset; // Determines how far the vertices are moved along their normal
};

// Updated each frame
cbuffer cbPerFrame
{
	row_major float4x4 ViewProjection;  // The combined view and projection matrices
	float4			   ViewPosition;
};

struct VS_INPUT
{
	// vertex data
	float4 Position	: POSITION;
	float3 Normal	: NORMAL;
	float3 AvgNormal : AVGNORMAL;
	float2 TexCoord : TEXCOORD;

	// instance data
	row_major float4x4 World  : WORLD;   
	float4	 Colour : COLOUR;
};

struct VS_OUTPUT
{
	float4 Position	: SV_POSITION;
	//float4 Colour	: COLOUR;
	//float3 Normal	: NORMAL;
	//float2 TexCoord : TEXCOORD;
};

VS_OUTPUT VS( VS_INPUT input )
{
    VS_OUTPUT output;

	float scale = 0.0f;
	#ifdef SCALING_ENABLED
		// Scale the width of the outline with growing distance of the vertices from the camera in order to
		// ensure a uniform outline width for the whole scene.
		scale = distance( mul( float4( input.Position.xyz, 1.0f ), input.World ), ViewPosition );
	#else
		// Scale the outlines by a fix value. Thus, outlines will become thinner as the distance from the
		// camera grows.
		scale = 150.0f;
	#endif

	// Move the vertex along the shared, average normal
	input.Position += mul( scale * VertexOffset, float4( input.AvgNormal.xyz, 0 ) );

	// Transform the vertex position
    output.Position = mul( input.Position,( mul( input.World, ViewProjection ) ) );
	
	// transform normal to world space (not needed at the moment)
	// output.Normal = mul( input.Normal, input.World );

	// forward texture coordinate unchanged (not needed at the moment)
    // output.TexCoord = input.TexCoord;

	// forward object colour (not needed at the moment)
	//output.Colour = input.Colour;

    return output;
}
