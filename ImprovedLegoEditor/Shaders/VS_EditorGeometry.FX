/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  VS_EditorGeometry.fx
*  Performs standard transformation of the vertex position and
*  passes it together with the vertex colour to the next stage.
*/

// Updated once per object
cbuffer cbPerSimpleObject
{
	row_major float4x4 WVP;   // The combined world, view and projection matrices
	float4 colour;			  // The vertex colour to use
};

struct VS_OUTPUT
{
	float4 Pos : SV_POSITION;
	float4 worldPos : POSITION;
	float4 colour : COLOUR;
};

VS_OUTPUT VS(float4 inPos : POSITION)
{
    VS_OUTPUT output;

    output.Pos      = mul(inPos, WVP);
    output.worldPos = inPos;
	output.colour   = colour;

    return output;
}

