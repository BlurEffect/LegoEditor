/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  VS_Lighted.fx
*  Performs standard transformation on vertex position and normal
*  and forwards them together with the vertex colour
*/

// Updated once per frame
cbuffer cbPerFrame
{
	row_major float4x4 ViewProjection;  // The combined view and projection matrices
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
    output.Position = mul( input.Position, ( mul( input.World, ViewProjection) ) );
	
	// Transform normal to world space
	output.Normal = mul( float4( input.Normal.xyz, 0.0f ), input.World ).xyz;

	// Forward texture coordinate unchanged (not needed at the moment)
    //output.TexCoord = input.TexCoord;

	// Forward vertex colour
	output.Colour = input.Colour;

    return output;
}