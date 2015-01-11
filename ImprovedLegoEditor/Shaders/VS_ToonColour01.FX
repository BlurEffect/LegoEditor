/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  VS_ToonColour01.fx
*  Performs standard transformation of the vertex position and normal
*  and passes them together with the vertex colour to the next stage.
*/

// Updated once per frame
cbuffer cbPerFrame
{
	row_major float4x4 ViewProjection;  // The combined view and projection matrix
};


struct VS_INPUT
{
	// vertex data
	float4 Position	 : POSITION;
	float3 Normal	 : NORMAL;
	float3 AvgNormal : AVGNORMAL;
	float2 TexCoord  : TEXCOORD;

	// instance data
	row_major float4x4 World  : WORLD;   // row_major "automatically" transposes matrix
	float4			   Colour : COLOUR;
};

struct VS_OUTPUT
{
	float4 Position	: SV_POSITION;
	float4 Colour	: COLOUR;
	float3 Normal	: NORMAL;
	//float2 TexCoord : TEXCOORD;
};

VS_OUTPUT VS( VS_INPUT input )
{
    VS_OUTPUT output;

	// Transfrom vertex position
    output.Position = mul( input.Position, ( mul( input.World, ViewProjection ) ) );
	
	// Transform normal to world space and normalize the normal vector
	output.Normal = mul( input.Normal, (float3x3) input.World );

	// forward texture coordinate unchanged (not needed at the moment)
    // output.TexCoord = input.TexCoord;

	// Forward object colour
	output.Colour = input.Colour;

    return output;
}