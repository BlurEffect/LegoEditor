/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  PS_Simple.fx
*  Simply returns the input colour as the final colour for the pixel.
*/

struct PS_INPUT
{
	float4 Position	: SV_POSITION;
	float4 Colour	: COLOUR;
	// float3 Normal	: NORMAL;
	// float2 TexCoord : TEXCOORD;
};

float4 PS( PS_INPUT input ) : SV_TARGET
{
    return input.Colour;
}
