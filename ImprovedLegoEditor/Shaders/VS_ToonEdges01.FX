/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  VS_ToonEdges01.fx
*  Moves vertices along their normals in order to create an outline around
*  objects. Afterwards, the new position is transformed as usual
*  and forwarded to the pixel shader.
*/

// Updated once per scene
cbuffer cbPerScene
{
	float VertexOffset; // Determines how far the vertices are moved along their normal
};


// Updated once per frame
cbuffer cbPerFrame
{
	row_major float4x4 ViewProjection; // The combined view and projection matrices
};

struct VS_INPUT
{
	// vertex data
	float4 Position	 : POSITION;
	float3 Normal	 : NORMAL;
	float3 AvgNormal : AVGNORMAL;
	float2 TexCoord  : TEXCOORD;

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

	// Move the vertex along its normal vector
	input.Position += mul( VertexOffset, float4( input.Normal.xyz, 0 ) );

	// Transform the vertex position
    output.Position = mul( input.Position,( mul( input.World, ViewProjection ) ) );
	
	// transform normal to world space (not needed at the moment)
	//output.Normal = mul( input.Normal, input.World );

	// forward texture coordinate unchanged (not needed at the moment)
    // output.TexCoord = input.TexCoord;

	// forward object colour (not needed at the moment)
	// output.Colour = input.Colour;


    return output;
}
