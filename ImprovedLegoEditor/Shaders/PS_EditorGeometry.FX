/* 
*  Kevin Meergans, Improved Lego Editor, 2014
*  PS_EditorGeometry.fx
*  Forwards the input colour as the final colour for th pixel.
*/

struct VS_OUTPUT
{
	float4 Pos : SV_POSITION;
	float4 worldPos : POSITION;
	float4 colour : COLOUR;
};

float4 PS(VS_OUTPUT input) : SV_TARGET
{
	return input.colour;
}
