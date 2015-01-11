/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  VS_Font.fx
*  Performs standard transformation on the vertex position and forwards it
*  together with the unaltered texture coordinates to the next stage.
*/

// Updated once per frame
cbuffer cbPerFrame
{
	row_major float4x4 WVP;		// The combined world, view and projection matrices
};

struct VS_INPUT
{
	float4 Position : POSITION;
    float2 TexCoord : TEXCOORD;
};

struct VS_OUTPUT
{
	float4 Position : SV_POSITION;
    float2 TexCoord : TEXCOORD;
};

VS_OUTPUT VS( VS_INPUT input )
{
    VS_OUTPUT output;

	// Transfrom vertex position
    output.Position = mul( input.Position, WVP );

	// Forward texture coordinate unchanged
    output.TexCoord = input.TexCoord;

    return output;
}

