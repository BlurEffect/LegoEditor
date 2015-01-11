/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  PS_ToonEdges01.fx
*  Simply returns a defined edge colour for every pixel.
*/

// Updated once per scene
cbuffer cbPerScene
{
	float4   EdgeColour; // The colour to paint the outline in
};

struct PS_INPUT
{
	float4 Position	: SV_POSITION;
	//float4 Colour	: COLOUR;
	//float3 Normal	: NORMAL;
	//float2 TexCoord : TEXCOORD;
};

float4 PS(PS_INPUT input) : SV_TARGET
{
    return EdgeColour;
}
